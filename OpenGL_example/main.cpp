#include <iostream>
#include <string.h>
#include <cmath>
#include <vector>
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

#include "GLWindow.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Utils.hpp"


GLWindow mainWindow;
// window dimensions
const GLint WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;




/*
    Vertex Shader
     - clamp - fixes values outside of the constraints (0 and 1)
*/
static const char* vShader = "shaders/vert.shader";


/*
    Fragment Shader
     - Handles each individual pixel and interpolates the values
 */
static const char* fShader = "shaders/frag.shader";


void createObjects() {
    
    unsigned int indices[] = {
        0, 3, 1, // side 1
        1, 3, 3, // side 2
        2, 3, 1, // front facing triangle
        0, 1, 2  // base of triange
    };
    
    // center of screen is 0.0
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    
    
    Mesh *obj1 = new Mesh();
    obj1->createMesh(vertices, indices, 12, 12);
    meshList.push_back(obj1);
    
}


void createShaders() {
    Shader *shader1 = new Shader();
    shader1->createFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}


int main() {
    
    GLWindow mainWindow = GLWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    
    createObjects();
    createShaders();
    
    camera = Camera();
    
    GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
    
    // create Projection
    glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth()/mainWindow.getBufferHeight(), 0.1f, 100.0f);
    
    // loop until the window is closed
    while(!mainWindow.getShouldClose()) {
        
        // get and handle user input
        glfwPollEvents();
        camera.keyControl(mainWindow.getKeys());
        
        // clear the window
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shaderList[0].useShader();
        uniformModel = shaderList[0].getModelLocation();
        uniformProjection = shaderList[0].getProjectionLocation();
        uniformView = shaderList[0].getViewLocation();
        
        glm::mat4 model = glm::mat4(0.1);
        
        // add any translations, rotations or scaling here, no need to touch the shaders
        // order can be thought of as happening in reverse
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::rotate(model, Utils::degreesToRadians(0), glm::vec3(0.0f, 1.0f, 0.0f));
        /* above requires projection to rotate around the 'world' as opposed to the window it's in */
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f)); // usually scale 'first'
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        
        meshList[0]->renderMesh();
        
        glUseProgram(0);
        
        
        mainWindow.swapBuffers();
    }
    
    glfwTerminate();
    return 0;
}






