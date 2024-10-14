#include "Server.h"
#include <iostream>
#include <array>
#include "AESEncryptor.h"
#include <thread>

Server::Server(boost::asio::io_context& io_context, short port,
    std::shared_ptr<ILogger> logger, std::shared_ptr<ISynchronization> sync,
    std::shared_ptr<IBuffer> buffer, const std::string& storageDir)
    : acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    fileHandler_(storageDir), logger_(logger), sync_(sync), buffer_(buffer)
{
  doAccept();
  decryptor_ = std::make_shared<AESEncryptor>();
}

void Server::doAccept() 
{
    acceptor_.async_accept([this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) 
        {
        if (!ec) 
        {
            std::thread(&Server::handleRequest, this, std::move(socket)).detach();
        }
        doAccept();
        });
}

void Server::handleRequest(boost::asio::ip::tcp::socket socket) 
{
    try 
    {
        logger_->log("Connection accepted.");

        sync_->lock();

        std::array<char, 256> bufferArray;
        boost::system::error_code error;

        size_t len = socket.read_some(boost::asio::buffer(bufferArray), error);
        std::string clientID(bufferArray.data(), len);

        len = socket.read_some(boost::asio::buffer(bufferArray), error);
        std::string filename(bufferArray.data(), len);

        std::string uniqueFilename = fileHandler_.generateUniqueFilename(filename, clientID);

        auto fileData = decryptor_->decrypt(buffer_->read());

        while ((len = socket.read_some(boost::asio::buffer(bufferArray), error)) > 0)
        {
            fileData.insert(fileData.end(), bufferArray.data(), bufferArray.data() + len);
        }

        fileHandler_.saveFile(uniqueFilename, fileData);

        sync_->unlock();
        sync_->notify();

        logger_->log("File saved: " + uniqueFilename);
    }
    catch (std::exception& e)
    {
        logger_->log("Error handling request: " + std::string(e.what()));
    }
}
