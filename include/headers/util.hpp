/*

util.hpp

Defines all the random functions that might be needed for some functions
Also has the includes for GLFW and GLAD as well as common STD files to keep
from including them over and over and over and over......

*/

// header guard
#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/// @brief The callback function for GLFW. Not to be used for anything else
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

/// @brief Reads entire file into one std::string.
/// @param filePath The file path to file to read from.
/// @return Entire file in one string, or empty on error.
std::string ReadFile(const char* filePath);

/// @brief Returns file extension of file path passed in
/// @param path File path to find the extension of
/// @return File extension or "" if it couldn't be found
std::string GetFileExt(const std::string& path);

/// @brief Initialises GLFW only
bool InitGLFW();

/// @brief Initalises OpenGL only. Can only be called after making a window the current context in GLFW.
bool InitOpenGL();

#endif