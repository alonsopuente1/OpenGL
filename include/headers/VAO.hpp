/*

VAO.hpp

Defines a class to make dealing with OpenGL Vertex Array Objects easier

*/

// header guard
#ifndef VAO_H
#define VAO_H

#include "headers/util.hpp"
#include "headers/error.hpp"

class VAO
{
public:
    // No constructor is needed
    VAO() {}

    // Deletes the OpenGL VAO object
    ~VAO()
    {
        free();
    }

    /// @brief Makes the VAO
    inline void Create()
    {
        free();
        GLCall(glGenVertexArrays(1, &m_VAO));
    }

    /// @brief Binds the VAO to make it active in OpenGL
    void Bind() const;
    

    /// @brief Unbinds the VAO
    static inline void Unbind()
    {
        glBindVertexArray(0);
    }

    /// @brief Deletes the OpenGL VAO object to free video memory
    inline void free() { GLCall(glDeleteVertexArrays(1, &m_VAO)); }
private:
    // Stores the OpenGL reference ID to the Vertex Array Object
    unsigned int m_VAO = 0;

};

#endif