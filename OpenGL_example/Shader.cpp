//
//  Shader.cpp
//  OpenGL GLFW
//
//  Created by Keith Tunstead on 26/12/2018.
//  Copyright © 2018 Keith Tunstead. All rights reserved.
//

#include "Shader.hpp"
#include "Utils.hpp"

Shader::Shader() {
    shaderID = 0;
    uniformModel = 0;
    uniformProjection = 0;
    uniformView = 0;
}

void Shader::createFromStrings(const char *vertexCode, const char *fragmentCode) {
    compileShader(vertexCode, fragmentCode);
}

void Shader::createFromFiles(const char *vertexLocation, const char *fragmentLocation) {
    Shader::createFromStrings(Utils::ReadFile(vertexLocation).c_str(), Utils::ReadFile(fragmentLocation).c_str());
}

void Shader::compileShader(const char *vertexCode, const char *fragmentCode) {
    shaderID = glCreateProgram();
    
    if(!shaderID) {
        std::cout << "Failed to create shader program!" << std::endl;
        return;
    }
    
    addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);
    
    // handle logging
    GLint result = 0;
    GLchar log[1024] = { 0 };
    
    // Get the link status
    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if(!result) {
        glGetProgramInfoLog(shaderID, sizeof(log), NULL, log);
        printf("Failed to link the shader program!\n %s \n", log);
        return;
    }
    
    // Validate
    std::cout << "Validating Shader..." << std::endl;
    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if(!result) {
        glGetProgramInfoLog(shaderID, sizeof(log), NULL, log);
        printf("Failed to validate the shader program!\n %s \n", log);
        return;
    }
    std::cout << "Complete." << std::endl;
    
    // get the uniform shader variables
    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformView = glGetUniformLocation(shaderID, "view");
}

GLuint Shader::getProjectionLocation() {
    return uniformProjection;
}
GLuint Shader::getModelLocation() {
    return uniformModel;
}
GLuint Shader::getViewLocation() {
    return uniformView;
}

void Shader::useShader() {
    glUseProgram(shaderID);
}

void Shader::clearShader() {
    if(shaderID != 0) {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }
    uniformModel = 0;
    uniformProjection = 0;
}

void Shader::addShader(GLuint program, const char *shaderCode, GLenum shaderType) {
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
        exit(1);
    }
    std::cout << "Complete." << std::endl;
    glAttachShader(program, theShader);
}

Shader::~Shader() {
    Shader::clearShader();
}
