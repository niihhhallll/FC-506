#include <iostream>

#include "../include/glad/glad.h"
#include "../include/Window.h"
#include "../include/GLFW/glfw3.h"


int main()
{
    InitOpengl::Window windowObj{100,100,"Hello"};

    windowObj.addHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    windowObj.addHint(GLFW_CONTEXT_VERSION_MINOR,3);
    windowObj.addHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    if(windowObj.init() != ErrorOpengl::Success)
    {
        return ErrorOpengl::windowInitFailed;
    }

    while(!windowObj.isClosed())
    {
        windowObj.update();
    }

    return 0;
}
