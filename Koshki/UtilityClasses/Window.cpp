#include "Window.hpp"

Window::Window(int inputWidth, int inputHeight){
    for(int i = 0; i < sizeof(keys); i++){
        keys[i] = false;
    }
    width = inputWidth;
    height = inputHeight;
    this->Init();
}

int Window::Init(){
    if (!glfwInit()){
        glfwTerminate();
        printf("GLFW init failed");
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // removes backward                                                                 // compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // allows forward compatibility
    window = glfwCreateWindow(width, height, "Main Window", NULL, NULL);
    if (!window){
        printf("Window creation failed");
        glfwTerminate();
        return 1;
    }
    int bufferWidth, bufferHeight;  //Get buffer size info
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
    glfwMakeContextCurrent(window);  // Set context for GLFW to use
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, bufferWidth, bufferHeight); // 0,0 -- the lower left corner of the
                                                 // viewport rectangle in pixels
    glfwSetWindowUserPointer(window, this);
    
//    EventManager::signToEvent("KEY_256_PRESS", [=](){
//        glfwSetWindowShouldClose(window, GLFW_TRUE);
//    });
    return 0;
}

GLfloat Window::getXChange(){
    GLfloat theChange = changeX;
    changeX = 0;
    return theChange;
}

GLfloat Window::getYChange(){
    GLfloat theChange = changeY;
    changeY = 0;
    return theChange;
}

Window::~Window(){
    glfwDestroyWindow(window);
    glfwTerminate();
}
