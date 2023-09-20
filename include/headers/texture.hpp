/*

texture.hpp

Texture class to make dealing with textures in OpenGL easier

*/

// header guards
#ifndef TEXTURE_H
#define TEXTURE_H

// necessary includes
#include <string>
#include "headers/util.hpp"
#include "headers/error.hpp"
#include "headers/logger.hpp"

class Texture
{

public:
    /// @brief Doesn't do anything
    Texture() {}

    /// @brief Loads texture provided. Useful for making a texture in one line insted of two
    /// @param file_path File path to image. Can only support '.jpg' images for now
    Texture(const std::string& file_path)
    {
        LoadTexture(file_path);
    }

    Texture(const Texture& other)
    : m_texture(other.m_texture),
      m_width(other.m_width),
      m_height(other.m_height) {}

    // frees the OpenGL texture object
    ~Texture()
    {
        free();
    }

    /// @brief Binds this texture only if the OpenGL texture object has been made
    /// @param texture_unit The OpenGL texture unit to bind this texture object to
    void Bind(int texture_unit) const;

    /// @brief Loads a texture in given the file path to an image
    /// @param file_path File path to image. Can only support '.jpg' images for now
    void LoadTexture(const std::string& file_path);

    /// @brief Loads the default texture found in 'res/textures/'
    void LoadDefault();

    /// @brief Unbinds the texture
    static void Unbind()
    {
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }

    /// @return The width of the texture
    inline int GetWidth() const
    {
        return m_width;
    }

    /// @return The height of the texture
    inline int GetHeight() const
    {
        return m_height;
    }

private:
    // variable to store the reference ID to the OpenGL texture object
    unsigned int m_texture = 0;

    // stores the width and height of the texture object loaded in
    int m_width;
    int m_height;

    /// @brief Deletes the OpenGL texture object
    void free();
};

#endif