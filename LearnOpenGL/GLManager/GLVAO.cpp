//
//  GLVAO.cpp
//  LearnOpenGL
//
//  Created by 张光明 on 2024/8/7.
//

#include "GLAgent.hpp"
#include "glad/glad.h"

GLVAO::GLVAO(){
    glGenVertexArrays(1, &m_vaoId);
}

GLVAO::~GLVAO(){
    if(m_vaoId)
    {
        glDeleteVertexArrays(1, &m_vaoId);
        m_vaoId = 0;
    }
}

void GLVAO::addVertex3D(float* data, int vertexCount, int layout)
{
    glBindVertexArray(m_vaoId);

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(float), data, GL_STATIC_DRAW);

    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

    glEnableVertexAttribArray(layout);


    glBindVertexArray(0);
}


void GLVAO::bindVAO()
{
    glBindVertexArray(m_vaoId);
}
