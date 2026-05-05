#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

void main()
{
    // Exercise 4: Use uniform mixValue (controlled by arrow keys)
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue);
}
