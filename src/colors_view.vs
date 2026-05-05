#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;
out vec3 LightPos;

uniform vec3 lightPos; // We now pass lightPos in world space, and convert it to view space
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // Transformed position into view space
    FragPos = vec3(view * model * vec4(aPos, 1.0));
    
    // Normal into view space
    Normal = mat3(transpose(inverse(view * model))) * aNormal;
    
    // Light position into view space
    LightPos = vec3(view * vec4(lightPos, 1.0));
    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
