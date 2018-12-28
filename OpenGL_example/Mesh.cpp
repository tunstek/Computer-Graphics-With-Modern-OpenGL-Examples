//
//  Mesh.cpp
//  OpenGL GLFW
//
//  Created by Keith Tunstead on 26/12/2018.
//  Copyright © 2018 Keith Tunstead. All rights reserved.
//

#include "Mesh.hpp"

Mesh::Mesh() {
    VAO = 0;
    VBO = 0;
    IBO = 0;
    indexCount = 0;
}



void Mesh::createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices) {
    indexCount = numOfIndices;
    
    glGenVertexArrays(1, &VAO); // creates a VAO array on the GPU and stores the ID in VAO
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0])*numOfIndices, indices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &VBO); // creates a buffer object and stores the ID in VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind the buffers
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*numOfVertices, vertices, GL_STATIC_DRAW); // not changing the values in the array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // chunks of 3 values
    glEnableVertexAttribArray(0);
    
    // unbind array buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(VAO);
    
    // unbind element/index array buffer (should happen AFTER unbinding VAO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void Mesh::renderMesh() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void Mesh::clearMesh() {
    if(IBO != 0) {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }
    if(VBO != 0) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if(VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    indexCount = 0;
}


Mesh::~Mesh() {
    Mesh::clearMesh();
}
