#ifndef PING_H
#define PING_H

#include "../Command.hpp"

class Ping : public Command // Définition de la classe Ping, qui hérite de Command
{
  public:
    // Constructeur de la classe
    Ping()
    {
        // Initialise les informations de la commande
        name = "ping"; // Nom de la commande
        description = "Determine server status"; // Description de la commande
        usage = "ping"; // Utilisation de la commande
        example[0] = "ping"; // Exemple d'utilisation de la commande
    }

    // Méthode appelée lors de l'exécution de la commande
    void execute()
    {
        sender->message("pong\n"); // Envoie un message "pong" au client exécutant la commande
    }
};

#endif
