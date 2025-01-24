#version 330 core
layout (location = 0) in vec4 aVertex; 

out vec2 texCoor;

uniform bool chaos;
uniform bool inverse;
uniform bool shake;

uniform float time;

void main(){
	
	vec2 tex = aVertex.zw;
	gl_Position = vec4(aVertex.x,aVertex.y,0.0f,1.0f);

	if(chaos){
		float strength = 0.3f;
		vec2 pos = vec2(tex.x + sin(time) * strength, tex.y + cos(time) * strength);

		texCoor = pos;

	}else if(inverse){
		texCoor = vec2(1.0f - tex.x, 1.0 - tex.y);
	}else {
		texCoor = tex;
	}
	if(shake){
		float strength = 0.01f;
		gl_Position.x += cos(time * 10) * strength;
		gl_Position.y += cos(time * 15) * strength;
	}
	
}