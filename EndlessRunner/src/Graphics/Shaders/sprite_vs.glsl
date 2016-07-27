#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform mat4 view;
uniform mat4 projection;

out vec2 fragTexCoords;

void main()
{
	fragTexCoords = texCoords;
	gl_Position.xy = position;
	gl_Position.zw = vec2(0.f, 1.f);
	gl_Position = projection * view * translation * rotation * scale * gl_Position;
}