//
//  Mesh.hpp
//  OpenGL GLFW
//
//  Created by Keith Tunstead on 26/12/2018.
//  Copyright © 2018 Keith Tunstead. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include <GL/glew.h>

class Mesh {
public:
    Mesh();
    
    void createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
    void renderMesh();
    void clearMesh();
    
    ~Mesh();
private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
};

#endif /* Mesh_hpp */
