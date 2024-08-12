//
//  GLProgram.cpp
//  LearnOpenGL
//
//  Created by 张光明 on 2024/8/7.
//

#include "GLAgent.hpp"
#include "glad/glad.h"

GLProgram::GLProgram(const char * vertexShaderStr, const char * fragmentShaderStr)
{
    m_program = glCreateProgram();
    std::shared_ptr<GLShader> vertexShader = std::make_shared<GLShader>(vertexShaderStr, GL_SHADER_VERTEX);
    std::shared_ptr<GLShader> fragmentShader = std::make_shared<GLShader>(fragmentShaderStr, GL_SHADER_FRAGMENT);
    glAttachShader(m_program, vertexShader->getShaderId());
    glAttachShader(m_program, fragmentShader->getShaderId());
    
    glLinkProgram(m_program);
}

GLProgram::~GLProgram()
{
    if(m_program)
    {
        glDeleteProgram(m_program);
        m_program = 0;
    }
}

void GLProgram::useProgram()
{
    glUseProgram(m_program);
}

void GLProgram::updaeUniformColor(float color)
{
    // 更新uniform颜色
    int vertexColorLocation = glGetUniformLocation(m_program, "ourColor");
    glUniform4f(vertexColorLocation, 0.0f, color, 0.0f, 1.0f);
}
