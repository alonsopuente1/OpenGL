#ifndef VBO_H
#define VBO_H

#include "headers/util.hpp"

struct Vertex;

class VBO
{
public:
    VBO() {}

    ~VBO()
    {
        free();
    }

    void Create(Vertex vertices[], int size);

    void Bind();

    static inline void Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

private:
    unsigned int m_VBO = 0;

    int m_size = 0;

    void free();
};

#endif