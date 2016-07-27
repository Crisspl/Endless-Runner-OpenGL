#version 330 core

layout (location = 0) in vec2 position;

uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position.xy = position;
	gl_Position.zw = vec2(0.f, 1.f);
	gl_Position = projection * view * translation * rotation * scale * gl_Position;
}