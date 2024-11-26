//
//  main.cpp
//  LearnOpenGL
//
//  Created by 张光明 on 2024/11/14.
//

#include <iostream>

#include "GLManager/shader.hpp"
#include "GLManager/core.h"
#include "Application/Application.hpp"


GLuint vao = 0, program = 0;


void pareVertex()
{
    float vertex[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    };
    
    
    unsigned int indices[] = {
        0, 1, 2,
    };
    
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    
    GLuint veo = 0;
    glGenBuffers(1, &veo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float)));
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veo);
    
    glBindVertexArray(0);
}

int main(int argc, char* argv[])
{
    // glfw 初始化
    if(!APP->initialize())
    {
        return 0;
    }
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    Shader shader("","");
    
    pareVertex();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // 执行窗体循环
    while(APP->update())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        shader.begin();
        shader.setFloat("time", glfwGetTime());
        glBindVertexArray(vao);
        
        glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        shader.end();
    }
    
    APP->destroy();
    return 0;
}
