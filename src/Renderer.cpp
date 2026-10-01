#include "../include/Renderer.h"
#include "../include/glad/glad.h"

void Renderer::setClearColor(float r,float gg,float b,float a)
{
    glClearColor(r,gg,b,a);
    return;
}

void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    return;
}
