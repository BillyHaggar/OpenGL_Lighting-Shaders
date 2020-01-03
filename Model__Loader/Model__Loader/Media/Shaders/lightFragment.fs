#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform vec3 lightColor;

void main()
{
    FragColor = vec4(lightColor, 1.0f); // set alle 4 vector values to 1.0

	 // check whether fragment output is higher than threshold, if so output as brightness color
    float brightness = dot(lightColor.rgb, vec3(1.2126, 1.3152, 1.1722));
    
	if(brightness > 1.0)
        BrightColor = vec4(lightColor.rgb, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 0.0);

}