#ifndef SERVER_H
#define SERVER_H

#include <arpa/inet.h> // bibliothèque pour la manipulation des adresses IP
#include <cstdlib> // bibliothèque standard en C++
#include <fcntl.h> // pour la manipulation de fichiers
#include <string> // pour les chaînes de caractères
#include <map> // pour les map
#include <vector> // pour les vecteurs

#include "./Channel.hpp" // inclusion de la classe Channel
#include "./Client.hpp" // inclusion de la classe Client
#include "./Color.hpp" // inclusion de la classe Color
#include "./config.hpp" // inclusion du fichier de configuration


class Command;

// Déclaration de la fonction validate_args
bool validate_args(int argc, char **argv);

class Server
{
  private:
    std::string const host; // Adresse IP du serveur
    std::string const servername; // Nom du serveur
    std::string const version; // Version du serveur
    std::string const port; // Port utilisé par le serveur
    std::string const password; // Mot de passe du serveur

  public:
    std::vector<Client *> _clients; // Liste des clients connectés

    std::map<std::string, Command *> _commands; // Liste des commandes disponibles

    std::map<std::string, Channel *> _channels; // Liste des canaux

    enum Status // Enumeration des états possibles du serveur
    {
        OFFLINE, // Hors ligne
        ONLINE, // En ligne
        CLOSED // Fermé
    } _status;

    std::vector<pollfd> _pfds; // Tableau des descripteurs de fichiers
    int                 _socket; // Descripteur de fichier pour la socket du serveur

  public:
    Server(std::string host, std::string port, std::string password); // Constructeur
    ~Server(); // Destructeur
    void close_server(); // Fonction pour fermer le serveur
    void run(); // Fonction principale pour lancer le serveur
bool is_running(void) // Fonction pour savoir si le serveur est en cours d'exécution
    {
        return (_status == ONLINE);
    }
    bool hasPassword(void) // Fonction pour savoir si le serveur a un mot de passe
    {
        return (password != "");
    }
    std::string const getPassword(void) // Fonction pour récupérer le mot de passe du serveur
    {
        return (password);
    }

    // Fonction pour récupérer la liste des clients connectés
    std::vector<Client *> getRelatedClients(Client *client)
    {
        std::vector<Channel *> channels = this->getChannels(); // Récupération de la liste des canaux
        std::vector<Client *>  related_clients; // Initialisation d'un vecteur vide pour stocker les clients

        // Parcours des canaux
        for (size_t i = 0; i < channels.size(); i++)
        {
            if (channels[i]->joined(client)) // Vérification si le client a rejoint le canal
            {
                std::vector<Client *> channel_clients = channels[i]->getClients(); // Récupération de la liste des clients du canal
                for (size_t u = 0; u < channel_clients.size(); u++) // Parcours des clients du canal
                {
                    std::cout << channel_clients[u]->getNick() << std::endl; // Affichage du nom du client (pour debug)
                    
                    // Vérifie que le client n'est pas déjà dans la liste
                    if (channel_clients[u] != client && !std::count(related_clients.begin(), related_clients.end(), channel_clients[u])) 
                    {
                        related_clients.push_back(channel_clients[u]);  // Ajoute le client à la liste des clients liés si il n'y est pas encore présent
                    }
                }
            }
      }
      return (related_clients);
    }
    // Fonction qui renvoie un vecteur de pointeurs de Channel contenant tous les channels 
    // auxquels le client est connecté
    std::vector<Channel *> getRelatedChannels(Client *client)
    {
        // Récupération de tous les channels
        std::vector<Channel *> channels = this->getChannels();
        // Vecteur qui va stocker les channels auxquels le client est connecté
        std::vector<Channel *> related_channels;

        // Parcours de tous les channels
        for (size_t i = 0; i < channels.size(); i++)
        {
            // Si le client est connecté au channel courant, on l'ajoute au vecteur des 
            // channels auxquels le client est connecté
            if (channels[i]->joined(client))
            {
                related_channels.push_back(channels[i]);
            }
        }
    // Retourne le vecteur des channels auxquels le client est connecté
    return (related_channels);
}
 private:
    void createServerListener(void); // méthode pour créer un listener pour le serveur
    void createServerPoll(void); // méthode pour créer un objet de sondage de socket pour le serveur
    void removeClientFromServer(size_t clientId); // méthode pour supprimer un client du serveur
    int readClient(size_t &i); // méthode pour lire des données envoyées par un client
    void setupCommands(void); // méthode pour configurer les commandes disponibles dans le serveur

 public:
    // Récupère un client en utilisant son nom
    Client *getClient(std::string const &name)
    {
        // Parcourt tous les clients connectés
        for (size_t i = 0; i < _clients.size(); i++)
        {
            std::cout << "Client name: " << _clients[i]->getNick() << std::endl;
            // Vérifie si le nom correspond
            if (_clients[i]->getNick() == name)
                return (_clients[i]); // Retourne le client correspondant
        }
        std::cout << "Client not found" << std::endl;
        return (NULL); // Retourne NULL si aucun client correspondant n'a été trouvé
    }

    // Récupère l'index d'un client en utilisant son nom
    size_t getClientIndex(std::string &name)
    {
        // Parcourt tous les clients connectés
        for (size_t i = 0; i < _clients.size(); i++)
        {
            // Vérifie si le nom correspond
            if (_clients[i]->_nick == name)
                return (i); // Retourne l'index du client correspondant
        }
        return (-1); // Retourne -1 si aucun client correspondant n'a été trouvé
    }

    // Récupère un canal en utilisant son nom
    Channel *getChannel(std::string &name)
    {
        // Si le nom commence par un '#', retire le premier caractère
        if (name.at(0) == '#')
            name = name.substr(1);
        return _channels[name]; // Retourne le canal correspondant au nom donné
    }

    // Récupère tous les canaux disponibles
    std::vector<Channel *> getChannels(void)
    {
        std::vector<Channel *>                     channels; // Crée un vecteur de canaux
        std::map<std::string, Channel *>::iterator it;
        for (it = _channels.begin(); it != _channels.end(); it++)
            channels.push_back(it->second); // Ajoute chaque canal au vecteur
        return channels; // Retourne le vecteur de canaux
    }

    // Crée un nouveau canal
    Channel *createChannel(std::string &name, std::string &password)
    {
        // Si le nom commence par un '#', retire le premier caractère
        if (name.at(0) == '#')
            name = name.substr(1);
        _channels[name] = new Channel(name, password); // Crée un nouveau canal et l'ajoute à la map de canaux
        return _channels[name]; // Retourne le canal créé
    }

    // Récupère une commande en utilisant son nom
    Command *getCommand(std::string &name)
    {
        if (_commands.find(name) != _commands.end()) // Vérifie si la commande existe dans la map de commandes
            return _commands[name]; // Retourne la commande correspondante
        return (NULL); // Retourne NULL si aucune commande correspondante n'a été trouvée
    }
};


#endif
