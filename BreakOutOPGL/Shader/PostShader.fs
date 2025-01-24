#version 330 core

in vec2 texCoor;

out vec4 FragColor;

uniform sampler2DMS frameTexture;

void main(){
	ivec2 screenCoord = ivec2(gl_FragCoord.x ,gl_FragCoord.y);
	vec4 sample1 = texelFetch(frameTexture,screenCoord,0);
	vec4 sample2 = texelFetch(frameTexture,screenCoord,1);
	vec4 sample3 = texelFetch(frameTexture,screenCoord,2);
	vec4 sample4 = texelFetch(frameTexture,screenCoord,3);
	vec4 color = (sample1 + sample2 + sample3 + sample4)/ 4.0f;

	//espace traitement post effet


	FragColor = color;
}