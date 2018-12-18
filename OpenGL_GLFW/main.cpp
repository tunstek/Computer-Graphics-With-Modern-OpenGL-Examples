#include <iostream>
#include <string.h>
#include <cmath>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
//GLM
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


// window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.14159265358f / 180.0f;

GLuint VAO, VBO, shader, uniformModel; // the relevant IDs

bool direction = true; // direction to move triangle. true - right,  false - left
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.0001f;

float currentAngle = 0.0f;


// Vertex Shader
static const char* vShader = "                      \n\
#version 330                                        \n\
layout (location = 0) in vec3 pos;                  \n\
uniform mat4 model;                                 \n\
void main() {                                       \n\
gl_Position = model * vec4(0.4*pos.x, 0.4*pos.y, pos.z, 1.0);       \n\
}";

// Fragment Shader
static const char* fShader = "                      \n\
#version 330                                        \n\
out vec4 color;                                     \n\
void main() {                                       \n\
color = vec4(1.0, 0.0, 0.0, 1.0);                   \n\
}";

void createTriangle() {
    // center of screen is 0.0
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    glGenVertexArrays(1, &VAO); // creates a VAO array on the GPU and stores the ID in VAO
    glBindVertexArray(VAO);
        glGenBuffers(1, &VBO); // creates a buffer object and stores the ID in VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind the buffers
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // not changing the values in the array
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // chunks of 3 values
            glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(VAO);
}


void addShader(GLuint program, const char* shaderCode, GLenum shaderType) {
    GLuint theShader = glCreateShader(shaderType);
    
    const GLchar* theCode[1];
    theCode[0] = shaderCode;
    
    GLint codeLength[1];
    codeLength[0] = (GLint)strlen(shaderCode);
    
    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);
    
    // handle logging
    GLint result = 0;
    GLchar log[1024] = { 0 };
    
    std::cout << "Compiling shader..." << std::endl;
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if(!result) {
        glGetShaderInfoLog(theShader, sizeof(log), NULL, log);
        std::cout << "Failed to compile the %d shader!\n" << log << std::endl;
        printf("Failed to compile the %d shader!\n %s \n", shaderType, log);
        return;
    }
    std::cout << "Complete." << std::endl;
    glAttachShader(program, theShader);
}


void compileShaders() {
    shader = glCreateProgram();
    
    if(!shader) {
        std::cout << "Failed to create shader program!" << std::endl;
        return;
    }
    
    addShader(shader, vShader, GL_VERTEX_SHADER);
    addShader(shader, fShader, GL_FRAGMENT_SHADER);
    
    // handle logging
    GLint result = 0;
    GLchar log[1024] = { 0 };
    
    // Get the link status
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if(!result) {
        glGetProgramInfoLog(shader, sizeof(log), NULL, log);
        printf("Failed to link the shader program!\n %s \n", log);
        return;
    }
    
    // Validate
    std::cout << "Validating Shader..." << std::endl;
    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if(!result) {
        glGetProgramInfoLog(shader, sizeof(log), NULL, log);
        printf("Failed to validate the shader program!\n %s \n", log);
        return;
    }
    std::cout << "Complete." << std::endl;
    
    // get the uniform shader variable
    uniformModel = glGetUniformLocation(shader, "model");
    
}

int main() {
    if(glfwInit() != GL_TRUE) {
        std::cout << "Failed to init GLFW" << std::endl;
        return -1;
    }
    
    // Set OpenGL version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Set OpenGL profile (compatibility)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // not backwards compatible
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // forwards compatible
    // Set the window as not resizable
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    int bufferWidth, bufferHeight; // screen width and height
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Example", nullptr, nullptr);
    if(window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
    
    // use window as the current main window
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE; // enable modern GLEW features
    
    if(glewInit() != GLEW_OK) {
        std::cout << "Failed to init GLEW" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    
    // Create viewport
    glViewport(0, 0, bufferWidth, bufferHeight);
    
    createTriangle();
    compileShaders();
    
    // loop until the window is closed
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        if(direction) {
            // going right
            triOffset += triIncrement;
        }
        else {
            triOffset -= triIncrement;
        }
        if(abs(triOffset) >= triMaxOffset) {
            direction  = !direction;
        }
        
        currentAngle += 0.01f;
        if(currentAngle >= 360) {
            currentAngle -= 360;
        }
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shader);
        
        glm::mat4 model = glm::mat4(0.1);
            // add any translations, rotations or scaling here, no need to touch the shaders
            // order can be thought of as happening in reverse
            model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
            model = glm::rotate(model, currentAngle*toRadians, glm::vec3(0.0f, 0.0f, 1.0f)); // rotate around the z axis
            // above requires projection to rotate around the 'world' as opposed to the window it's in
        
        
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        
            glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);
        
        glUseProgram(0);
        
        
        // swaps the buffers (one buffer to draw to [that the user cannot see] and the other that the user can currently see)
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}






