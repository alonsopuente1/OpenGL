#include "headers/texture.hpp"

#include "headers/error.hpp"
#include "headers/util.hpp"
#include "headers/logger.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

void Texture::Bind(int texture_unit) const
{
    // If texture doesn't exist and you're trying to bind it, let user know it doesn't exist
    if(m_texture == 0)
    {
        Logger::Warn("Cannot bind texture as texture has not been loaded!");
        return;
    }

    // Otherwise just bind normally
    GLCall(glActiveTexture(GL_TEXTURE0 + texture_unit));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_texture));
}

void Texture::LoadTexture(const std::string& file_path)
{
    // Delete any pre-existing textures
    free();

    // Make new texture and bind it for future texture function calls to be done on this object
    GLCall(glGenTextures(1, &m_texture));
    Bind(0);

    // Configure how the texture should display, (nearest or linear interpolation) and wrap around
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));	
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    // Necessary variable to call stbi_load() function, not actually used though    
    int channels;

    // OpenGL reads image from bottom to top, whereas stbi reads them from top to bottom, so we need to flip the image vertically
    stbi_set_flip_vertically_on_load(true);

    // The raw data to the image
    unsigned char* img = stbi_load(file_path.c_str(), &m_width, &m_height, &channels, 0);

    // If the image exists, check the file extension of the image to load differently depending on file extension
    if(img)
    {
        // JPG's format is RGB so load it that way into OpenGL
        if(GetFileExt(file_path) == ".jpg")
        {
            // Let user know we are loading the texture in.
            Logger::Debug("Loading %s texture as jpg", file_path.c_str());
            GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img));
            GLCall(glGenerateMipmap(GL_TEXTURE_2D));

            // Goto exit saves me from having to create a flag to know whether creating the texture was successful
            // and checking if its true at the end. Only one label used so code is still readable
            goto exit;
        }
        // Only JPG's can be loaded for now, will add more in the future if needed
        else
        {
            Logger::Warn("Image format not supported");
        }
    }

    // If the texture was not created, load the default texture instead.
    Logger::Warn("Failed to load texture %s. Loading default texture instead...", file_path.c_str());
    LoadDefault();

exit:
    Unbind();
    if(img)
        delete img;
}

void Texture::LoadDefault()
{
    // Similar to LoadTexture() function except image to load is hardcoded as a default image instead
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
     open the default texture img, which probably means the
     executable is being ran in the wrong location */
    assert(img);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);

    delete img;

    Unbind();
}

void Texture::free()
{
    GLCall(glDeleteTextures(1, &m_texture));
}
