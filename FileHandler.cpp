#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

FileHandler::FileHandler(const std::string& storageDir) : storageDir_(storageDir) {}

void FileHandler::saveFile(const std::string& filename, const std::vector<char>& data) 
{
    std::ofstream file(storageDir_ + "/" + filename, std::ios::binary);
    if (!file) 
    {
        throw std::runtime_error("Unable to open file: " + filename);
    }
    file.write(data.data(), data.size());
}

std::string FileHandler::generateUniqueFilename(const std::string& filename, const std::string& clientID)
{
    std::stringstream ss;
    ss << clientID << "_" << filename << ".txt";
    return ss.str();
}
