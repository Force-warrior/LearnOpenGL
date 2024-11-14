//
//  Application.hpp
//  LearnOpenGL
//
//  Created by 张光明 on 2024/11/14.
//

#ifndef Application_hpp
#define Application_hpp

#include <stdio.h>
#include <functional>
#include "GLFW/glfw3.h"

using FrameBufferResizeCallback =  std::function<void(int, int)>;

class Application
{
    explicit Application() = default;
public:
    ~Application();
    static Application* getInstance();
    
public:
    bool initialize();
    bool update();
    void destroy();
    
    void setFreamBufferResizeCallback(FrameBufferResizeCallback callback);
    
private:
    static void FreamBuffer_Resize_Event(GLFWwindow* window, int width, int height);
    static void Windows_Close_Event(GLFWwindow* window);
private:
    GLFWwindow *mainWindow_ = nullptr;
    FrameBufferResizeCallback cb_FrameBufferResize_;
};

#define APP Application::getInstance()

#endif /* Application_hpp */
