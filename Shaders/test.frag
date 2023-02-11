#version 330 core

layout(location=0)out vec4 fragColor;

void main()
{
    vec4 color=vec4(0,0,0,1);
    
    fragColor = color.rgba;
}