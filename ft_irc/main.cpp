#include "includes/Server.hpp"

int main(int argc, char **argv)
{
    Server *server;
    std::vector<std::string> args;

    // Store the command line arguments in a vector with std::string
    for (int i = 0; i < argc; i++)
    {
        args.push_back(argv[i]);
    }

    // Validate the command line arguments
    if (!validate_args(argc, argv))
    {
        return 1;
    }

    try
    {
        // Create a new Server object with the host address, port, and password
        server = new Server("0.0.0.0", args[1], args[2]);

        // Delete the Server object
        delete server;
    }
    catch (const std::exception &e)
    {
        // Print any errors that occur
        std::cerr << e.what() << '\n';
    }

    return 0;
}