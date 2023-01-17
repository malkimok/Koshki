#include "Scene.hpp"

Scene::Scene(){
}

void Scene::setLight(Light* light){
    sceneLightsList.push_back(light);
    increaseLightCount();
}

void Scene::createWindow(int width, int height){
    Window* mainWindow = new Window(width, height);
    setWindow(mainWindow);
}

void Scene::createCamera(glm::vec3 cameraPosition, glm::vec3 cameraUp,
                         GLfloat cameraYaw, GLfloat cameraPitch,
                         GLfloat cameraMoveSpeed, GLfloat cameraTurnSpeed){
    Camera* camera = new Camera(cameraPosition, cameraUp,
                                cameraYaw, cameraPitch,
                                cameraMoveSpeed, cameraTurnSpeed);
    setCamera(camera);
}

void Scene::createLight(GLfloat red, GLfloat green, GLfloat blue,
                        GLfloat ambientIntensity, GLfloat diffuseIntensity,
                        GLfloat xPos, GLfloat yPos, GLfloat zPos,
                        GLfloat xDir, GLfloat yDir, GLfloat zDir,
                        GLfloat con, GLfloat lin, GLfloat exp,
                        GLfloat edg){
    Light* light = new Light(red, green, blue,
                             ambientIntensity, diffuseIntensity,
                             xPos, yPos, zPos,
                             xDir, yDir, zDir,
                             con, lin, exp,
                             edg);
    setLight(light);
}
