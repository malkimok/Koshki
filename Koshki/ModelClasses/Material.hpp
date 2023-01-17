#ifndef Material_hpp
#define Material_hpp

#include <stdio.h>
#include <OpenGL/gl3.h>

#endif

class Material{
public:
    Material();
    Material(GLfloat specIntensity, GLfloat shine);
    void useMaterial(GLuint specIntensityLocation, GLuint shininessLocation);
    ~Material();
private:
    GLfloat specularIntensity;
    GLfloat shininess;
    
};
