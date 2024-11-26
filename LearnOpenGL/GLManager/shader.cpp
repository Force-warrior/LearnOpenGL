//
//  shader.cpp
//  LearnOpenGL
//
//  Created by 张光明 on 2024/11/25.
//

#include "shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
//    std::string strVertexShader, strFragmentShader;
//    std::ifstream fVertexFile, fFragmentFile;
//    fVertexFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
//    fFragmentFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
//    
//    try {
//        fVertexFile.open(vertexPath);
//        fFragmentFile.open(fragmentPath);
//        std::stringstream vertexStream;
//        vertexStream << fVertexFile.rdbuf();
//        std::stringstream fragmentStream;
//        fragmentStream <<  fFragmentFile.rdbuf();
//        fVertexFile.close();
//        fFragmentFile.close();
//        
//        strVertexShader = vertexStream.str();
//        strFragmentShader = fragmentStream.str();
//    } catch (std::ifstream::failure & e ) {
//        
//    }
//    
//    const char* vertexShaderSource = strVertexShader.c_str();
//    const char* fragmentShaderSource = strFragmentShader.c_str();
    
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
        "uniform float time;\n"
        "void main()\n"
        "{\n"
        "   float intensity = (sin(time) + 1.0) / 2.0;\n"
        "   fragColor = vec4(vec3(intensity) + color, 1.0f);\n"
        "}\0";
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    GLint success;
    char info[1024] = {};
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 1024, NULL, info);
        std::cout<<"Shader Compile Failed, info: "<<info<<std::endl;
    }
    
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 1024, NULL, info);
        std::cout<<"Shader Compile Failed, info: "<<info<<std::endl;
    }
    
    program_ = glCreateProgram();
    glAttachShader(program_, vertexShader);
    glAttachShader(program_, fragmentShader);
    glLinkProgram(program_);
    
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(program_, 1024, NULL, info);
        std::cout<<"Shader Linked Failed, info: "<< info <<std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    
}

void Shader::begin()
{
    glUseProgram(program_);
}

void Shader::end()
{
    glUseProgram(0);
}

void Shader::setFloat(const std::string &name, float value)
{
    GLint location = glGetAttribLocation(program_, name.c_str());
    glUniform1f(location, value);
}
