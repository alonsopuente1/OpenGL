/*

IBO.hpp

Defines a class to make dealing with OpenGL Index Buffer Objects easier

*/

// header guard
#ifndef IBO_H
#define IBO_H

#include "headers/util.hpp"
#include "headers/error.hpp"

class IBO
{
public:
    IBO() {}

    ~IBO()
    {
        free();
    }

    /// @brief Creates the OpenGL Index Buffer Object
    /// @param indices Indices array to push to the object
    /// @param size Size of the array in bytes (use sizeof() function)
    void Create(unsigned int* indices, int size);

    /// @brief Binds the IBO to make it active in OpenGL
    void Bind() const;

    /// @brief Unbinds the IBO
    static inline void Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    /// @brief Deletes the OpenGL object to free video memory
    inline void free() { GLCall(glDeleteBuffers(1, &m_IBO)); }
    unsigned int m_IBO = 0;
private:
    // Stores the OpenGL reference ID to the Index Buffer Object

};

#endif
