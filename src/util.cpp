#include "headers/util.hpp"
#include "headers/logger.hpp"

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

std::string ReadFile(const char* filePath)
{

    std::fstream file(filePath);

    if(!file.is_open())
    {
        Logger::Error("Could not open file at %s", filePath);
        return "";
    }

    std::stringstream stream;

    stream << file.rdbuf();

    file.close();
    
    std::string string = stream.str();

    return string;
}

std::string GetFileExt(const std::string& path)
{
    int i;
    for(i = path.size() - 1; i >= 0; i--)
        if(path.at(i) == '.')
            goto return_val;

    Logger::Warn("Could find file extension of %s", path.c_str());
    return "";

return_val:
    return path.substr(i, path.size() - i);
}
