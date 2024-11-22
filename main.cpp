//
//  main.cpp
//  LearnOpenGL
//
//  Created by 张光明 on 2024/11/14.
//

#include <iostream>

#include "glad/glad.h"
#include "Application/Application.hpp"

GLuint vao = 0, program = 0;

void prepareShader()
{
    const char * vertexShaderSource =
        "#version 330 core\n"
        "layout (location=0) in vec3 aPos;\n"
        "layout (location=1) in vec3 aColor;\n"
        "out vec3 color;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0f);\n"
        "   color = aColor;\n"
        "}\0";
    
    const char * fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 fragColor;\n"
        "in vec3 color;\n"
        "void main()\n"
        "{\n"
        "   fragColor = vec4(color, 1.0f);\n"
        "}\0";
    
    
    GLuint vertesShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertesShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertesShader);
    GLint success = 0;
    GLchar info[1024];
    glGetShaderiv(vertesShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertesShader, 1024, NULL, info);
        std::cout << "VERTEX SHADER COMPILE ERROR: \n" << info << std::endl;
    }
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 1024, NULL, info);
        std::cout << "FRAGMENT SHADER COMPILE ERROR: \n" << info << std::endl;
    }
    
    program = glCreateProgram();
    glAttachShader(program, vertesShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(program, 1024, NULL, info);
        std::cout << "PROGRAM LINKED ERROR: \n" << info << std::endl;
    }
    
    glDeleteShader(vertesShader);
    glDeleteShader(fragmentShader);
}

void pareVertex()
{
    float vertex[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.5f, 0.5f, 0.2f, 0.0f, 1.0f,
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
    
    prepareShader();
    
    pareVertex();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    //prepareVAOForGLTriangles();

    // 执行窗体循环
    while(APP->update())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glBindVertexArray(vao);
        
        glDrawElements(GL_LINE_STRIP, 4, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    
    APP->destroy();
    return 0;
}
