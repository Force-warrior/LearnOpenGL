//
//  main.cpp
//  LearnOpenGL
//
//  Created by 张光明 on 2024/11/14.
//

#include <iostream>

#include "glad/glad.h"
#include "Application/Application.hpp"

int main()
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
    
    // 执行窗体循环
    while(true)
    {
        if(!APP->update())
        {
            return 0;
        }
    }
    
    APP->destroy();
    return 0;
}
