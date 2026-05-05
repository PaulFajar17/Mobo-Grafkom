#version 330 core
out vec4 FragColor;

// uniform vec3 lightColor; // We could pass it in, but usually the cube is just white

void main()
{
    // FragColor = vec4(lightColor, 1.0);
    FragColor = vec4(1.0); // set all 4 vector values to 1.0
}
