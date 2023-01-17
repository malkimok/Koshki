#version 330

struct Light{
    vec3 colour;
    float ambientIntensity;
    float diffuseIntensity;
    vec3 position;
    float constant;
    float linear;
    float exponent;
    vec3 direction;
    float edge;
};

struct Material{
    float specularIntensity;
    float shininess;
};

const int MAX_LIGHTS = 32;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 finalColour;

uniform sampler2D theTexture;
uniform Material material;
uniform vec3 eyePosition;

uniform int lightsCount;
uniform Light lights[MAX_LIGHTS];

vec4 CalcLightByDirection(Light light, vec3 direction){
    vec4 ambientColour = vec4(light.colour, 1.0f) * light.ambientIntensity;
    float diffuseFactor = max(dot(normalize(normal), normalize(direction)), 0.0f);
    vec4 diffuseColour = vec4(light.colour, 1.0f) * light.diffuseIntensity * diffuseFactor;
    vec4 specularColour = vec4(0.0f);
    
    if (diffuseFactor > 0.0f){
        vec3 fragToEye = normalize(eyePosition - fragPos);
        vec3 reflectedVertex = reflect(-direction, normalize(normal));
        float specularFactor = max(dot(fragToEye, reflectedVertex),0.0f);
        if (specularFactor > 0.0f){
            specularFactor = pow(specularFactor, material.shininess);
            specularColour = vec4(light.colour * material.specularIntensity * specularFactor, 1.0f);
        }
    }
    return (ambientColour + (diffuseColour + specularColour));
}

vec4 CalcLightColour(Light light){
    vec3 direction = fragPos - light.position;
    float distance = length(direction);
    direction = normalize(direction);
    vec4 colour = CalcLightByDirection(light, direction);
    float attenuation = light.exponent * distance*distance
                        + light.linear * distance
                        + light.constant;
    return (colour/attenuation);
}

vec4 CalcLight(Light light){
    vec3 rayDirection = normalize(fragPos - light.position);
    float slFactor = dot(rayDirection, light.direction);
    if(slFactor > light.edge){
        vec4 colour = CalcLightColour(light);
        return colour * (1.0f - (1.0f - slFactor)*(1.0f/ (1.0f - light.edge)));
    }else{
        return vec4(0.0f);
    }
}

vec4 CalcLights(){
    vec4 totalColour = vec4(0.0f);
    for(int i = 0; i < lightsCount; i++){
        totalColour += CalcLight(lights[i]);
    }
    return totalColour;
}

void main(){
    vec4 colour = vec4(0.0f);
    colour += CalcLights();
    finalColour = texture(theTexture, texCoord) * colour;
}

