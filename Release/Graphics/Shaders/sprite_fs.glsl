#version 330 core

in vec2 fragTexCoords;

uniform sampler2D texSampler;
uniform vec4 color;

out vec4 outColor;

void main()
{
	vec4 tempColor = texture(texSampler, fragTexCoords);
	if(tempColor.a == 0)
		discard;
		
	outColor = tempColor * color;
}