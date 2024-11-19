//
//  Application.cpp
//  LearnOpenGL
//
//  Created by 张光明 on 2024/11/14.
//

#include "Application.hpp"

#include "OpenGL/gl.h"

Application::~Application()
{
    if(mainWindow_)
    {
        glfwDestroyWindow(mainWindow_);
    }
}

Application* Application::getInstance()
{
    static Application obj;
    
    return &obj;
}


bool Application::initialize()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    mainWindow_ = glfwCreateWindow(800, 600, "MainWindow", NULL, NULL);
    if(mainWindow_ == nullptr)
    {
        return false;
    }
    glfwMakeContextCurrent(mainWindow_);
    
    glfwSetFramebufferSizeCallback(mainWindow_, FreamBuffer_Resize_Event);
    glfwSetWindowCloseCallback(mainWindow_, Windows_Close_Event);
    
    return true;
}

bool Application::update()
{
    if(glfwWindowShouldClose(mainWindow_))
    {
        glfwDestroyWindow(mainWindow_);
        return false;
    }
    glfwSwapBuffers(mainWindow_);
    glfwPollEvents();
    return true;
}

void Application::destroy()
{
    glfwTerminate();
}

void Application::FreamBuffer_Resize_Event(GLFWwindow* window, int width, int height)
{
    if(Application::getInstance()->cb_FrameBufferResize_)
    {
        Application::getInstance()->cb_FrameBufferResize_(width, height);
    }
    glViewport(0, 0, width, height);
}

void Application::Windows_Close_Event(GLFWwindow* window)
{
    glfwSetWindowShouldClose(window, true);
}

void Application::setFreamBufferResizeCallback(FrameBufferResizeCallback callback)
{
    cb_FrameBufferResize_ = callback;
}
