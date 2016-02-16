#version 150

out vec4 ret;
in vec2 texc;

uniform sampler2D tex;

void main()
{
    ret = texture(tex, texc);
}
