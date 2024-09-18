//
//  texture.cpp
//  LearnOpenGL
//
//  Created by 张光明 on 2024/8/13.
//
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "GLManager/GLAgent.hpp"

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    
    return 0;
}
