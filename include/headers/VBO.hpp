/*

VBO.hpp

Defines a class to make dealing with OpenGL Vertex Buffer Objects easier

*/

// header guard
#ifndef VBO_H
#define VBO_H

#include "headers/util.hpp"
#include "headers/error.hpp"

// This is defined in 'include/headers/vertex.hpp'
struct Vertex;

class VBO
{
public:
    VBO() {}

    ~VBO()
    {
        free();
    }

    /// @brief Makes the OpenGL Vertex Buffer Object and fills it with vertices
    /// @param vertices Array of Vertex objects to push to OpenGL
    /// @param size Size of the array in bytes (use sizeof() function)
    void Create(Vertex vertices[], int size);

    /// @brief Binds this VBO to make it active in OpenGL
    void Bind() const;

    /// @brief Unbinds the VBO
    static inline void Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    /// @brief Deletes the OpenGL VBO to free video memory
    inline void free() { GLCall(glDeleteBuffers(1, &m_VBO)); }
private:
    // Stores the reference ID to the OpenGL Vertex Buffer Object
    unsigned int m_VBO = 0;

};

#endif