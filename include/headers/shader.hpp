/*

shader.hpp

Defines a shader class that makes it easy to deal with shader programs in OpenGL

*/

// header guard
#ifndef SHADER_H
#define SHADER_H

#include "headers/util.hpp"
#include "headers/error.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Shader
{

public:
    /// @brief Constructor to compile shaders given two files to a vertex and fragment shader (for now). Shaders must be written in GLSL
    /// @param vert_file_path File path to vertex shader
    /// @param frag_file_path File path to fragment shader
    Shader(const char* vert_file_path, const char* frag_file_path)
    {
        // Read the vertex and fragment shader files into one string
        std::string vert_shader_source = ReadFile(vert_file_path);
        std::string frag_shader_source = ReadFile(frag_file_path);

        // Convert them to c-style strings first as OpenGL needs a pointer to a c-style
        // string for one of the arguements 
        const char* p_vert_shader_source = vert_shader_source.c_str();        
        const char* p_frag_shader_source = frag_shader_source.c_str();

        // Declare vertex and fragment shaders now
        unsigned int vert = 0;     // Vertex shader
        unsigned int frag = 0;     // Fragment shader
                char infolog[512]; // Info

        // Create and load the source of the vertex and fragment shaders
        printf("Hello\n");
        GLClearError();
        vert = glCreateShader(GL_VERTEX_SHADER);
        GLLogCall("glCreateShader(GL_VERTEX_SHADER)", __FILE__, __LINE__ - 1);
        GLCall(glShaderSource(vert, 1, &p_vert_shader_source, nullptr));
        frag = glCreateShader(GL_FRAGMENT_SHADER);
        GLLogCall("glCreateShader(GL_FRAGMENT_SHADER)", __FILE__, __LINE__ - 1);
        GLCall(glShaderSource(frag, 1, &p_frag_shader_source, nullptr));

        // Compile the shaders
        GLCall(glCompileShader(vert));
        GLCall(glCompileShader(frag));

        // If vertex shader compilation failed
        if(!CheckShaderCompilation(vert))
        {
            // Log the OpenGL error message that stores why the shader didn't compile successfully
            GLCall(glGetShaderInfoLog(vert, sizeof(infolog), NULL, infolog));
            Logger::Error("Failed to compile vertex shader.\nERROR: %s", infolog);
        
            // Delete the shaders to free memory
            GLCall(glDeleteShader(vert));
            GLCall(glDeleteShader(frag));

            return;
        }

        // If fragment shader compilation failed
        if(!CheckShaderCompilation(frag))
        {
            // Log the OpenGL error message that stores why the shader didn't compile successfully
            GLCall(glGetShaderInfoLog(vert, sizeof(infolog), NULL, infolog));
            Logger::Error("Failed to compile fragment shader.\nERROR: %s", infolog);
            
            // Delete shaders before exiting to save memory
            GLCall(glDeleteShader(vert));
            GLCall(glDeleteShader(frag));

            return;
        }

        // Create the shader program
        m_shader_program = glCreateProgram();

        // Attach the shaders to the program
        GLCall(glAttachShader(m_shader_program, vert));
        GLCall(glAttachShader(m_shader_program, frag));

        // Link the program
        GLCall(glLinkProgram(m_shader_program));

        // If linking failed
        if(!CheckProgramLink(m_shader_program))
        {
            // Log the OpenGL error message that stores why the program didn't link correctly
            GLCall(glGetProgramInfoLog(m_shader_program, sizeof(infolog), NULL, infolog));
            Logger::Error("Shader not linked.\nERROR: %s", infolog);

            // Delete shaders and program to free memory
            GLCall(glDeleteShader(vert));
            GLCall(glDeleteShader(frag));

            GLCall(glDeleteProgram(m_shader_program));

            return;
        }

        #ifdef DEBUG

        glValidateProgram(m_shader_program);

        GLCall(glGetProgramInfoLog(m_shader_program, sizeof(infolog), NULL, infolog));

        Logger::Debug("Program validation: %s", infolog);

        #endif

        // Delete the shaders before we exit to free memory
        GLCall(glDeleteShader(vert));
        GLCall(glDeleteShader(frag));
    }
    
    /// @brief Deletes the shader program to free memory
    ~Shader()
    {
        free();
    }

    /// @brief Binds the shader to be the active shader in OpenGL
    inline void Bind()
    {
        GLCall(glUseProgram(m_shader_program));
    }

    /// @brief Sets the single integer uniform in the shader program
    /// @param name Name of the uniform
    /// @param val Value to give the uniform
    void SetIntUniform(const std::string& name, const int& val);

    /// @brief Sets the 4x4 matrix uniform in the shader program
    /// @param name Name of the uniform
    /// @param mat Matrix to give the uniform
    void SetMatrixUniform(const std::string& name, const glm::mat4& mat);

    /// @brief Deletes the shader program
    void free();

private:
    // Reference ID to the OpenGL shader object
    unsigned int m_shader_program;

    /// @brief Checks if the OpenGL shader object passed through compiled correctly
    /// @param shader Shader to check compilation
    /// @return True if successful, false if not
    bool CheckShaderCompilation(const unsigned int& shader);

    /// @brief Checks if the OpenGL program object passed through linked correctly
    /// @param program Program to check linking
    /// @return True if successful, false if not
    bool CheckProgramLink(const unsigned int& program);

};

#endif