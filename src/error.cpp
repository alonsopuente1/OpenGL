#include "headers/error.hpp"
#include "headers/util.hpp"

void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

void GLLogCall(const char* function, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        Logger::Warn("OpenGL Error (%x): Function %s in file %s on line %i", error, function, file, line);
    }
}