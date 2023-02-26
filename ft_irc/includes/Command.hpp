#ifndef COMMAND_H
#define COMMAND_H

#include "./Server.hpp"

class Command
{
  protected:
    std::string                   name;        // nom de la commande
    std::string                   description; // description de la commande
    std::string                   usage;       // utilisation de la commande
    bool                         ope_required;      // indique si la commande nécessite un opérateur
    bool                          authentif_required;  // indique si l'authentification est nécessaire pour exécuter la commande
    std::map<size_t, std::string> example;     // exemples d'utilisation de la commande

    // membres de données pour stocker des informations sur l'expéditeur de la commande,
    // le serveur sur lequel la commande est exécutée et le message associé à la commande
    Client *sender;
    Server *server;
    Message *message;
    size_t   sender_index;

  public:
    // méthodes pour récupérer les informations sur la commande
    std::string getName() const
    {
        return name;
    };
    std::string getDescription() const
    {
        return description;
    };
    std::string getUsage() const
    {
        return usage;
    };
    std::map<size_t, std::string> getExample() const
    {
        return example;
    };
    // méthodes pour définir les informations sur l'expéditeur de la commande
    Client *getSender() const
    {
        return sender;
    };
    void setSender(Client *sender, size_t index)
    {
        sender = sender;
        sender_index = index;
    };
    // méthode pour définir le serveur sur lequel la commande est exécutée
    void setServer(Server *server)
    {
        server = server;
    };
    // méthode pour définir le message associé à la commande
    void setMessage(Message *message)
    {
        message = message;
    };
    // méthodes pour vérifier si la commande nécessite un opérateur et si l'authentification est nécessaire pour exécuter la commande
    bool hasOpe(void)
    {
        return (ope_required);
    };
    bool needsAuth(void)
    {
        return (authentification_require);
    };

    // méthode virtuelle pure qui doit être implémentée par les classes dérivées pour exécuter la commande
    virtual void execute() = 0;
    // méthode virtuelle qui peut être implémentée par les classes dérivées pour valider les paramètres de la commande
    virtual bool validate(void)
    {
        return (true);
    }
    // constructeur par défaut qui initialise les membres de données à leurs valeurs par défaut
    Command()
        :ope_required(false), authentification_require(true), sender(NULL), server(NULL), message(NULL), sender_index(0){};
    // méthode pour signaler que la commande nécessite un opérateur
    void missingOpe(void)
    {
        // Envoie un message au client pour l'avertir que l'utilisateur
        // n'a pas de rôle d'opérateur pour exécuter cette commande
        sender->message(std::string("Operator role is needed to exec " + name + "\n").c_str());
    };

    // Destructeur virtuel de la classe Command
    virtual ~Command()
    {
        // Affiche un message pour indiquer que le destructeur de la commande a été appelé
        std::cout << "Command " << name << " destructor is called" << std::endl;
    };
);

#endif
