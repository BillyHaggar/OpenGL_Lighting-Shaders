#version 330 core

out vec4 FragColor;
in vec3 inNormal;
in vec2 inTexture;
in vec3 fragPosition;
in vec3 inColor;

struct Material {
	float Ns;
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	vec3 Ke;
	float Ni;
	float d;
	int illum;
};

uniform sampler2D texture;
uniform vec3 lightColor;
uniform float ambientLight;
uniform vec3 lightPos;
uniform vec3 viewPosition;
uniform Material material;

void main(){

	//diffuse
	vec3 norm = normalize(inNormal);
	vec3 lightDir = normalize(lightPos - fragPosition);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * inColor) * (lightColor);

	//specular
	float specularStrength = 1.0;
	vec3 viewDir = normalize(viewPosition - fragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
	vec3 specular = specularStrength * spec * lightColor; 


	vec3 result = (ambientLight + diffuse + specular) * inColor;


	FragColor = texture(texture, inTexture) * vec4(result, material.d);
}