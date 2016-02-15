#version 150

layout(points) in;
layout(triangle_strip, max_vertices = 5) out;

void main()
{
    gl_Position = gl_in[0].gl_Position + vec4(0, 0, 0, 0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(24.0 * 2 / 640, 0, 0, 0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(24.0 * 2 / 640, -24.0 * 2 / 480, 0, 0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0, -24.0 * 2 / 480, 0, 0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0, 0, 0, 0);
    EmitVertex();

    EndPrimitive();
}
