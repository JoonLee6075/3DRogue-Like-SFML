#pragma once

#include <string>

#include <SFML/Graphics.hpp>

class FileManager
{
public:
    // Constructor to initialize the path to resources
    FileManager();

    // Load font from the resources folder
    bool loadFont(sf::Font& font, const std::string& filename);

    // Function to get the base path to the executable
    std::string getExecutablePath() const;

    // Function to combine the base path with the resources folder path
    std::string getResourcePath(const std::string& filename) const;

private:
    std::string basePath;
};