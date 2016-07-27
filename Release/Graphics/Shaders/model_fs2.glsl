#version 330 core

struct Material
{
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	float shininess;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 color;

uniform Material material;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	float ambientStrength = 0.1f;
	vec3 ambient = lightColor * ambientStrength;
	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diffStrength = max(dot(norm, lightDir), 0.f);
	vec3 diffuse = diffStrength * lightColor;
	
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow( max( dot(viewDir, reflectDir), 0.0f), material.shininess); //32 is shininess
	vec3 specular = specularStrength * spec * lightColor;
	
	vec3 result = vec3(texture(material.texture_diffuse1, TexCoords)) * (ambient + diffuse + specular);

	color = vec4(result, 1.0);
}