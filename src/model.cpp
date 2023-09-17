#include "headers/model.hpp"

void Model::Draw()
{
    m_vao.Bind();

    m_texture.Bind(0);

    if(m_using_indices)
    {
        GLCall(glDrawElements(GL_TRIANGLES, m_num_indices, GL_UNSIGNED_INT, (void*)0));
    }
    else
    {
        GLCall(glDrawArrays(GL_TRIANGLES, 0, m_num_vertices));
    }

    m_vao.Unbind();
}