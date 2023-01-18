#pragma once

#include <OpenGL/gl3.h>

//GLFW
#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <map>

#include "Window.hpp"
#include "Camera.hpp"
#include "EventManager.hpp"
#include "Light.hpp"

using namespace std;

class Scene{
public:
    Scene();
    void setWindow(Window* window);
    void setCamera(Camera* camera);
    void setLight(Light* light);
    
    void createWindow(int width, int height, string name);
    void createCamera(glm::vec3 cameraPosition, glm::vec3 cameraUp,
                      GLfloat cameraYaw, GLfloat cameraPitch,
                      GLfloat cameraMoveSpeed, GLfloat cameraTurnSpeed,
                      string cameraName);
    void createLight(GLfloat red, GLfloat green, GLfloat blue,
                     GLfloat ambientIntensity, GLfloat diffuseIntensity,
                     GLfloat xPos, GLfloat yPos, GLfloat zPos,
                     GLfloat xDir, GLfloat yDir, GLfloat zDir,
                     GLfloat con, GLfloat lin, GLfloat exp,
                     GLfloat edg,
                     string name);
    void increaseLightCount(){lightCount++;}
    map<string, Window*> getWindowsMap(){return sceneWindowsMap;}
    map<string, Camera*> getCamerasMap(){return sceneCamerasMap;}
    map<string, Light*> getLightsMap(){return sceneLightsMap;}
    int getLightCount(){return lightCount;}
private:
    map<string, Window*> sceneWindowsMap;
    map<string, Camera*> sceneCamerasMap;
    map<string, Light*> sceneLightsMap;
    int lightCount = 0;
};
