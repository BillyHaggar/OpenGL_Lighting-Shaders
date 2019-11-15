#version 330 core

out vec4 FragColor;
in vec3 inNormal;
in vec2 inTexture;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 lightColor;
uniform float ambientLight;

void main(){

	vec3 lightResult = lightColor * ambientLight;
	// linearly interpolate between both textures ((80% texture1, 20% texture2) 80% Colour)
	FragColor = texture(texture2, inTexture)  * vec4(lightResult, 1.0f);
}