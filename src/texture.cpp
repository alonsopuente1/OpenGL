#include "headers/texture.hpp"

#include "headers/error.hpp"
#include "headers/util.hpp"
#include "headers/logger.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

void Texture::Bind(int texture_unit) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + texture_unit));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_texture));
}

void Texture::LoadTexture(const std::string& file_path)
{
    free();
    GLCall(glGenTextures(1, &m_texture));
    Bind(0);

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));	
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    
    int channels;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* img = stbi_load(file_path.c_str(), &m_width, &m_height, &channels, 0);

    if(img)
    {
        if(GetFileExt(file_path) == ".jpg")
        {
            Logger::Debug("Loading %s texture as jpg", file_path.c_str());
            GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img));
            GLCall(glGenerateMipmap(GL_TEXTURE_2D));
            goto exit;
        }
        else
        {
            Logger::Warn("Image format not supported");
        }
    }

    Logger::Warn("Failed to load texture %s. Loading default texture instead...", file_path.c_str());
    LoadDefault();

exit:

    Unbind();
    if(img)
        delete img;
}

void Texture::LoadDefault()
{
    free();
    GLCall(glGenTextures(1, &m_texture));
    Bind(0);

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));	
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    
    int channels;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* img = stbi_load("../res/textures/default.jpg", &m_width, &m_height, &channels, 0);

    /* if the image doesnt exist, that means stbi could not 
     open the default texture img, which means something is 
     very wrong */
    assert(img);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);

    delete img;

    Unbind();
}

void Texture::free()
{
    GLCall(glDeleteTextures(1, &m_texture));
}
