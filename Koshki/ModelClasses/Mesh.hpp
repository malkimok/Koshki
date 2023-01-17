#pragma once
#include <OpenGL/gl3.h>

class Mesh{
public:
    Mesh();
    void createMesh(GLfloat *vertices, GLuint *indices, GLuint numberOfVertices, GLuint numberOfIndices);
    void renderMeshTriangles();
    void clearMesh();
    ~Mesh();
    
    private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
};
