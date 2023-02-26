#ifndef HELP_H
#define HELP_H

#include "../Color.hpp"  // Inclusion de la classe Color pour afficher des couleurs dans le terminal
#include "../Command.hpp"  // Inclusion de la classe Command dont la classe Help hérite

class Help : public Command // Classe Help hérite de la classe Command
{
  public:
    // Constructeur de la classe Help
    Help()
    {
        name = "help";  // Nom de la commande
        description = "Show you a guide about usage of all command";  // Description de la commande
        usage = "help <command?>";  // Utilisation de la commande
        example[0] = "help";  // Exemple d'utilisation de la commande
        example[1] = "help ping";  // Exemple d'utilisation de la commande avec un argument
    }

    // Méthode qui est exécutée lorsqu'on utilise la commande Help
    void execute() 
    {
        std::string result = "";  // Variable qui va stocker le résultat de l'exécution de la commande
        bool filter = false;  // Booléen qui va déterminer si on filtre les résultats de la commande en fonction d'un argument
        std::map<std::string, Command *>::iterator it = server->commands.begin();  // Itérateur qui va parcourir toutes les commandes du serveur
        std::map<size_t, std::string> params = message->getParams();  // Récupération des arguments passés avec la commande Help

        result = std::string(C_U) + std::string(C_BOLD) + std::string(C_GREEN) + "Commands usage guide" + std::string(C_X) + "\n";  // Ajout d'un titre en vert gras souligné au résultat

        if (params.size() == 1 && server->commands.count(params[0]))  // Si un argument a été passé avec la commande, on filtre les résultats
            filter = true;

        for (; it != server->commands.end(); it++)  // On parcourt toutes les commandes du serveur
        {
            if (filter && it->second->getName() != params[0])  // Si on filtre les résultats et que la commande actuelle ne correspond pas à l'argument passé, on continue
                continue;

            result += std::string("Command: " + it->second->getName() +  // Ajout du nom de la commande
                                   "\n\t Description: " + it->second->getDescription() +  // Ajout de la description de la commande
                                   "\n\t Usage: " + it->second->getUsage() + "\n\t Example:\n");  // Ajout de l'utilisation de la commande et d'une ligne pour les exemples

            std::map<size_t, std::string> example(it->second->getExample());  // Récupération des exemples de la commande actuelle
            std::map<size_t, std::string>::iterator it_ex = example.begin();  // Itérateur qui va parcourir tous les exemples
            for (; it_ex != example.end(); it_ex++)  // On parcourt tous les exemples
                result += std::string("\t\t" + it_ex->second + "\n");  // Ajout de l'exemple

            result += "\n";  // Ajout d'une ligne vide à la fin de chaque commande
        }

        sender->message(result.c_str());  // Envoi du résultat de la commande au client
    }
};
#endif 
