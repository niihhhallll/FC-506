#include <iostream>

#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"
#include "../include/glm/glm.hpp"

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

    struct Vertex
    {
       glm::vec2 position;
       glm::vec2 uv;
       glm::vec4 color;
    };


    Vertex vertices[4] = {
        // Position (X, Y)       UV          Color
        {{ -0.5f,  0.5f },  { 0.0f, 0.0f }, { 0.1f, 0.7f, 0.8f, 1.0f }}, // Top-Left
        {{  0.5f,  0.5f },  { 1.0f, 0.0f }, { 0.1f, 0.7f, 0.8f, 1.0f }}, // Top-Right
        {{ -0.5f, -0.5f },  { 0.0f, 1.0f }, { 0.1f, 0.7f, 0.8f, 1.0f }}, // Bottom-Left
        {{  0.5f, -0.5f },  { 1.0f, 1.0f }, { 0.1f, 0.7f, 0.8f, 1.0f }}  // Bottom-Right
    };

    unsigned int indices[3] = {
        0, 1, 2,  // Triangle 1
    };
    // vertex shader
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec2 aPos;\n"
        "uniform mat4 u_Projection;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
        "}\0";

    const char* fragmentshader = R"(#version 330 core
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    } )";

    unsigned int vao;
    // gene id
    glGenVertexArrays(1,&vao);
    // binds it.
    glBindVertexArray(vao);

    unsigned int vbo;
    // generate buffer
    glGenBuffers(1, &vbo);
    // bind buffer
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    // add buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // Upload the 'indices' array to GPU memory!
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // adding to the layout slot 0,1,2 in location of the vertex shader
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // Slot 1 (UV): Read 2 floats
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    //glEnableVertexAttribArray(1);
    // -> The VAO records: "Slot 1 reads 2 floats starting at offset 8 of VBO."

    // Slot 2 (Color): Read 4 floats
    //glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    //glEnableVertexAttribArray(2);
    // -> The VAO records: "Slot 2 reads 4 floats starting at offset 16 of VBO."

    glBindVertexArray(0);
    // create vertexshader variable
    unsigned int vertexshader;
    // createshader
    vertexshader = glCreateShader(GL_VERTEX_SHADER);
    // give the shader source
    glShaderSource(vertexshader,1,&vertexShaderSource,NULL);
    // compile the shader
    glCompileShader(vertexshader);

    // create fragmentshader variable
    unsigned int fragmentShader;
    // create the shader r
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // give the source
    glShaderSource(fragmentShader, 1, &fragmentshader, NULL);
    // compile the shader
    glCompileShader(fragmentShader);

    // make the last shader object
    unsigned int shader;
    // create the program
    shader = glCreateProgram();
    // attach the vertex shader output to shader
    glAttachShader(shader, vertexshader);
    // attach the fragment shader to shader
    glAttachShader(shader, fragmentShader);
    // atlast link the program
    glLinkProgram(shader);

    while(!windowObj.isClosed())
    {
        renderObj.clear();
        // debug code

        // use the shader program
        glUseProgram(shader);

        glBindVertexArray(vao);

        // 3. DRAW!
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        windowObj.update();
    }

    return ErrorOpengl::Success;
}
