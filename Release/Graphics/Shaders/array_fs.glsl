#version 330 core

in vec4 outColor;

out vec4 col;

void main()
{
	vec4 tempColor = outColor;
	if(tempColor.a == 0)
		discard;
		
	col = tempColor;
}