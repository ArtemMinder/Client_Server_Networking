#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include "Client.h"
#include "Server.h"
#include "Buffer.h"
#include "Synchronization.h"
#include "ConsoleLogger.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <mode> <port> [<files...>]" << std::endl;
        return 1;
    }

    std::string mode = argv[1];
    short port = std::atoi(argv[2]);

    boost::asio::io_context io_context;
    auto buffer = std::make_shared<Buffer>();
    auto sync = std::make_shared<Synchronization>();
    auto logger = std::make_shared<ConsoleLogger>();

    try
    {
        if (mode == "server")
        {
            std::string storageDir = "server_storage";
            Server server(io_context, port, logger, sync, buffer, storageDir);
            io_context.run();
        }
        else if (mode == "client")
        {
            if (argc < 4)
            {
                std::cerr << "Usage: " << argv[0] << " client <port> <files...>" << std::endl;
                return 1;
            }

            std::string clientID = "client1";
            Client client(io_context, "localhost", port, logger, sync, buffer);

            for (int i = 3; i < argc; ++i)
            {
                std::string filePath = argv[i];
                client.sendFile(clientID, filePath);
            }
        }
        else
        {
            std::cerr << "Unknown mode: " << mode << std::endl;
            return 1;
        }
    }
    catch (std::exception& e)
    {
        logger->log("Exception: " + std::string(e.what()));
    }

    return 0;
}