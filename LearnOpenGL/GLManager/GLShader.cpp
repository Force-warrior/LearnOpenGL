//
//  ShaderDelegate.cpp
//  LearnOpenGL
//
//  Created by 张光明 on 2024/8/5.
//

#include "GLAgent.hpp"
#include "glad/glad.h"

GLShader::GLShader(const char * shaderStr, GLShaderType type)
{
    if(type == GLShaderType::GL_SHADER_VERTEX)
    {
        m_shaderId = glCreateShader(GL_VERTEX_SHADER);
    }
    else if (type == GLShaderType::GL_SHADER_FRAGMENT)
    {
        m_shaderId = glCreateShader(GL_FRAGMENT_SHADER);
    }
    
    glShaderSource(m_shaderId, 1, &shaderStr, NULL);
    glCompileShader(m_shaderId);
    
}

GLShader::~GLShader()
{
    if(m_shaderId != 0)
    {
        glDeleteShader(m_shaderId);
    }
}
