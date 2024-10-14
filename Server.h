#pragma once

#include "FileHandler.h"
#include "ILogger.h"
#include "ISynchronization.h"
#include "IBuffer.h"
#include <boost/asio.hpp>

class Server 
{
public:
    Server(boost::asio::io_context& io_context, short port,
        std::shared_ptr<ILogger> logger, std::shared_ptr<ISynchronization> sync,
        std::shared_ptr<IBuffer> buffer, const std::string& storageDir);
private:
    void doAccept();
    void handleRequest(boost::asio::ip::tcp::socket socket);

    boost::asio::ip::tcp::acceptor acceptor_;
    FileHandler fileHandler_;
    std::shared_ptr<ILogger> logger_;
    std::shared_ptr<ISynchronization> sync_;
    std::shared_ptr<IBuffer> buffer_;
};
