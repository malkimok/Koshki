#include "Controller.hpp"
#include "DeltaTime.hpp"

void Controller::cameraKeyControl(Scene* scene, int windowNumber, int cameraNumber){
    Camera* camera = scene->getCamerasList()[cameraNumber];
    bool* keys = scene->getWindowsList()[windowNumber]->getKeys();
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

void Controller::cameraMouseControl(Scene* scene, int windowNumber, int cameraNumber){
    Camera* camera = scene->getCamerasList()[cameraNumber];
    float xChange = scene->getWindowsList()[windowNumber]->getXChange();
    float yChange = scene->getWindowsList()[windowNumber]->getYChange();
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

void Controller::cameraControl(Scene* scene, int windowNumber, int cameraNumber){
    cameraKeyControl(scene, windowNumber, cameraNumber);
    cameraMouseControl(scene, windowNumber, cameraNumber);
}
