#pragma once

#include "UserInput.hpp"
#include "Scene.hpp"

class Controller{
public:
    static void cameraKeyControl(Scene* scene, int windowNumber, int cameraNumber);
    static void cameraMouseControl(Scene* scene, int windowNumber, int cameraNumber);
    static void cameraControl(Scene* scene, int windowNumber, int cameraNumber);
private:
    
};
