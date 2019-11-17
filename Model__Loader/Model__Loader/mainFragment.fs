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
uniform vec3 viewPosition;

void main(){

	//diffuse
	vec3 norm = normalize(inNormal);
	vec3 lightDir = normalize(lightPos - fragPosition);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	//specular
	float specularStrength = 1.0;
	vec3 viewDir = normalize(viewPosition - fragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
	vec3 specular = specularStrength * spec * lightColor; 


	vec3 result = (ambientLight + diffuse + specular);

	FragColor = texture(texture2, inTexture)  * vec4(result, 1.0f);
}