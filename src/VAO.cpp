#include "headers/VAO.hpp"

#include "headers/logger.hpp"

void VAO::Bind() const
{   
    // Check if IBO exists first before binding it. If it doesn't exist
    // tell user to create it first THEN bind it
    if(m_VAO == 0)
    {
        Logger::Warn("Cannot bind VAO as it doesn't exist!");
        return;
    }
    GLCall(glBindVertexArray(m_VAO));
}