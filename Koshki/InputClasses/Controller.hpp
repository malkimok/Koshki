#pragma once

#include "UserInput.hpp"
#include "Scene.hpp"

class Controller{
public:
    static void cameraKeyControl(Scene* scene, string windowName, string cameraName);
    static void cameraMouseControl(Scene* scene, string windowName, string cameraName);
    static void cameraControl(Scene* scene, string windowName, string cameraName);
private:
    
};
