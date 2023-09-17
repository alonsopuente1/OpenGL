#ifndef MODEL_H
#define MODEL_H

#include "headers/VAO.hpp"
#include "headers/VBO.hpp"
#include "headers/IBO.hpp"
#include "headers/Vertex.hpp"
#include "headers/texture.hpp"
#include "headers/error.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Model
{

public:
    Model(Vertex* vertices, const int& v_size, const bool& use_indices, unsigned int* indices, const int& i_size, const char* texture_path)
    : m_using_indices(use_indices), m_num_indices(i_size / sizeof(unsigned int)), m_num_vertices(v_size / sizeof(Vertex)), m_texture(texture_path)
    {
        m_vao.Create();
        m_vbo.Create(vertices, v_size);

        if(m_using_indices)
        {
            m_ibo.Create(indices, i_size);
        }

        m_vao.Bind();
        m_vbo.Bind();

        if(m_using_indices)
        {
            m_ibo.Bind();
        }

        m_vao.Unbind();

        m_vbo.Unbind();
        m_ibo.Unbind();
    }

    inline glm::vec3 GetPos() const { return m_pos; }
    inline void SetPos(const glm::vec3& new_pos) { memcpy(&m_pos, &new_pos, sizeof(new_pos)); }

    inline glm::mat4 GetModelMat() { return glm::translate(glm::mat4(1.0f), m_pos); }

    void Draw();
    

private:
    VAO m_vao;
    VBO m_vbo;
    IBO m_ibo;

    glm::vec3 m_pos;

    Texture m_texture;

    const unsigned int m_num_vertices;
    const unsigned int m_num_indices;
    const bool m_using_indices;
};

#endif