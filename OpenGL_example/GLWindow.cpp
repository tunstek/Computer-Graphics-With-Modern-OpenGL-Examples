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
    GLWindow::init();
}

GLWindow::GLWindow(GLint windowWidth, GLint windowHeight) {
    width = windowWidth;
    height = windowHeight;
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
    
    return 0;
}


GLWindow::~GLWindow() {
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}
