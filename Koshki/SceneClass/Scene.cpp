#include "Scene.hpp"

Scene::Scene(){
}

void Scene::setWindow(Window* window){
    sceneWindowsMap.insert({window->getName(), window});
}

void Scene::setCamera(Camera* camera){
    sceneCamerasMap.insert({camera->getName(), camera});
}

void Scene::setLight(Light* light){
    sceneLightsMap.insert({light->getName(), light});
    increaseLightCount();
}

void Scene::createWindow(int width, int height, string name){
    Window* mainWindow = new Window(width, height, name);
    setWindow(mainWindow);
}

void Scene::createCamera(glm::vec3 cameraPosition, glm::vec3 cameraUp,
                         GLfloat cameraYaw, GLfloat cameraPitch,
                         GLfloat cameraMoveSpeed, GLfloat cameraTurnSpeed,
                         string cameraName){
    Camera* camera = new Camera(cameraPosition, cameraUp,
                                cameraYaw, cameraPitch,
                                cameraMoveSpeed, cameraTurnSpeed, cameraName);
    setCamera(camera);
}

void Scene::createLight(GLfloat red, GLfloat green, GLfloat blue,
                        GLfloat ambientIntensity, GLfloat diffuseIntensity,
                        GLfloat xPos, GLfloat yPos, GLfloat zPos,
                        GLfloat xDir, GLfloat yDir, GLfloat zDir,
                        GLfloat con, GLfloat lin, GLfloat exp,
                        GLfloat edg,
                        string name){
    Light* light = new Light(red, green, blue,
                             ambientIntensity, diffuseIntensity,
                             xPos, yPos, zPos,
                             xDir, yDir, zDir,
                             con, lin, exp,
                             edg, name);
    setLight(light);
}
