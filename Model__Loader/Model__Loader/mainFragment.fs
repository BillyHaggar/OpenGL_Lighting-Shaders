#version 330 core

out vec4 FragColor;
in vec3 inColor;
in vec2 inTexture;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
	// linearly interpolate between both textures ((80% texture1, 20% texture2) 80% Colour)
	FragColor = mix(mix(texture(texture1, inTexture), texture(texture2, inTexture), 0.2),vec4(inColor, 0.0),0.8);
}