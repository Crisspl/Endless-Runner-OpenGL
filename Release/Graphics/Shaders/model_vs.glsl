#version 330 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	mat4 model = translation * rotation * scale;
	gl_Position = projection * view * model * vec4(position, 1.0f);
	TexCoords = texCoords;
}