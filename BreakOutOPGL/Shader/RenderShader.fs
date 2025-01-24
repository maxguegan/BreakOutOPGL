#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D aTexture;
uniform vec3 aColor;

void main()
{    
    color = vec4(aColor, 1.0) * texture(aTexture, TexCoords);
}