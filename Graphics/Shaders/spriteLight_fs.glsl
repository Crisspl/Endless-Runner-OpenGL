#version 330 core

struct Light
{
	vec3 direction;
	vec3 position;
	vec4 color;
	float linear;
	float quadratic;
	float cutOff;
	float outerCutOff;
	int type;
};

in vec2 fragTexCoords;
in vec3 FragPos;

uniform sampler2D texSampler;
uniform vec4 color;
uniform Light light;

out vec4 outColor;

void main()
{
	vec4 tempColor = texture(texSampler, fragTexCoords);
	if(tempColor.a == 0)
		discard;
		
	vec3 ambient;
	
	if(light.type == 0)
		ambient = light.color.xyz * vec3(texture(texSampler, fragTexCoords));
	else if(light.type == 1)
	{
		float distance = length(light.position - FragPos);
		float attenuation = 1.f / (1.f + light.linear * distance + light.quadratic * pow(distance, 2));
			
		ambient = light.color.xyz * vec3(texture(texSampler, fragTexCoords)) * attenuation;
	}
	else if(light.type == 2)
	{
		vec3 lightDir = normalize(light.position - FragPos); 
		float angleCos = dot(lightDir, normalize(-light.direction));
		float intensity = clamp((angleCos - light.outerCutOff) / (light.cutOff - light.outerCutOff), 0.f, 1.f);
		
		ambient = light.color.xyz * vec3(texture(texSampler, fragTexCoords)) * intensity;
	}
		
	outColor = tempColor * color * vec4(ambient, 1.f);
}

