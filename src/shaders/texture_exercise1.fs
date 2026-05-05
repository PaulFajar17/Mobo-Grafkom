#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // Exercise 1: Flip the happy face horizontally
    // Hanya texture2 (awesomeface) yang di-flip, texture1 (container) tetap normal
    FragColor = mix(texture(texture1, TexCoord),
                    texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
}
