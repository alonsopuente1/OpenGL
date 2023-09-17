#ifndef VAO_H
#define VAO_H

#include "headers/util.hpp"

class VAO
{
public:
    VAO() {}
    ~VAO()
    {
        free();
    }

    inline void Create()
    {
        free();
        glGenVertexArrays(1, &m_VAO);
    }

    inline void Bind()
    {
        glBindVertexArray(m_VAO);
    }

    static inline void Unbind()
    {
        glBindVertexArray(0);
    }

private:
    unsigned int m_VAO = 0;

    void free()
    {
        glDeleteVertexArrays(1, &m_VAO);
    }
};

#endif