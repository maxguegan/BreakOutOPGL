#version 330 core
layout (location = 0) in vec4 aVertex; //


uniform mat4 projection;
uniform vec2 offset;
uniform vec4 color;

out vec2 texCoord;
out vec4 partColor;

void main(){
float scale = 10.0f;
texCoord = aVertex.zw;
partColor = color;
gl_Position  = projection  * vec4((aVertex.xy * scale) + offset,0.0f,1.0f);

}