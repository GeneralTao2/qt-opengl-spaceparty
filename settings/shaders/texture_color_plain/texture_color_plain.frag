#version 420 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D plain;
uniform vec3 color;

void main()
{
    FragColor = texture(plain, TexCoord);
}
