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

void SingleBuffer()
{
    float positions[] = {
        -0.5f, -0.5f ,0.0f,
         0.5f, -0.5f ,0.0f,
         0.0f,  0.5f ,0.0f
    };
    float colors[] = {
        1.0f ,0.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f
    };
    
    GLuint posVbo = 0, colorVbo = 0;
    glGenBuffers(1, &posVbo);
    glGenBuffers(1, &colorVbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorVbo), colors, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
    
    glBindVertexArray(0);
}

void interLeavedBuffer()
{
    float vertices[] = {
        -0.5f, -0.5f ,0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f ,0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f ,0.0f, 0.0f, 0.0f, 1.0f
    };
    
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);
    
}

void prepareShader()
{
    const char *vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(aPos, 1.0);\n"
        "}\0";
    
    const char *fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 fragColor;\n"
        "void main()\n"
        "{\n"
        "fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0);\n"
        "}\0";
    
    
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    GLint success = 0;
    char infoLog[1024];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        std::cout << "ERROR: SHADER COMPILE ERROR --VERTEX : \n" <<infoLog<<std::endl;
    }
    
    GLuint fragShader = glad_glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        std::cout << "ERROR: SHADER COMPILE ERROR --FRAGMENT : \n" <<infoLog<<std::endl;
    }
    
    
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        std::cout << "Error: SHADER LINK ERROR " << "\n" << infoLog << std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
}


void prepareNextShader()
{
    const char *vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(aPos, 1.0);\n"
        "}\0";
    
    const char *fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 fragColor;\n"
        "void main()\n"
        "{\n"
        "fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0);\n"
        "}\0";
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragShader);
    
    program = glCreateProgram();
    
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragShader);
    
    glLinkProgram(program);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
}

void prepareVAOForGLTriangles()
{
    float vertices[] = {
        -0.5f, -0.5f ,0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f ,0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f ,0.0f, 0.0f, 0.0f, 1.0f
    };
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float)));
    
    glEnableVertexAttribArray(0);
    
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
    
    //SingleBuffer();
    
    //prepareShader();
    prepareNextShader();
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    prepareVAOForGLTriangles();

    // 执行窗体循环
    while(APP->update())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glBindVertexArray(vao);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    
    APP->destroy();
    return 0;
}
