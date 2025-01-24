#version 330 core

in vec2 texCoord;
in vec4 partColor;
uniform sampler2D aTexture;

out vec4 FragColor;

void main(){
	vec4 color = texture(aTexture,texCoord) *  partColor;
	if(color.w <= 0.0f)discard;
	 FragColor = color;
}