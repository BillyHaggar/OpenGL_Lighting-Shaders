#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 inNormal;
out vec2 inTexture;
out vec3 fragPosition;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(){
   fragPosition = vec3(model * vec4(aPos, 1.0));
   inNormal = mat3(transpose(inverse(model))) * aNormal; 
   inTexture = aTexCoord;
   gl_Position = projection * view * model * (vec4(aPos, 1.0));
}