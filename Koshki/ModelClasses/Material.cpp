#include "Material.hpp"


Material::Material(){
    specularIntensity = 0.0f;
    shininess = 0.0f;
}

Material::Material(GLfloat specIntensity, GLfloat shine){
    specularIntensity = specIntensity;
    shininess = shine;
}

void Material::useMaterial(GLuint specIntensityLocation, GLuint shininessLocation){
    glUniform1f(specIntensityLocation, specularIntensity);
    glUniform1f(shininessLocation, shininess);
}

Material::~Material(){
    
}
