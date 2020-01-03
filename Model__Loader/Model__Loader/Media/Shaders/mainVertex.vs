#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aColor;

out vec3 inNormal;
out vec2 inTexture;
out vec3 fragPosition;
out vec3 inColor;
out vec4 inFragPosLightSpace;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;

void main(){
   fragPosition = vec3(model * vec4(aPos, 1.0));
   inNormal = mat3(transpose(inverse(model))) * aNormal; 
   inTexture = aTexCoord;
   inColor = aColor;
   inFragPosLightSpace = lightSpaceMatrix * vec4(fragPosition, 1.0);
   gl_Position = projection * view * model * (vec4(aPos, 1.0));
}