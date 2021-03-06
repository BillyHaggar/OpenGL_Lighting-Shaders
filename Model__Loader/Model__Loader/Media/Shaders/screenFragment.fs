#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform sampler2D blurTexture;
uniform sampler2D shadowTexture;
uniform bool bloom;
uniform float exposure;

void main()
{             
    float gamma = 1.0;
    vec3 hdrColor = texture(screenTexture, TexCoords).rgb;      
    vec3 bloomColor = texture(blurTexture, TexCoords).rgb;
    if(bloom){
        hdrColor += bloomColor; // additive blending
		gamma = 0.8;
	}
    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    // also gamma correct while we're at it       
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0);
}
