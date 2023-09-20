#include "headers/util.hpp"
#include "headers/logger.hpp"

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // Resizes viewport to the new width and height of the window
    glViewport(0, 0, width, height);
}

std::string ReadFile(const char* filePath)
{
    // Open the file
    std::fstream file(filePath);

    // If the file fails to open display error and return empty string
    if(!file.is_open())
    {
        Logger::Error("Could not open file at %s", filePath);
        return "";
    }

    // Else create a string stream
    std::stringstream stream;

    // Read entire file into string stream
    stream << file.rdbuf();

    // Close the file
    file.close();
    
    // Store string variant of string stream into variable and return that
    std::string string = stream.str();
    return string;
}

std::string GetFileExt(const std::string& path)
{
    // Keep the index because we want to remember the index where the full stop is
    int i;
    for(i = path.size() - 1; i >= 0; i--)
        if(path.at(i) == '.')
            goto return_val;

    // If it couldn't find the full stop, it couldn't find the file extension
    Logger::Warn("Couldn't find file extension of %s", path.c_str());
    return "";

return_val:
    // Else return the file extension
    return path.substr(i, path.size() - i);
}

bool InitGLFW()
{
    // Tell GLFW that the OpenGL version we're using is 4.6 and we are using modern OpenGL (core)
    glfwInitHint(GLFW_VERSION_MAJOR, 4);
    glfwInitHint(GLFW_VERSION_MINOR, 6);
    glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // If GLFW doesn't initialise then display error and return false
    if(!glfwInit())
    {
        const char* x;
        glfwGetError(&x);
        Logger::Error("Failed to initialise GLFW. GLFW Error: %s", x);
        return false;
    }

    return true;
}

bool InitOpenGL()
{
    // Load OpenGL functions here. If this evaluates to false, OpenGL failed to init
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logger::Error("Failed to load OpenGL.");
        return false;
    }

    // Else let the user know that it initialised with the OpenGL version it has loaded in the console
    Logger::Info("OpenGL version: %s", glGetString(GL_VERSION));

    return true;
}
