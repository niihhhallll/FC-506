#include <iostream>

#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"
#include "../include/Window.h"


void framebuffer_size_callback(GLFWwindow* window,int width,int height)
{
   glViewport(0,0,width,width);
   return;
}

// adding hint to the glfwwindow;
void InitOpengl::Window::addHint(int hint,int value)
{
    // adds the hint and the value to the init of the window.
    glfwWindowHint(hint,value);
    return;
}

ErrorOpengl::Error InitOpengl::Window::init()
{
    // Creates window According to the width,width,name passed by the user.
    this->windowHandle = glfwCreateWindow(windowDataHandle.width,windowDataHandle.height,windowDataHandle.windowName.c_str(), NULL, NULL);
    if (this->windowHandle == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        // terminates the Init
        glfwTerminate();
        return ErrorOpengl::Error::windowInitFailed;
    }

    glfwMakeContextCurrent(this->windowHandle);
    glfwSetFramebufferSizeCallback(this->windowHandle,framebuffer_size_callback);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Faild to init glad." << std::endl;
        return ErrorOpengl::Error::gLoadFailed;
    }

    glViewport(0, 0, windowDataHandle.width,windowDataHandle.height);
    return ErrorOpengl::Error::Success;
}

void InitOpengl::Window::addContext(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);
    return;
}

// updates the SwapBuffer and PollEvents function.
void InitOpengl::Window::update()
{
    glfwSwapBuffers(this->windowHandle);
    glfwPollEvents();
    return;
}

bool InitOpengl::Window::isClosed()
{
    return glfwWindowShouldClose(this->windowHandle);
}


// deconstructor
InitOpengl::Window::~Window()
{
    // @use: Terminates the object of windowHandle;
    glfwTerminate();
}
