#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 inColor;
out vec2 inTexture;
out vec3 inLighting;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(){
   gl_Position = projection * view * model * (transform * vec4(aPos, 1.0));
   inColor = aColor;
   inTexture = aTexCoord;
}