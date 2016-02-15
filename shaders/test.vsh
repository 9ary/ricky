#version 150

in vec2 position;

const mat4 P = mat4(vec4(2.0/640, 0, 0, 0),
        vec4(0, -2.0/480, 0, 0),
        vec4(0, 0, -2, 0),
        vec4(-1 + (1.0/640), 1 - (1.0/480), -1, 1));

void main()
{
    gl_Position = P * vec4(position, 0, 1);
}
