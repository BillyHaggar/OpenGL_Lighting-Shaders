#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec3 inNormal;
in vec2 inTexture;
in vec3 fragPosition;
in vec3 inColor;
in vec4 inFragPosLightSpace;

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
uniform sampler2D diffuseTexture;
uniform sampler2D shadowTexture;
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
	vec3 halfwayDir = normalize(lightDir + viewDir); 

	//blinn phong specular
	float spec = pow(max(dot(norm, halfwayDir), 0.0), 64);
	vec3 specular = specularStrength * spec * lightColor; 

	//shadows
	vec3 projCoords = inFragPosLightSpace.xyz / inFragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = texture(shadowTexture, projCoords.xy).r;
	float currentDepth = projCoords.z;
    float bias = max(0.05 * (1.0 - dot(norm, lightDir)), 0.005);
	float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowTexture, 0);
	for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowTexture, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
	shadow /= 9.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;


	vec3 result = ((ambientLight + (1.0 - shadow)) * (diffuse + specular)) * inColor;
	FragColor = texture(texture, inTexture) * vec4(result, 1.0);

	 // check whether fragment output is higher than threshold, if so output as brightness color
    float brightness = dot(result.rgb, vec3(0.3126, 0.7152, 0.2722));
    
	if(brightness > 1.0)
        BrightColor = vec4(result.rgb, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 0.0);
}