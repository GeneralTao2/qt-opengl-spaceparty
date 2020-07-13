#version 440 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float kernelMat[9];
uniform float offset;
uniform int mode;
uniform float gamma;
uniform float exposure;

vec4 inversion();
vec4 grayscale();
vec4 kernel();


void main()
{
    vec4 color;
    if(mode == 0) {
        color = texture(screenTexture, TexCoords);
    } else if(mode == 1) {
        color = kernel();
    } else if(mode == 2) {
        color = grayscale();
    } else if(mode == 3) {
        color = inversion();
    }

    FragColor = color;
    FragColor.rgb = vec3(1.0) - exp(-FragColor.rgb * exposure);
    FragColor.rgb = pow(FragColor.rgb, vec3(1.0/gamma));
}

vec4 inversion() {
    return vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);
}

vec4 grayscale() {
    vec4 color = texture(screenTexture, TexCoords);
    float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
    return vec4(average, average, average, 1.0);
}

vec4 kernel() {
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right
    );

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernelMat[i];

    return vec4(col, 1.0);
}
