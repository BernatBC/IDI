#version 330 core

in vec3 vertex;

void main()  {
    gl_Position = vec4 (vertex.x * 0.5, vertex.y * 0.5, vertex.z, 1.0);
}
