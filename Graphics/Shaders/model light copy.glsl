#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 Normal;
out vec3 FragPos;
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
	Normal = mat3(transpose(inverse(model))) * normal; //it cuts off translation and rotation and also non-uniform scaling effect
	FragPos = vec3(model * vec4(position, 1.f));
}