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
    mainScene->createWindow(1080, 1024, "MainWindow");
    mainScene->createCamera(glm::vec3(0.0f, 0.0f, 0.0f),
                            glm::vec3(0.0f, -1.0f, 0.0f),
                            0.0f, 0.0f,
                            3.0f, 0.5f,
                            "MainCamera");
    UserInput userInput(mainScene->getWindowsMap()["MainWindow"]);
    Shader::createShader(vShader, fShader);
    
    // REMOVE LATER
    Material catMat = Material(1.0f, 4);
    Model cat = Model();
    mainScene->createLight(1.0f, 1.0f, 1.0f,
                           0.5f, 2.0f,
                           0.0f, 0.0f, 0.0f,
                           0.0f, 0.0f, 1.0f,
                           1.0f, 0.1f, 0.1f,
                           20,
                           "flashLight");
    cat.loadModel("Models/YellowCat.obj");
    // REMOVE
    
    while(!glfwWindowShouldClose(mainScene->getWindowsMap()["MainWindow"]->getWindowPointer())){
        
        DeltaTime::calculateDeltaTime();
        Handler::shaderList[0]->useShader();
        glfwPollEvents();
        glClearColor(0.2f, 0.0f, 0.0f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        // Camera Control REMOVE LATER
        mainScene->getCamerasMap()["MainCamera"]->update();
        Controller::cameraControl(mainScene, "MainWindow", "MainCamera");
    
        // TEST!!!!!! BAD PLACE FOR THIS CODE
        Handler::shaderList[0]->setLights(mainScene->getLightsMap(),
                                          mainScene->getLightCount());
        mainScene->getLightsMap()["flashLight"]->
        updatePosition(mainScene->getCamerasMap()["MainCamera"]->getCameraPosition().x,
                       mainScene->getCamerasMap()["MainCamera"]->getCameraPosition().y + 0.1f,
                       mainScene->getCamerasMap()["MainCamera"]->getCameraPosition().z);
        mainScene->getLightsMap()["flashLight"]->
        updateDirection(mainScene->getCamerasMap()["MainCamera"]->getCameraDirection().x,
                        mainScene->getCamerasMap()["MainCamera"]->getCameraDirection().y,
                        mainScene->getCamerasMap()["MainCamera"]->getCameraDirection().z);
        
        uniformSpecularIntensity = Handler::shaderList[0]->getSpecularIntensityLocation();
        uniformShininess = Handler::shaderList[0]->getShininessLocation();
        uniformModel = Handler::shaderList[0]->getModelLocation();
        uniformProjection = Handler::shaderList[0]->getProjectionLocation();
        uniformView = Handler::shaderList[0]->getViewLocation();
        glm::mat4 projection = glm::perspective(glm::radians(-60.0f),
            (GLfloat)mainScene->getWindowsMap()["MainWindow"]->getWidth()/
            (GLfloat)mainScene->getWindowsMap()["MainWindow"]->getHeight(), 0.1f, 100.0f);
        glm::mat4 view = mainScene->getCamerasMap()["MainCamera"]->calculateViewMatrix();
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
        glfwSwapBuffers(mainScene->getWindowsMap()["MainWindow"]->getWindowPointer());
    }
    return 0;
}

