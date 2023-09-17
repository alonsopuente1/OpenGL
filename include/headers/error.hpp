#ifndef ERROR_H
#define ERROR_H

#include "headers/settings.hpp"
#include "headers/logger.hpp"

#ifdef DEBUG

#define GLCall(x) GLClearError();\
                  x;\
                  GLLogCall(#x, __FILE__, __LINE__)

#else

#define GLCall(x) x

#endif

void GLClearError();

void GLLogCall(const char* function, const char* file, int line);

#endif