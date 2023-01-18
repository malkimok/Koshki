#include "Shader.hpp"
#include "Handler.hpp"

Shader::Shader(){
    shaderID = 0;
    
    uniformModel = 0;
    uniformView = 0;
    uniformProjection = 0;
}

void Shader::createFromFiles(const char* vertexLocation, const char* fragmentLocation){
    string vertexShaderCode = readFile(vertexLocation);
    string fragmentShaderCode = readFile(fragmentLocation);
    compileShader(vertexShaderCode.c_str(), fragmentShaderCode.c_str());
}

string Shader::readFile(const char* fileLocation){
    string content;
    ifstream fileStream(fileLocation, ios::in);
    if(!fileStream.is_open()){
        cout << "Shader file didn`t open" << endl;
        return content;
    }
    string line;
    while(!fileStream.eof()){
        getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();
    return content;
}

void Shader::compileShader(const char* vertexShaderCode, const char* fragmentShaderCode){
    shaderID = glCreateProgram();
    if(!shaderID){
        printf("Shader compile failed");
        return;
    }
    addShader(shaderID, vertexShaderCode, GL_VERTEX_SHADER);
    addShader(shaderID, fragmentShaderCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar errorLog[1024] = {0};

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if(!result){
        glGetProgramInfoLog(shaderID, sizeof(errorLog), NULL, errorLog);
        printf("Error while linking program: '%s'", errorLog);
        return;
    }
    glValidateProgram(shaderID);
    glGetShaderiv(shaderID, GL_VALIDATE_STATUS, &result);
    if(!result){
        glGetProgramInfoLog(shaderID, sizeof(errorLog), NULL, errorLog);
        printf("Error while validating program: '%s'", errorLog);
        return;
    }
    assignUniforms();
}

void Shader::addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType){
    GLuint theShader = glCreateShader(shaderType);
    const GLchar* theCode[1];
    theCode[0] = shaderCode;
    GLint codeLength[1];
    codeLength[0]  = (int)strlen(shaderCode);
    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);
    GLint result = 0;
    GLchar errorLog[1024] = {0};
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if(!result){
        glGetShaderInfoLog(theShader, sizeof(errorLog), NULL, errorLog);
        printf("Error while compiling %d : '%s' \n", shaderType, errorLog);
        return;
    }
    glAttachShader(theProgram, theShader);
}

void Shader::createShader(const char* vShader, const char* fShader){
    Shader* shader = new Shader;
    shader->createFromFiles(vShader, fShader);
    Handler::shaderList.push_back(shader);
}

void Shader::useShader(){
    glUseProgram(shaderID);
}

void Shader::disableShader(){
    glUseProgram(0);
}

void Shader::clearShader(){
    if(shaderID != 0){
        glDeleteProgram(shaderID);
        shaderID = 0;
    }
    uniformModel = 0;
    uniformView = 0;
    uniformProjection = 0;
}

void Shader::setLights(map<string, Light*> lights, unsigned int lightCount){
    if(lightCount > MAX_LIGHTS){
        lightCount = MAX_LIGHTS;
    }
    glUniform1i(uniformLightCount, lightCount);
    size_t i = 0;
    for (const auto& [name, light] : lights) {
        light->useLight(uniformLights[i].uniformAmbientIntensity,
                            uniformLights[i].uniformColour,
                            uniformLights[i].uniformDiffuseIntensity,
                            uniformLights[i].uniformPosition,
                            uniformLights[i].uniformDirection,
                            uniformLights[i].uniformConstant,
                            uniformLights[i].uniformLinear,
                            uniformLights[i].uniformExponent,
                            uniformLights[i].uniformEdge);
        i++;
    }
}

Shader::~Shader(){
    clearShader();
}


void Shader::assignUniforms(){
    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformView = glGetUniformLocation(shaderID, "view");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformTexture = glGetUniformLocation(shaderID, "TheTexture");
    uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
    uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
    uniformLightCount = glGetUniformLocation(shaderID, "lightsCount");
    for (size_t i = 0; i < MAX_LIGHTS; i++){
        char locBuffer[100] = { '\0' };
        
        snprintf(locBuffer, sizeof(locBuffer), "lights[%zu].colour", i);
        uniformLights[i].uniformColour = glGetUniformLocation(shaderID, locBuffer);
        
        snprintf(locBuffer, sizeof(locBuffer), "lights[%zu].ambientIntensity", i);
        uniformLights[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, locBuffer);
        
        snprintf(locBuffer, sizeof(locBuffer), "lights[%zu].diffuseIntensity", i);
        uniformLights[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, locBuffer);
        
        snprintf(locBuffer, sizeof(locBuffer), "lights[%zu].position", i);
        uniformLights[i].uniformPosition = glGetUniformLocation(shaderID, locBuffer);
        
        snprintf(locBuffer, sizeof(locBuffer), "lights[%zu].constant", i);
        uniformLights[i].uniformConstant = glGetUniformLocation(shaderID, locBuffer);
        
        snprintf(locBuffer, sizeof(locBuffer), "lights[%zu].linear", i);
        uniformLights[i].uniformLinear = glGetUniformLocation(shaderID, locBuffer);
        
        snprintf(locBuffer, sizeof(locBuffer), "lights[%zu].exponent", i);
        uniformLights[i].uniformExponent = glGetUniformLocation(shaderID, locBuffer);
        
        snprintf(locBuffer, sizeof(locBuffer), "lights[%zu].direction", i);
        uniformLights[i].uniformDirection = glGetUniformLocation(shaderID, locBuffer);
        
        snprintf(locBuffer, sizeof(locBuffer), "lights[%zu].edge", i);
        uniformLights[i].uniformEdge = glGetUniformLocation(shaderID, locBuffer);
    }
}
