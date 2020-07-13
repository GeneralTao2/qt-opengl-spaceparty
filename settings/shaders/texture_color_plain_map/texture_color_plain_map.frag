#version 420 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D plain;
uniform vec3 color;
uniform vec4 textureCoords;

void main()
{
    FragColor = texture(plain, textureCoords.xy + vec2(TexCoord.x * textureCoords.z, TexCoord.y * textureCoords.w));
}
