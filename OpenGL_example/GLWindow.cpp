//
//  GLWindow.cpp
//  OpenGL GLFW
//
//  Created by Keith Tunstead on 27/12/2018.
//  Copyright © 2018 Keith Tunstead. All rights reserved.
//

#include <iostream>
#include "GLWindow.hpp"

GLWindow::GLWindow() {
    width = 800;
    height = 600;
    
    for(size_t i = 0; i < 1024; i++) {
        keys[i] = false;
    }
    
    GLWindow::init();
}

GLWindow::GLWindow(GLint windowWidth, GLint windowHeight) {
    width = windowWidth;
    height = windowHeight;
    
    for(size_t i = 0; i < 1024; i++) {
        keys[i] = false;
    }
    
    GLWindow::init();
}

int GLWindow::init() {
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
    
    mainWindow = glfwCreateWindow(width, height, "OpenGL Example", nullptr, nullptr);
    if(mainWindow == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    
    // use window as the current main window
    glfwMakeContextCurrent(mainWindow);
    
    // handle key and mouse input
    createCallbacks();
    
    
    glewExperimental = GL_TRUE; // enable modern GLEW features
    
    if(glewInit() != GLEW_OK) {
        std::cout << "Failed to init GLEW" << std::endl;
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return -1;
    }
    
    
    // enable OpenGL Features
    glEnable(GL_DEPTH_TEST);
    
    
    // Create viewport
    glViewport(0, 0, bufferWidth, bufferHeight);
    
    glfwSetWindowUserPointer(mainWindow, this);
    
    return 0;
}


void GLWindow::createCallbacks() {
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);
}


void GLWindow::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
    // get the focused window
    GLWindow* theWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
    
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if(key >= 0 && key < 1024) {
        //valid key
        if(action == GLFW_PRESS) {
            theWindow->keys[key] = true;
        }
        else if(action == GLFW_RELEASE) {
            theWindow->keys[key] = false;
        }
    }
}


void GLWindow::handleMouse(GLFWwindow* window, double xPos, double yPos) {
    // get the focused window
    GLWindow* theWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
    
    if(theWindow->mouseFirstMove) {
        // the mouse has not yet been moved, avoids sharp jerks on initial statup
        theWindow->lastMouseX = xPos;
        theWindow->lastMouseY = yPos;
        theWindow->mouseFirstMove = false;
    }
    
    theWindow->deltaMouseX = xPos - theWindow->lastMouseX;
    theWindow->deltaMouseY = theWindow->lastMouseY - yPos; // swap to invert the movement
    
    theWindow->lastMouseX = xPos;
    theWindow->lastMouseY = yPos;
    
    printf("x:%.6f y:%.6f\n", xPos, yPos);
}


GLWindow::~GLWindow() {
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}
