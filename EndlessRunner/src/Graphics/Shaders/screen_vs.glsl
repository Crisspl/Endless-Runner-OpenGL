#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

out vec2 outTexCoords;

void main()
{
	outTexCoords = texCoords;
	gl_Position = vec4(position - vec2(1.f, 1.f), vec2(0.f , 1.f));
}