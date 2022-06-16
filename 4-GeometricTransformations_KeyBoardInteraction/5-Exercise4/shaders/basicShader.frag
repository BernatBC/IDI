#version 330 core

in vec3 ColorOUT;
out vec4 FragColor;

void main() {
    FragColor = vec4(ColorOUT, 1);
}
