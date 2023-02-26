#ifndef BAN_H
#define BAN_H

#include "../Command.hpp"

class Ban : public Command // Classe Ban hérite de la classe Command
{
  public:
  // Constructeur
    Ban()
    {
        name = "ban"; // Définition du nom de la commande
        description = "Ban a naughty people"; // Définition de la description de la commande
        usage = "ban <client_nickname>"; // Définition de l'utilisation de la commande
        example[0] = "ban Faerris"; // Définition d'un exemple d'utilisation de la commande
        ope_required = true; // Définition du statut de l'opérateur nécessaire pour utiliser la commande
    }

    bool validate(void) // Fonction de validation de la commande
    {
        std::map<size_t, std::string> p = message->getParams(); // Récupération des paramètres de la commande

        if (p.size() == 0 || p.size() > 2) // Vérification du nombre de paramètres
        {
            sender->message("Wrong usage, use it this way : ban <client_nickname>")
                             "<client_nickname>\n"); // Envoi d'un message d'erreur au client
            return (false); // Retourne faux si les paramètres sont invalides
        }
        else if (p[0] == sender->nick) // Vérification que le client ne se bannit pas lui-même
        {
            sender->message(std::string("Don't be stupid, don't hurt yourself\n").c_str()); // Envoi d'un message d'erreur au client
            return (false); // Retourne faux si le client essaie de se bannir lui-même
        }
        else if (!server->getClient(p[0])) // Vérification de l'existence du client à bannir
        {
            sender->message("Client not found!\n"); // Envoi d'un message d'erreur au client
            return (false); // Retourne faux si le client à bannir n'existe pas
        }
        return (true); // Retourne vrai si la validation a réussi
    }

    void execute() // Fonction d'exécution de la commande
    {
        std::string name = message->getParams()[0]; // Récupération du nom du client à bannir
        Client *    client = server->getClient(name); // Récupération du client à bannir
        size_t      client_index = server->getClientIndex(name); // Récupération de l'index du client à bannir

        client->message(
            std::string("You've been banned by " + sender->nick + "\n").c_str()); // Envoi d'un message au client banni
        sender->message(
            std::string("Client " + client->nick + " has been banned!\n").c_str()); // Envoi d'un message au client ayant exécuté la commande

        delete client; // Suppression du client banni
        server->_clients.erase(server->_clients.begin() + client_index); // Suppression du client banni de la liste de clients
        server->_pfds.erase(server->_pfds.begin() + client_index + 1); // Suppression du client banni du tableau de des
    }
};
#endif
