#include "FileManager.h"
#include <filesystem>
#include <iostream>

// Constructor to initialize the base path (directory of the executable)
FileManager::FileManager()
{
    this->basePath = std::filesystem::current_path().string();
    
}

// Function to load a font from the resources folder
bool FileManager::loadFont(sf::Font& font, const std::string& filename)
{
    std::string fullPath = getResourcePath(filename);

    if (!font.loadFromFile(fullPath))
    {
        std::cout << "Error loading font from: " << fullPath << std::endl;
        return false;
    }

    return true;
}

// Function to get the base path (location of the executable)
std::string FileManager::getExecutablePath() const
{
    return this->basePath;
}

// Combine the base path and the given filename to form a full resource path
std::string FileManager::getResourcePath(const std::string& filename) const
{
    return this->basePath + "/resources/" + filename;
}
