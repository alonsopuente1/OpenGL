#include "headers/VBO.hpp"
#include "headers/Vertex.hpp"

void VBO::Create(Vertex vertices[], int size)
{
    free();
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);


    Unbind();
}

void VBO::Bind()
{
    // bind buffer and set vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    // location = 0, position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // location = 1, colour attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    
    // location = 2, tex coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);
}

void VBO::free()
{
    glDeleteBuffers(1, &m_VBO);
}