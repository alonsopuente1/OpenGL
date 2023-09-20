/*

error.hpp

Defines a GLCall() macro which checks and displays any OpenGL errors
Only used in development for debugging

*/

// header guard
#ifndef ERROR_H
#define ERROR_H

#include "headers/settings.hpp"
#include "headers/logger.hpp"

// only if the debug macro is defined should we check for OpenGL errors
#ifdef DEBUG

// Clears all errors first, calls function then checks for errors. If 
// there is an error, print the function name, file and line it was
// called from as well as the OpenGL error code in hexadecimal
#define GLCall(x) GLClearError();\
                  x;\
                  GLLogCall(#x, __FILE__, __LINE__)

#else

#define GLCall(x) x

#endif

/// @brief Clears any OpenGL errors in the queue
void GLClearError();

/// @brief Displays all OpenGL errors in queue
/// @param function Error causing function name
/// @param file The file that the function is being called from
/// @param line The line that its being called from in said file
void GLLogCall(const char* function, const char* file, int line);

#endif