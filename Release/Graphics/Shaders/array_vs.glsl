#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec4 color;

out vec4 outColor;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	outColor = color;
	gl_Position = projection * view * vec4(position, 0.f, 1.f);
}