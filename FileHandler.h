#pragma once

#include <string>
#include <vector>

class FileHandler 
{
public:
    FileHandler(const std::string& storageDir);
    void saveFile(const std::string& filename, const std::vector<char>& data);
    std::string generateUniqueFilename(const std::string& filename, const std::string& clientID);

private:
    std::string storageDir_;
};
