#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "headers/util.hpp"
#include "headers/error.hpp"
#include "headers/logger.hpp"

class Texture
{

public:
    Texture() {}

    Texture(const std::string& file_path)
    {
        LoadTexture(file_path);
    }

    ~Texture()
    {
        free();
    }

    void Bind(int texture_unit) const;

    void LoadTexture(const std::string& file_path);
    void LoadDefault();

    static void Unbind()
    {
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }

    inline int GetWidth() const
    {
        return m_width;
    }

    inline int GetHeight() const
    {
        return m_height;
    }

private:
    unsigned int m_texture = 0;

    int m_width;
    int m_height;

    void free();
};

#endif