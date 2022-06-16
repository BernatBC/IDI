#version 330 core

in vec3 vertex;
uniform float scale;
uniform mat4 TG;

void main()  {
    gl_Position = TG*vec4 (vertex*scale, 1.0);
}
