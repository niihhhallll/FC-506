#include <iostream>

#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"
#include "../include/glm/glm.hpp"
#include "Shader.cpp"
#include "../include/Window.h"
#include "../include/Renderer.h"

int main()
{
    InitOpengl::Window windowObj{800,600,"Hello"};
    Renderer renderObj;
    windowObj.addHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    windowObj.addHint(GLFW_CONTEXT_VERSION_MINOR,3);
    windowObj.addHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    if(windowObj.init() != ErrorOpengl::Success)
    {
        return ErrorOpengl::windowInitFailed;
    }
    // set Clear Color
    renderObj.setClearColor(0.0f,0.0f,0.0f,1.0f);

   Graphics::Shader shaderObj{};
    while(!windowObj.isClosed())
    {
        renderObj.clear();
        shaderObj.DrawQuad(400,300,200,400);
        shaderObj.DrawTriangle(200,400,100,50);
        windowObj.update();
    }

    return ErrorOpengl::Success;
}
