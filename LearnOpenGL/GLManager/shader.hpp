//
//  shader.hpp
//  LearnOpenGL
//
//  Created by 张光明 on 2024/11/25.
//

#ifndef shader_hpp
#define shader_hpp

#include "core.h"

#include <stdio.h>
#include <string>

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    
    void begin();
    void end();
    
    void setFloat(const std::string &name, float value);
private:
    GLuint program_ {0};
};


#endif /* shader_hpp */
