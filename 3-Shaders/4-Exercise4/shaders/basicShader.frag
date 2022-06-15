#version 330 core

in vec3 colorb;
out vec4 FragColor;

void main() {
    FragColor = vec4(colorb, 1.);
}
