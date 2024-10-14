#pragma once

#include "ILogger.h"
#include "ISynchronization.h"
#include "IBuffer.h"
#include <boost/asio.hpp>
#include <string>
#include <vector>

class Client 
{
public:
    Client(boost::asio::io_context& io_context, const std::string& server, short port, std::shared_ptr<ILogger> logger, std::shared_ptr<ISynchronization> sync, std::shared_ptr<IBuffer> buffer);
    void sendFile(const std::string& clientID, const std::string& filePath);

private:
    boost::asio::ip::tcp::socket socket_;
    std::shared_ptr<ILogger> logger_;
    std::shared_ptr<ISynchronization> sync_;
    std::shared_ptr<IBuffer> buffer_;
};
