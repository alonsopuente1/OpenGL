#include "headers/IBO.hpp"

void IBO::Create(unsigned int indices[], int size)
{
    free();
    glGenBuffers(1, &m_IBO);
    Bind();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    Unbind();
}