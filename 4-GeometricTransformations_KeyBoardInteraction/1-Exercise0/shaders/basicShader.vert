#version 330 core

in vec3 vertex;
uniform float scale;

void main()  {
    gl_Position = vec4 (scale*vertex, 1.0);
}
