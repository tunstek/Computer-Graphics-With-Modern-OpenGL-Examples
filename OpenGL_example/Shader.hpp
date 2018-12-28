//
//  Shader.hpp
//  OpenGL GLFW
//
//  Created by Keith Tunstead on 26/12/2018.
//  Copyright © 2018 Keith Tunstead. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class Shader {
public:
    Shader();
    
    void createFromFiles(const char* vertexLocation, const char* fragmentLocation);
    void createFromStrings(const char* vertexCode, const char* fragmentCode);
    
    GLuint getProjectionLocation();
    GLuint getModelLocation();
    GLuint getViewLocation();
    
    void useShader();
    void clearShader();
    
    ~Shader();
private:
    GLuint shaderID, uniformProjection, uniformModel, uniformView;
     
    void compileShader(const char* vertexCode, const char* fragmentCode);
    void addShader(GLuint program, const char* shaderCode, GLenum shaderType);
};

#endif /* Shader_hpp */
