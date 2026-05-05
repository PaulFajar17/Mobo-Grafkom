#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main()
{
    // Flip the y-axis to draw the triangle upside down
    gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0);
    ourColor = aColor;
}
