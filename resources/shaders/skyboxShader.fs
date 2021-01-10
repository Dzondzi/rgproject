#version 330 core

out vec4 FragColor;

in vec3 TexCoord;

uniform samplerCube skybox;
uniform vec3 skyboxColor;

void main(){
    FragColor = texture(skybox, TexCoord) * vec4(skyboxColor, 1.0);
}