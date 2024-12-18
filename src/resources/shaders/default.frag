#version 330 core
in vec3 ourColor;
out vec4 FragColor;

uniform sampler2D tex0;
in vec2 texcoord;

void main()
{
    FragColor = texture(tex0,texcoord);
}