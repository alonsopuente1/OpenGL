#include "headers/VBO.hpp"

#include "headers/Vertex.hpp"
#include "headers/logger.hpp"

void VBO::Create(Vertex vertices[], int size)
{
    // Delete any existing VBO and make new ones
    free();
    GLCall(glGenBuffers(1, &m_VBO));

    // Bind the new VBO
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));

    // Fill it with data provided
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));

    // Finally unbind
    Unbind();
}

void VBO::Bind() const
{
    // Check if VBO exists first before binding it. If it doesn't exist
    // tell user to create it first THEN bind it
    if(m_VBO == 0)
    {
        Logger::Warn("Cannot bind VBO as it doesn't exist!");
        return;
    }

    // bind buffer and set vertex attributes
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));

    // location = 0, position attribute
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));
    GLCall(glEnableVertexAttribArray(0));

    // location = 1, colour attribute
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3)));
    GLCall(glEnableVertexAttribArray(1));
    

    // location = 2, tex coord attribute
    GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 6)));
    GLCall(glEnableVertexAttribArray(2));
}
