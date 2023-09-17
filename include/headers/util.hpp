#ifndef UTIL_HPP
#define UTIL_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>

/// @brief The callback function for GLFW. Not to be used for anything else
void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

/// @brief Reads entire file into one std::string.
/// @param filePath The file path to file to read from.
/// @return Entire file in one string, or empty on error.
std::string ReadFile(const char* filePath);

/// @brief Returns file extension of file path passed in
/// @param path File path to find the extension of
/// @return File extension or "" if it couldn't be found
std::string GetFileExt(const std::string& path);

#endif