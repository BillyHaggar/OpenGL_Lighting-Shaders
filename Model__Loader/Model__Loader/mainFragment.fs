#version 330 core

out vec4 FragColor;
in vec3 inNormal;
in vec2 inTexture;
in vec3 fragPosition;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 lightColor;
uniform float ambientLight;
uniform vec3 lightPos;

void main(){

	
	vec3 norm = normalize(inNormal);
	vec3 lightDir = normalize(lightPos - fragPosition);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	
	vec3 result = (ambientLight + diffuse);

	FragColor = texture(texture2, inTexture)  * vec4(result, 1.0f);
}