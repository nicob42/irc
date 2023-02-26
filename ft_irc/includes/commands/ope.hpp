#ifndef OPE_H
#define OPE_H

#include "../Command.hpp"

class Ope : public Command  // Classe ope hérite de la classe Command
{
  public:
    // Constructeur de la classe ope
    Ope()
    {
        name = "ope"; // Nom de la commande
        description = "Give operator role to yourself or a client"; // Description de la commande
        usage = "ope <nikname?>"; // Usage de la commande
        example[0] = "ope"; // Exemple d'utilisation de la commande
        example[1] = "ope Faerris"; // Exemple d'utilisation de la commande avec un argument
        ope_required = false; // Indique si l'utilisateur qui exécute la commande est déjà un opérateur ou non
    }

    void execute()
    {
        if (message->getParams().size() == 0) // Si aucun argument n'est fourni
        {
            sender->ope_required = !sender->ope_required; // Inverse le statut d'opérateur de l'utilisateur qui exécute la commande
            sender->message(sender->ope_required ? "Congrats, you're now operator!\n" : "Unfortunately you have been demoted soldier\n"); // Envoie un message à l'utilisateur pour confirmer ou annuler son statut d'opérateur
        }
        else if (message->getParams().size() > 1) // Si trop d'arguments sont fournis
        {
            sender->message("Wrong usage, use it this way : ope <nikname?>\n"); // Envoie un message d'erreur à l'utilisateur
        }
        else // Si un argument est fourni
        {
            Client *client;
            if ((client = server->getClient(message->getParams()[0]))) // Recherche le client correspondant au pseudonyme fourni
            {
                client->ope_required = !client->ope_required; // Inverse le statut d'opérateur du client
                sender->message(std::string(client->ope_required ?
                                                 "Currently the client " + client->nick + " is an operator!\n" :
                                                 "Currently the client " + client->nick + " isn't an operator!\n")
                                     .c_str()); // Envoie un message à l'utilisateur pour confirmer le statut d'opérateur du client
                client->message(
                    std::string(client->ope_required ? "Congrats you're an operator!\n" : "Unfortunately you aren't an operator!\n")
                        .c_str()); // Envoie un message au client pour confirmer son nouveau statut d'opérateur
                return;
            }
            else
                sender->message("Client not found!\n"); // Si aucun client ne correspond au pseudonyme fourni, envoie un message d'erreur à l'utilisateur
        }
    }
};

#endif
