#include "Controller.hpp"
#include "DeltaTime.hpp"

void Controller::cameraKeyControl(Scene* scene, string windowName, string cameraName){
    Camera* camera = scene->getCamerasMap()[cameraName];
    bool* keys = scene->getWindowsMap()[windowName]->getKeys();
    GLfloat deltaSpeed = camera->getMovementSpeed() * DeltaTime::getDeltaTime();
    if(keys[GLFW_KEY_W]){
        camera->addCameraPosition(camera->getCameraDirection() * deltaSpeed);
    }
    if(keys[GLFW_KEY_S]){
        camera->addCameraPosition((-camera->getCameraDirection() * deltaSpeed));
    }
    if(keys[GLFW_KEY_D]){
        camera->addCameraPosition((-camera->getCameraRight() * deltaSpeed));
    }
    if(keys[GLFW_KEY_A]){
        camera->addCameraPosition(camera->getCameraRight() * deltaSpeed);
    }
}

void Controller::cameraMouseControl(Scene* scene, string windowName, string cameraName){
    Camera* camera = scene->getCamerasMap()[cameraName];
    float xChange = scene->getWindowsMap()[windowName]->getXChange();
    float yChange = scene->getWindowsMap()[windowName]->getYChange();
    xChange *= camera->getTurnSpeed();
    yChange *= camera->getTurnSpeed();
    
    camera->addCameraYaw(xChange);
    camera->addCameraPitch(yChange);
    if(camera->getPitch() > 89.0f){
        camera->setCameraPitch(89.0f);
    }
    else if(camera->getPitch() < - 89.0f){
        camera->setCameraPitch(-89.0f);
    }
    else{
        camera->update();
    }
}

void Controller::cameraControl(Scene* scene, string windowName, string cameraName){
    cameraKeyControl(scene, windowName, cameraName);
    cameraMouseControl(scene, windowName, cameraName);
}
