#include "headers/model.hpp"

void Model::Draw() const
{
    // Bind VAO which automatically binds associated VBOs and IBOs if they are used
    // Also holds the attribute layout of the VBO, (position, colour and tex-coord)
    m_texture.Bind(0);
    m_vao.Bind();

    // Bind the current texture for use

    m_ibo.Bind();

    // Depending on if the model uses indices or not then draw differently
    if(m_using_indices)
    {
        GLCall(glDrawElements(GL_TRIANGLES, m_num_indices, GL_UNSIGNED_INT, (void*)0));
    }
    else
    {
        GLCall(glDrawArrays(GL_TRIANGLES, 0, m_num_vertices));
    }

    // Makes sure to unbind VAO to not affect it with any other OpenGL calls we might make afterwards
    m_vao.Unbind();
}