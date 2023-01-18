#define STB_IMAGE_IMPLEMENTATION
#define GL_SILENCE_DEPRECATION

#include <OpenGL/gl3.h>

//GLFW
#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <assimp/Importer.hpp>

#include "Scene.hpp"

#include "Shader.hpp"
#include "DeltaTime.hpp"

#include "Window.hpp"
#include "UserInput.hpp"
#include "Controller.hpp"
#include "EventManager.hpp"

#include "Model.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "Handler.hpp"
#include "Light.hpp"

using namespace std;

const char* vShader = "../../Shaders/mainVertShader.vert";
const char* fShader = "../../Shaders/mainFragShader.frag";

GLuint uniformModel, uniformProjection, uniformView,
       uniformLightCount, uniformSpecularIntensity, uniformShininess;

int main(int argc, const char * argv[]){
    Scene* mainScene = new Scene();
    mainScene->createWindow(1080, 1024);
    mainScene->createCamera(glm::vec3(0.0f, 0.0f, 0.0f),
                            glm::vec3(0.0f, -1.0f, 0.0f),
                            0.0f, 0.0f,
                            3.0f, 0.5f);
    UserInput userInput(mainScene->getWindowsList()[0]);
    Shader::createShader(vShader, fShader);
    
    //  gitTest
    // REMOVE LATER
    Material catMat = Material(1.0f, 4);
    Model cat = Model();
    mainScene->createLight(1.0f, 1.0f, 1.0f,
                           0.5f, 2.0f,
                           0.0f, 0.0f, 0.0f,
                           0.0f, 0.0f, 1.0f,
                           1.0f, 0.1f, 0.1f,
                           30);
    cat.loadModel("Models/YellowCat.obj");
    // REMOVE
    
    while(!glfwWindowShouldClose(mainScene->getWindowsList()[0]->getWindowPointer())){
        DeltaTime::calculateDeltaTime();
        Handler::shaderList[0]->useShader();
        glfwPollEvents();
        glClearColor(0.2f, 0.0f, 0.0f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        // Camera Control REMOVE LATER
        mainScene->getCamerasList()[0]->update();
        Controller::cameraControl(mainScene, 0, 0);
    
        // TEST!!!!!! BAD PLACE FOR THIS CODE
        Handler::shaderList[0]->setLights(mainScene->getLightsList(),
                                          mainScene->getLightCount());
        mainScene->getLightsList()[0]->
        updatePosition(mainScene->getCamerasList()[0]->getCameraPosition().x,
                       mainScene->getCamerasList()[0]->getCameraPosition().y + 0.1f,
                       mainScene->getCamerasList()[0]->getCameraPosition().z);
        mainScene->getLightsList()[0]->
        updateDirection(mainScene->getCamerasList()[0]->getCameraDirection().x,
                        mainScene->getCamerasList()[0]->getCameraDirection().y,
                        mainScene->getCamerasList()[0]->getCameraDirection().z);
        
        uniformSpecularIntensity = Handler::shaderList[0]->getSpecularIntensityLocation();
        uniformShininess = Handler::shaderList[0]->getShininessLocation();
        uniformModel = Handler::shaderList[0]->getModelLocation();
        uniformProjection = Handler::shaderList[0]->getProjectionLocation();
        uniformView = Handler::shaderList[0]->getViewLocation();
        glm::mat4 projection = glm::perspective(glm::radians(-60.0f),
            (GLfloat)mainScene->getWindowsList()[0]->getWidth()/
            (GLfloat)mainScene->getWindowsList()[0]->getHeight(), 0.1f, 100.0f);
        glm::mat4 view = mainScene->getCamerasList()[0]->calculateViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.4f, 0.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.f, 0.f, 0.f));
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(uniformLightCount, mainScene->getLightCount());
        catMat.useMaterial(uniformSpecularIntensity, uniformShininess);
        cat.renderModel();
        // TEST
        
        Handler::shaderList[0]->disableShader();
        glfwSwapBuffers(mainScene->getWindowsList()[0]->getWindowPointer());
    }
    return 0;
}

