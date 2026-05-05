#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

uniform vec2 offset1;
uniform vec2 offset2;
uniform vec2 scale1;
uniform vec2 scale2;

void main()
{
    // Apply aspect ratio scale from the center, then add manual offset
    vec2 tc1 = (TexCoord - 0.5) * scale1 + 0.5 + offset1;
    vec2 tc2 = (TexCoord - 0.5) * scale2 + 0.5 + offset2;
	FragColor = mix(texture(texture1, tc1), texture(texture2, tc2), mixValue);
}
