

#include "../include/glad/glad.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"

// for printing out the errors and all,NULL identifier.
#include <iostream>

namespace Graphics {
class Shader {
public:
  // forward declaration for methods; (init methods)
  // constructor
  Shader() {
    // glsl code for vertex shader code.
    const char *vertexShaderCode = R"(#version 330 core
                    layout (location = 0) in vec2 aPos;

                    out vec4 outColor;
                    uniform mat4 Projection;
                    uniform mat4 Model;
                    void main()
                    {
                        vec4 worldPosition = Model * vec4(aPos,0.0,1.0f);
                        gl_Position = Projection * worldPosition;

                        outColor = vec4(1.0f,0.5f,0.2f,1.0f);
                    }

                )";
    // glsl code for fragment shader.
    const char *fragmentShaderCode = R"(#version 330 core
                    in vec4 outColor;

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

    // DEBUG CODE
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "VERTEX SHADER ERROR:\n" << infoLog << std::endl;
    }


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

    // DEBUG CODE
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "SHADER LINKING ERROR:\n" << infoLog << std::endl;
    }
    // after linking them to the shaderProgram we no longer need the vertex and
    // fragment shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    initTriangle();
    initQuad();
  }

  void initQuad()
  {
      glm::vec2 vertices[] =
          {
              glm::vec2(-0.5f,0.5f), // top
              glm::vec2(-0.5f,-0.5f), // bottom left
              glm::vec2(0.5f,-0.5f), // bottom right
              glm::vec2(0.5f,-0.5f), // bottom right
              glm::vec2(0.5f,0.5f), // top right
              glm::vec2(-0.5f,0.5f), // center
          };
      glGenVertexArrays(1,&quadVao);
      glGenBuffers(1,&quadVbo);
      glBindVertexArray(quadVao);

      glBindBuffer(GL_ARRAY_BUFFER, quadVbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
      glEnableVertexAttribArray(0);
      glBindVertexArray(0);
      return;
  }

  void DrawQuad(float x,float y,float height,float width)
  {
      glUseProgram(shaderProgram);
     // the screen size height and width should be changed.
     // it should be inherited from the window class.
      glm::mat4 projection = glm::ortho(0.0f,800.0f,600.0f,0.0f);

      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model,glm::vec3(x,y,0.0f));
      model = glm::scale(model,glm::vec3(width,height,1.0f));

      glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"Projection"),1,GL_FALSE,&projection[0][0]);
      glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"Model"),1,GL_FALSE,&model[0][0]);
      glBindVertexArray(quadVao);
      glDrawArrays(GL_TRIANGLES,0,6);
      glBindVertexArray(0);
  }

  void initTriangle()
  {
      // centered vertices
      glm::vec2 vertices[] = {
          glm::vec2( 0.0f, -0.5f), // Top
          glm::vec2(-0.5f,  0.5f), // Bottom-Left
          glm::vec2( 0.5f,  0.5f)  // Bottom-Right
      };

      glGenVertexArrays(1,&triangleVao);
      glGenBuffers(1,&triangleVbo);
      glBindVertexArray(triangleVao);

      glBindBuffer(GL_ARRAY_BUFFER, triangleVbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
      glEnableVertexAttribArray(0);
      glBindVertexArray(0);

      return;
  }

  void DrawTriangle(float x,float y,float height,float width)
  {
      glUseProgram(shaderProgram);
     // the screen size height and width should be changed.
     // it should be inherited from the window class.
      glm::mat4 projection = glm::ortho(0.0f,800.0f,600.0f,0.0f);

      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model,glm::vec3(x,y,0.0f));
      model = glm::scale(model,glm::vec3(width,height,1.0f));

      glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"Projection"),1,GL_FALSE,&projection[0][0]);
      glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"Model"),1,GL_FALSE,&model[0][0]);
      glBindVertexArray(triangleVao);
      glDrawArrays(GL_TRIANGLES,0,3);
      glBindVertexArray(0);
  }

  private:
    // shader program's object
    unsigned int shaderProgram;

    // VAO'S FOR SHAPES
    // ----------------
        unsigned int triangleVao,triangleVbo;
        unsigned int quadVao,quadVbo;

    // ----------------
  };
}
