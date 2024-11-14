//
//  main.cpp
//  LearnOpenGL
//
//  Created by 张光明 on 2024/11/14.
//

#include <iostream>

#include "glad/glad.h"
#include "Application/Application.hpp"

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
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    // 执行窗体循环
    while(true)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        if(!APP->update())
        {
            return 0;
        }
    }
    
    APP->destroy();
    return 0;
}
