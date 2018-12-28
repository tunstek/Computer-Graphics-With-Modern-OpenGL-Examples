//
//  GLWindow.hpp
//  OpenGL GLFW
//
//  Created by Keith Tunstead on 27/12/2018.
//  Copyright © 2018 Keith Tunstead. All rights reserved.
//

#ifndef GLWindow_hpp
#define GLWindow_hpp

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLWindow {
public:
    GLWindow();
    GLWindow(GLint windowWidth, GLint windowHeight);
    
    int init();
    
    GLfloat getBufferWidth() { return bufferWidth; }
    GLfloat getBufferHeight() { return bufferHeight; }
    
    bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }
    
    bool* getKeys() { return keys; }
    GLfloat getDeltaMouseX();
    GLfloat getDeltaMouseY();
    
    // swaps the buffers (one buffer to draw to [that the user cannot see] and the other that the user can currently see)
    void swapBuffers() { glfwSwapBuffers(mainWindow); }
    
    ~GLWindow();
private:
    GLFWwindow *mainWindow;
    
    GLint width, height, bufferWidth, bufferHeight;
    
    bool keys[1024];
    
    GLfloat lastMouseX, lastMouseY, deltaMouseX, deltaMouseY;
    bool mouseFirstMove;
    
    void createCallbacks();
    static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

#endif /* GLWindow_hpp */
