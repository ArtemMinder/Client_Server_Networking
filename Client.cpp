#include "Client.h"
#include <fstream>
#include "AESEncryptor.h"
#include <iostream>

Client::Client(boost::asio::io_context& io_context, const std::string& server,
    short port, std::shared_ptr<ILogger> logger, std::shared_ptr<ISynchronization> 
    sync, std::shared_ptr<IBuffer> buffer)
    : socket_(io_context), logger_(logger), sync_(sync), buffer_(buffer) 
{
    boost::asio::ip::tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(server, std::to_string(port));
    boost::asio::connect(socket_, endpoints);
    encryptor_ = std::make_shared<AESEncryptor>();
}

void Client::sendFile(const std::string& clientID, const std::string& filePath)
{
    try 
    {
        logger_->log("Sending file: " + filePath);

        sync_->lock();

        boost::asio::write(socket_, boost::asio::buffer(clientID));
        boost::asio::write(socket_, boost::asio::buffer(filePath));

        std::ifstream file(filePath, std::ios::binary);
        if (!file.is_open()) 
        {
            throw std::runtime_error("Unable to open file: " + filePath);
        }

        std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        auto encryptedData = encryptor_->encrypt(buffer);
        buffer_->write(encryptedData);

        auto fileData = buffer_->read();

        boost::asio::write(socket_, boost::asio::buffer(fileData.data(), fileData.size()));

        sync_->unlock();

        logger_->log("File sent: " + filePath);
    }
    catch (std::exception& e) 
    {
        logger_->log("Error sending file: " + std::string(e.what()));
    }
}
