#ifndef ECHO_H
#define ECHO_H

#include "../Command.hpp"

class Echo : public Command // Classe Echo hérite de la classe Command
{
  public:
  // Constructeur
    Echo()
    {
        name = "echo"; // Nom de la commande
        description = "Return the string sent"; // Description de la commande
        usage = "echo <string?>"; // Usage de la commande
        example[0] = "echo"; // Exemple d'utilisation de la commande
        example[1] = "echo hello";
        example[3] = "echo hello world";
    }

    // Méthode qui exécute la commande
    void execute()
    {
        std::map<size_t, std::string> p = message->getParams(); // On récupère les paramètres de la commande
        std::string                   result = ""; // On initialise une variable qui contiendra le résultat de la commande

        // On parcourt les paramètres et on les concatène dans la variable result
        for (std::map<size_t, std::string>::iterator it = p.begin(); it != p.end(); ++it)
            result += std::string(it->second + " ");

        // On envoie le résultat à tous les clients connectés, sauf l'expéditeur de la commande
        for (size_t i = 0; i < server->clients.size(); i++)
        {
            if (server->clients[i] != sender)
                server->clients[i]->message(std::string(result + "\n").c_str());
        }
    }
};
#endif
