#version 430 core

out vec4 fragColor;

in vec2 otex;

uniform sampler2D tex;

void main()
{
    fragColor = texture(tex, otex);
}
