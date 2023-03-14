#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <poll.h>

#include <arpa/inet.h>

#define BUFFER_SIZE 1024

/**
 * Obtenir une sockaddr, IPv4 ou IPv6
 */
void *get_address_info(struct sockaddr *address)
{
	if (address->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)address)->sin_addr);
	}

	return &(((struct sockaddr_in6*)address)->sin6_addr);
}

/**
 * Programme principal
 */
int main(int argument_count, char *arguments[])
{
	int socket_descriptor;
	struct addrinfo hints, *server_info, *pointer;
	int result;
	char address_string[INET6_ADDRSTRLEN];

	if (argument_count != 3) {
	    fprintf(stderr,"Usage : telnot hostname port\n");
	    exit(1);
	}

	char *host_name = arguments[1];
	char *port = arguments[2];

	// Tentative de connexion

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((result = getaddrinfo(host_name, port, &hints, &server_info)) != 0) {
		fprintf(stderr, "getaddrinfo : %s\n", gai_strerror(result));
		return 1;
	}

	// Boucle à travers tous les résultats et se connecte au premier possible
	for(pointer = server_info; pointer != NULL; pointer = pointer->ai_next) {
		if ((socket_descriptor = socket(pointer->ai_family, pointer->ai_socktype,
				pointer->ai_protocol)) == -1) {

			continue;
		}

		if (connect(socket_descriptor, pointer->ai_addr, pointer->ai_addrlen) == -1) {
			close(socket_descriptor);
			continue;
		}

		break;
	}

	if (pointer == NULL) {
		fprintf(stderr, "Client : échec de la connexion\n");
		return 2;
	}

	// Connecté !

	inet_ntop(pointer->ai_family, get_address_info((struct sockaddr *)pointer->ai_addr),
			address_string, sizeof address_string);

	printf("Connecté à %s port %s\n", address_string, port);
	printf("Hit ^C to exit\n");

	freeaddrinfo(server_info); // Terminé avec cette structure

    // Surveille l'entrée standard et le descripteur de socket pour les données entrantes (prêtes à lire)
    struct pollfd file_descriptors[2];

    file_descriptors[0].fd = 0;
    file_descriptors[0].events = POLLIN;

    file_descriptors[1].fd = socket_descriptor;
    file_descriptors[1].events = POLLIN;

    // Boucle principale
    for(;;) {
	    if (poll(file_descriptors, 2, -1) == -1) {
		    perror("poll");
		    exit(1);
	    }

	    for (int i = 0; i < 2; i++) {

		    // Vérifie si prête à lire
		    if (file_descriptors[i].revents & POLLIN) {

			    int bytes_read, bytes_written;
			    char buffer[BUFFER_SIZE];

			    // Calcule où écrire les données. Si nous sommes à l'entrée standard (0),
			    // nous écrirons sur le descripteur de socket. Si nous sommes sur le descripteur de socket, nous écrirons sur la sortie standard (1).
			    int output_descriptor = file_descriptors[i].fd == 0? socket_descriptor: 1;

			    // Nous utilisons read() et write() ici car cela fonctionne sur
			    // tous les descripteurs de fichiers, pas seulement les sockets. send() et recv() échoueraient
			    // sur l'entrée standard et la sortie standard car ce ne sont pas des sockets.
			    if ((bytes_read = read(file_descriptors[i].fd, buffer, BUFFER_SIZE)) == -1) {
				    perror("read");
				    exit(2);
			    }

			    char *pointer = buffer;
			    int remaining_bytes = bytes_read;

			    // Écris toutes les données
			    while (remaining_bytes > 0) {
				    if ((bytes_written = write(output_descriptor, pointer, remaining_bytes)) == -1) {
					    perror("write");
					    exit(2);
				    }

				    pointer += bytes_written;
				    remaining_bytes -= bytes_written;
			    }
		    }
	    }
    }


    return 0;
}