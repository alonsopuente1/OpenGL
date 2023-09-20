#include "headers/IBO.hpp"

#include "headers/logger.hpp"

void IBO::Create(unsigned int* indices, int size)
{
    // Delete any existing IBO and create new one
    free();
    GLCall(glGenBuffers(1, &m_IBO));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));

    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW));
    Unbind();
}

void IBO::Bind() const
{
    // Check if IBO exists first before binding it. If it doesn't exist
    // tell user to create it first THEN bind it
    if(m_IBO == 0)
    {
        Logger::Warn("Cannot bind IBO as it doesn't exist!");
        return;
    }
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
}