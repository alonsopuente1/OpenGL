/*

model.hpp

Defines a model class to make it easy to draw 3D models
I will implement a way to load .obj files soon

*/

// header guard
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
    /// @brief Creates a 3D model given some vertices, optionally some indices and optionally a texture
    /// @param vertices The array of vertices to define the model
    /// @param v_size The size of the array of vertices in bytes (use sizeof() function)
    /// @param use_indices If this value is false, the model will be rendered using every three vertices in the vertex array to define a triangle. Otherwise it uses every 3 indices to define a triangle
    /// @param indices (Optional) The array of indices. It is safe to pass nullptr to this if use_indices is false
    /// @param i_size (Optional) The size of the array of indices (use sizeof() function)
    /// @param texture_path (Optional) The path to the texture of the model. If an empty string is passed here, the console will display an error but it will use the default texture
    Model(Vertex* vertices, const int& v_size, const bool& use_indices, unsigned int* indices, const int& i_size, const char* texture_path)
    : m_using_indices(use_indices), 
      m_num_indices(i_size / sizeof(unsigned int)), 
      m_num_vertices(v_size / sizeof(Vertex)), 
      m_texture(texture_path)
    {
        m_vao.Create();
        m_vao.Bind();
        m_vbo.Create(vertices, v_size);

        if(use_indices)
        {
            m_ibo.Create(indices, i_size);
        }

        m_vbo.Bind();

        if(use_indices)
        {
            m_ibo.Bind();
        }

        m_vao.Unbind();

        m_vbo.Unbind();
        m_ibo.Unbind();
    }

    /// @brief Copy constructor
    /// @param other The model to copy
    Model(const Model& other)
    : m_vao(other.m_vao),
      m_vbo(other.m_vbo),
      m_ibo(other.m_ibo),
      m_pos(other.m_pos),
      m_texture(other.m_texture),
      m_num_vertices(other.m_num_vertices),
      m_num_indices(other.m_num_indices),
      m_using_indices(other.m_using_indices)
    {
        
    }

    /// @brief Copy assignment operator
    /// @param other The model to copy
    Model& operator=(const Model& other)
    {
        if(this == &other)
            return *this;

        m_vao = other.m_vao;
        m_vbo = other.m_vbo;
        m_ibo = other.m_ibo; 
        m_pos = other.m_pos; 
        m_texture = other.m_texture;
        m_num_vertices = other.m_num_vertices;
        m_num_indices = other.m_num_indices;
        m_using_indices = other.m_using_indices;
    }

    /// @brief Destructs this model's resources
    ~Model()
    {
        free();
    }

    /// @brief Gets the position of the model
    /// @return Position of model;
    inline glm::vec3 GetPos() const { return m_pos; }

    /// @brief Sets the position of the model to the position passed in the parameter
    /// @param new_pos Position to set the model to
    inline void SetPos(const glm::vec3& new_pos) { memcpy(&m_pos, &new_pos, sizeof(new_pos)); }

    /// @brief Gets the model matrix of this model to be used in the shader
    /// @return Model matrix of this model
    inline glm::mat4 GetModelMat() const { return glm::translate(glm::mat4(1.0f), m_pos); }

    /// @brief Draws the model onto the screen. Does it differently depending on if the model uses indices or not
    void Draw() const;

    /// @brief Frees all the resources used by the model
    inline void free() { m_vao.free(); m_vao.free(); m_ibo.free(); }
    

private:
    // Stores the attrib pointers and VBO + IBO bind calls
    VAO m_vao;
    // Stores the vertex data of this model
    VBO m_vbo;
    // If the model uses indices, this stores the indices 
    // of the model with every 3 defining a triangle
    IBO m_ibo;

    // The position of this model
    glm::vec3 m_pos;

    // The texture for this model
    Texture m_texture;

    // Number of vertices in the model. Needed to know for glDrawArrays() function
    unsigned int m_num_vertices;

    // The number of indices (if used). Need to know for glDrawElements() call
    unsigned int m_num_indices;

    // Stores if the model uses indices. Need to know for drawing with either glDrawArrays() or glDrawElements()
    bool m_using_indices;
};

#endif