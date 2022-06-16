#version 330 core

in vec3 vertex;
in vec3 ColorIN;
out vec3 ColorOUT;
uniform mat4 TG;

void main()  {
    ColorOUT = ColorIN;
    gl_Position = TG*vec4 (vertex, 1.0);
}
