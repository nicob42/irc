#ifndef EXIT_H
#define EXIT_H

#include "../Command.hpp"

class Exit : public Command // Classe Exit hérite de la classe Command
{
  public:
  // Constructeur
    Exit()
    {
        // On définit les informations concernant la commande
        name = "exit";
        description = "Disconnect from the IRC server";
        usage = "exit";
        example[0] = "exit";
    }

    void execute()
    {
        // On supprime le client qui a envoyé la commande de la liste des clients
        delete server->clients[sender_index];
        server->clients.erase(server->clients.begin() + sender_index);

        // On supprime le descripteur de fichier associé au client de la liste des descripteurs de fichiers
        server->fd.erase(server->fd.begin() + sender_index + 1);
    }
};
#endif
