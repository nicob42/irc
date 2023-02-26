#ifndef PM_H
#define PM_H

#include "../Command.hpp" 

class PM : public Command // Classe PM hérite de la classe Command
{
  public:
    // Constructeur de la classe
    PM()
    {
        name = "pm";  // Nom de la commande
        description = "Send message to the user";  // Description de la commande
        usage = "pm <nickname> <message>";  // Usage de la commande
        example[0] = "pm Faerris hello bff";  // Exemple d'utilisation
        example[1] = "pm Faerris On se fait du koli?";  // Exemple d'utilisation
    }

    // Méthode exécutée lorsque la commande est appelée
    void execute() 
    {
        if (message->getParams().size() < 2)  // Si le nombre de paramètres est inférieur à 2
        {
            sender->message("Wrong usage, use it this way : pm <nickname> <message>\n");  // On envoie un message d'erreur
        }
        else
        {
            std::map<size_t, std::string> p = message->getParams();  // On récupère les paramètres de la commande

            std::string result = "";
            for (std::map<size_t, std::string>::iterator it = p.begin(); it != p.end(); ++it)  // On parcourt les paramètres
                if (it->first != 0)  // Si on n'est pas sur le premier paramètre (qui est le nom d'utilisateur)
                    result += std::string(it->second + " ");  // On ajoute le paramètre à une chaîne de caractères
            if (name == sender->nick)  // Si le nom de l'utilisateur est identique au nom de l'expéditeur
            {
                sender->message("Sorry you can't talk to yourself!\n");  // On envoie un message d'erreur
            }
            else 
            {
                for (size_t i = 0; i < server->clients.size(); i++)  // On parcourt les clients connectés
                {
                    if (server->clients[i]->nick == p[0])  // Si le nom du client est identique au premier paramètre
                    {
                        server->clients[i]->message(std::string(sender->nick + " sent you a message: " + result + "\n").c_str());  // On envoie le message au client
                        return;  // On quitte la fonction
                    }
                }
                sender->message("Client not found!\n");  // On envoie un message d'erreur
            }
        }
    }
};

#endif
