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
    void setWindow(Window* window){sceneWindowsList.push_back(window);}
    void setCamera(Camera* camera){sceneCamerasList.push_back(camera);}
    void setLight(Light* light);
    
    void createWindow(int width, int height);
    void createCamera(glm::vec3 cameraPosition, glm::vec3 cameraUp,
                      GLfloat cameraYaw, GLfloat cameraPitch,
                      GLfloat cameraMoveSpeed, GLfloat cameraTurnSpeed);
    void createLight(GLfloat red, GLfloat green, GLfloat blue,
                     GLfloat ambientIntensity, GLfloat diffuseIntensity,
                     GLfloat xPos, GLfloat yPos, GLfloat zPos,
                     GLfloat xDir, GLfloat yDir, GLfloat zDir,
                     GLfloat con, GLfloat lin, GLfloat exp,
                     GLfloat edg);
    void increaseLightCount(){lightCount++;}
    vector<Camera*> getCamerasList(){return sceneCamerasList;}
    vector<Window*> getWindowsList(){return sceneWindowsList;}
    vector<Light*> getLightsList(){return sceneLightsList;}
    int getLightCount(){return lightCount;}
private:
    vector<Window*> sceneWindowsList;
    vector<Camera*> sceneCamerasList;
    vector<Light*> sceneLightsList;
    int lightCount = 0;
};
