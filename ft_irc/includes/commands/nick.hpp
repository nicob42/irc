#ifndef NICK_H
#define NICK_H

#include "../Command.hpp"

class Nick : public Command // Classe Nick hérite de la classe Command
{
  public:
    // Constructeur de la classe Nick
    Nick()
    {
        // Initialisation des attributs de la commande
        name = "Nick";
        description = "adssa";
        usage = "Nick";
        example = "Nick";
    }

    // Méthode exécutée lorsque la commande est appelée
    void execute(std::string name)
    {
        sender->name = name;
    }
};
#endif
