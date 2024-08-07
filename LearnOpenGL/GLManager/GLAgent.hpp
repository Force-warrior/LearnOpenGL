//
//  ShaderDelegate.hpp
//  LearnOpenGL
//
//  Created by 张光明 on 2024/8/5.
//

#ifndef ShaderDelegate_hpp
#define ShaderDelegate_hpp

#include <stdio.h>
#include <memory>

enum GLShaderType
{
    GL_SHADER_VERTEX = 1,
    GL_SHADER_FRAGMENT = 2
};

class GLShader : public std::enable_shared_from_this<GLShader>
{
public:
    GLShader(const char * shaderStr, GLShaderType type);
    ~GLShader();
    
    unsigned int getShaderId(){return m_shaderId;}
    
private:
    unsigned int m_shaderId = 0;
};

class GLProgram : public std::enable_shared_from_this<GLProgram>
{
public:
    GLProgram(const char * vertexShaderStr, const char * fragmentShaderStr);
    ~GLProgram();
    
    void useProgram();
    
private:
    unsigned int m_program;
};

class GLVAO : public std::enable_shared_from_this<GLVAO>
{
public:
    GLVAO();
    ~GLVAO();
    
    void addVertex3D(float* data, int vertexCount, int layout);
    
    void bindVAO();
private:
    unsigned int m_vaoId = 0;
};



#endif /* ShaderDelegate_hpp */
