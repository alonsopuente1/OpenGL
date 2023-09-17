#include "headers/shader.hpp"
#include "headers/error.hpp"

bool Shader::checkShaderCompilation(const unsigned int& shader)
{
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    return success;
}

bool Shader::checkProgramLink(const unsigned int& program)
{
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    return success;
}

void Shader::SetIntUniform(const std::string& name, int val)
{
    Bind();
    GLCall(glUniform1i(glGetUniformLocation(m_shader_program, name.c_str()), val));
}

void Shader::SetMatrixUniform(const std::string& name, const glm::mat4& mat)
{
    Bind();
    GLCall(glUniformMatrix4fv(glGetUniformLocation(m_shader_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat)));
}
