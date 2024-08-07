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
    
    GLint length = 0;
    glGetShaderiv(m_shaderId, GL_INFO_LOG_LENGTH, &length);
    if(length)
    {
        char* log = (char*)malloc(length);
        glGetShaderInfoLog(m_shaderId, length, NULL, log);
        printf(" %s", log);
        free(log);
    }
    
}

GLShader::~GLShader()
{
    if(m_shaderId != 0)
    {
        glDeleteShader(m_shaderId);
        m_shaderId = 0;
    }
}

