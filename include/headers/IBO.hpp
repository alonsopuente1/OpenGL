#ifndef IBO_H
#define IBO_H

#include "headers/util.hpp"

class IBO
{
public:
    IBO() {}

    /// @brief Creates OpenGL index buffer object
    /// @param indices indices array to push to the object
    /// @param size size of the array in bytes
    void Create(unsigned int indices[], int size);

    inline void Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    }

    static inline void Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
private:
    unsigned int m_IBO = 0;

    void free()
    {
        glDeleteBuffers(1, &m_IBO);
    }
};

#endif
