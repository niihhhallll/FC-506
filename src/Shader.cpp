

#include "../include/glad/glad.h"

// for printing out the errors and all,NULL identifier.
#include <iostream>

namespace Graphics {
struct Vertex {
  float position[2]; // x and y positons
  float texCords[2]; // u,v for texture cordinates from 0 to 1
};

class Shader {
public:
  // constructor
  Shader() {
    // glsl code for vertex shader code.
    const char *vertexShaderCode = R"(#version 330 core
                    layout (location = 0) in vec2 aPos;
                    layout (location = 1) in vec2 uv;
                    layout (location = 2) in ve4 colors;

                    out vec2 textCord;
                    out vec2 outColor;
                    uniform mat4 uModel;
                    uniform mat4 uProjection;
                    void main()
                    {
                        vec4 worldPosition = uModel * vec4(aPos.x,aPos.y,0.0,1.0f);
                        gl_position = uProjection * worldPostion;

                        textCord = uv;
                        outColor = colors;
                    }

                )";
    // glsl code for fragment shader.
    const char *fragmentShaderCode = R"(#version 330 core
                    in vec2 textCord;
                    in vec2 outColor;

                    out vec4 FragColor;
                    void main()
                    {
                        FragColor = outColor;
                    }
                )";

    // dynamically compile at run-time.
    // @usage: creates a shader object, and referenced it by id.
    // @return: unsigned int(id of the shader).
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // @params: 1, ShaderObject
    //          2, How many strings are we passing to it.
    //          3, the string's source code pointer.
    //          4, LEAVE IT AS NULL (opengl docs).
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);

    // compiles the shader.(vertex shader)

    glCompileShader(vertexShader);

    // fragment shader.
    // glCreateShader creates a GL_FRAGMENT_SHADER (enum value).
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // @params: 1, ShaderObject
    //          2, How many strings are we passing to it.
    //          3, the string's source code pointer.
    //          4, LEAVE IT AS NULL (opengl docs).
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);

    // compiling shader. (fragment shader)
    glCompileShader(fragmentShader);

    // @usage: Attachs both the vertex shader and fragment shader, and links
    // them. Then we use the variable for running both the shader and fragment
    // shader programs
    shaderProgram = glCreateProgram();

    // attaches the vertex shader to the shaderprogram
    glAttachShader(shaderProgram, vertexShader);

    // attaches the fragment shader to the shaderProgram
    glAttachShader(shaderProgram, fragmentShader);

    // links the shader with vertex shader and fragment shader.
    glLinkProgram(shaderProgram);

    // after linking them to the shaderProgram we no longer need the vertex and
    // fragment shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
  }
  // create init for voa. for triangle, square,rectangle,circle
  void InitQuadVao() {
    // binding the vertex array for quad.
    // @usage: for plug and playing to draw fiqures to the screen using draw rectangle.

    glGenVertexArrays(1,&quadVao);

    // THESE AI GENERATED CODE'S ARE MAJOR BOILERPLIATE CODE'S, I AM THE PERSON WHO IS HANDLING LOGIC,I AM ONLY DOING LITTLE BIT OF AI WORK HERE.
    // ai generated cords.
    Vertex quadVertices[] = {
        // Position (X, Y)     // Texture Coords (U, V)
        { { -0.5f,  0.5f },    { 0.0f, 1.0f } }, // Top-Left     (Index 0)
        { {  0.5f,  0.5f },    { 1.0f, 1.0f } }, // Top-Right    (Index 1)
        { { -0.5f, -0.5f },    { 0.0f, 0.0f } }, // Bottom-Left  (Index 2)
        { {  0.5f, -0.5f },    { 1.0f, 0.0f } }  // Bottom-Right (Index 3)
    };
    // ai generated indices for the quad
    unsigned int quadIndices[] = {
        0, 1, 2,  // Triangle 1
        2, 1, 3   // Triangle 2
    };

    unsigned int quadVBO,quadEBO;


    glGenBuffers(1,&quadVBO);
    glGenBuffers(1,&quadEBO);

    // binds the vertex array
    glBindVertexArray(quadVao);
   // binds the quadvao to GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER,quadVao);
    glBufferData(GL_ARRAY_BUFFER,sizeof(quadIndices),quadIndices,GL_STATIC_DRAW);

    // binds the elemetns to quad ebo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,quadEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(quadVertices),quadVertices,GL_STATIC_DRAW);

    //AI GENERATED CODE
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

        // Attribute 1: Texture Coordinates / UV
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(1);

    // unbinds the vao
    glBindVertexArray(0);

  }

  void drawRectangle(float x,float y,float width,float height)
  {
      glUseProgram(shaderProgram);
      glm::mat4 model = glm::mat4(1.0f);

          // 1. Move to screen position (x, y)
          model = glm::translate(model, glm::vec3(x, y, 0.0f));

          // 2. Scale the 1x1 base float vertices to (width, height)
          model = glm::scale(model, glm::vec3(width, height, 1.0f));

          // Send GLM matrix and color to shader uniforms
          int modelLoc = glGetUniformLocation(shaderProgram, "u_Model");
          int colorLoc = glGetUniformLocation(shaderProgram, "u_Color");

          glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
          glUniform4fv(colorLoc, 1, glm::value_ptr(color));

          // Bind the VAO containing our float vertices and draw!
          glBindVertexArray(quadVAO);
          glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
          glBindVertexArray(0);
  }

  private:
    // shader program's object
        unsigned int shaderProgram;

    // VAO'S FOR SHAPES
    // ----------------

        unsigned int triganleVao;
        unsigned int sqaureVao;
        unsigned int quadVao;

    // ----------------
  };
}
