//
//  shader.cpp
//  LearnOpenGL
//
//  Created by 张光明 on 2024/11/25.
//

#include "shader.hpp"
#include <fstream>
#include <sstream>

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
        "uniform float time;\n"
        "out vec3 color;\n"
        "void main()\n"
        "{\n"
        "   float value = (sin(time)) / 5;\n"
        "   gl_Position = vec4(aPos, 1.0f);\n"
        "   color = vec3(value) + aColor;\n"
        "}\0";
    
    const char * fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 fragColor;\n"
        "in vec3 color;\n"
        "void main()\n"
        "{\n"
        "   fragColor = vec4(color, 1.0f);\n"
        "}\0";
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    program_ = glCreateProgram();
    glAttachShader(program_, vertexShader);
    glAttachShader(program_, fragmentShader);
    glLinkProgram(program_);
    
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
