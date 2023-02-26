#ifndef INFO_H
#define INFO_H

#include "../Command.hpp"

class Info : public Command // Classe Info hérite de la classe Command
{
  public:
    // Constructeur de la classe Info
    Info()
    {
        // Initialisation des attributs de la commande
        name = "info";
        description = "Get info about the current IRC server";
        usage = "info";
        example[0] = "info";
    }

    // Méthode exécutée lorsque la commande est appelée
    void execute()
    {
        // Affichage du nombre de clients connectés et du nom de l'utilisateur qui a exécuté la commande
        sender->message(
            std::string("Connected clients: " + itoa(server->clients.size()) + "\n" +
                        "Name: " + sender->nick + "\n")
                .c_str());

        // Parcours de la liste des clients connectés au serveur
        for (size_t i = 0; i < server->clients.size(); i++)
        {
            // Si le client n'est pas celui qui a exécuté la commande, afficher son nom d'utilisateur
            if (server->clients[i] != sender)
            {
                sender->message(
                    std::string("Client " + server->clients[i]->nick + "\n").c_str());
            }
        }
    }
};

#endif
