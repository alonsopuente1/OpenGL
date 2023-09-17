#ifndef SHADER_H
#define SHADER_H

#include "headers/util.hpp"
#include "headers/error.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Shader
{
public:
    Shader(const char* vert_file_path, const char* frag_file_path)
    {
        std::string vert_shader_source = ReadFile(vert_file_path);
        std::string frag_shader_source = ReadFile(frag_file_path);

        const char* p_vert_shader_source = vert_shader_source.c_str();        
        const char* p_frag_shader_source = frag_shader_source.c_str();

        unsigned int vert;         // Vertex shader
        unsigned int frag;         // Fragment shader
                char infolog[512]; // Info


        vert = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vert, 1, &p_vert_shader_source, nullptr);
        frag = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(frag, 1, &p_frag_shader_source, nullptr);

        glCompileShader(vert);
        glCompileShader(frag);

        if(!checkShaderCompilation(vert))
        {
            glGetShaderInfoLog(vert, sizeof(infolog), NULL, infolog);
            Logger::Error("Failed to compile vertex shader.\nERROR: %s", infolog);
        }

        if(!checkShaderCompilation(frag))
        {
            glGetShaderInfoLog(vert, sizeof(infolog), NULL, infolog);
            Logger::Error("Failed to compile fragment shader.\nERROR: %s", infolog);
        }

        m_shader_program = glCreateProgram();

        glAttachShader(m_shader_program, vert);
        glAttachShader(m_shader_program, frag);

        glLinkProgram(m_shader_program);

        if(!checkProgramLink(m_shader_program))
        {
            glGetProgramInfoLog(m_shader_program, sizeof(infolog), NULL, infolog);
            Logger::Warn("Shader not linked.\nERROR: %s", infolog);
        }

        #ifdef DEBUG
        glValidateProgram(m_shader_program);

        GLCall(glGetProgramInfoLog(m_shader_program, sizeof(infolog), NULL, infolog));

        Logger::Debug("Program validation: %s", infolog);

        #endif

        glDeleteShader(vert);
        glDeleteShader(frag);
    }
    
    ~Shader()
    {
        GLCall(glDeleteProgram(m_shader_program));
    }

    inline void Bind()
    {
        GLCall(glUseProgram(m_shader_program));
    }

    void SetIntUniform(const std::string& name, int val);
    void SetMatrixUniform(const std::string& name, const glm::mat4& mat);

private:
    unsigned int m_shader_program;

    bool checkShaderCompilation(const unsigned int& shader);
    bool checkProgramLink(const unsigned int& program);
};

#endif