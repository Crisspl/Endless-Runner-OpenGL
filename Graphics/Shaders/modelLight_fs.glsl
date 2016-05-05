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
	float illuminance;
	int type;
};

struct Material
{
	sampler2D texture_diffuse1;
	//sampler2D texture_specular1;
	float shininess;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 color;

uniform Material material;
uniform Light light[20];
uniform int lightsCount;

vec3 calcLight(Light _light, vec3 _normal, vec3 _viewDir);
vec3 calcDirLight(Light _light, vec3 _normal, vec3 _viewDir);
vec3 calcPointLight(Light _light, vec3 _normal, vec3 _viewDir);
vec3 calcSpotLight(Light _light, vec3 _normal, vec3 _viewDir);

void main()
{	
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(vec3(400, 300, 330) - FragPos);
	
	vec3 result;
	for(int i = 0; i < lightsCount; i++)
		result += calcLight(light[i], normal, viewDir);

	color = texture(material.texture_diffuse1, TexCoords) * vec4(result, 1.f);
}

vec3 calcLight(Light _light, vec3 _normal, vec3 _viewDir)
{
	vec3 ret;
	if(_light.type == 0)
		ret = calcDirLight(_light, _normal, _viewDir);
	else if(_light.type == 1)
		ret = calcPointLight(_light, _normal, _viewDir);
	else if(_light.type == 2)
		ret = calcSpotLight(_light, _normal, _viewDir);
	return ret * _light.illuminance;
}

vec3 calcDirLight(Light _light, vec3 _normal, vec3 _viewDir)
{
	vec3 lightDir = normalize(-_light.direction);
	
	float diff = max(dot(_normal, lightDir), 0.f);
	
	vec3 reflectDir = normalize(reflect(-lightDir, _normal));
	float spec = pow(max(dot(_viewDir, reflectDir), 0.f), material.shininess);
	
	vec3 diffuse = _light.color.xyz * diff;
	vec3 specular = _light.color.xyz * spec;
	
	return diffuse + specular;
}

vec3 calcPointLight(Light _light, vec3 _normal, vec3 _viewDir)
{
	vec3 lightDir = normalize(_light.position - FragPos);
	
	float diff = max(dot(_normal, lightDir), 0.f);

	vec3 reflectDir = normalize(reflect(-lightDir, _normal));
	float spec = pow(max(dot(_viewDir, reflectDir), 0.f), material.shininess);
	
	vec3 diffuse = _light.color.xyz * diff;
	vec3 specular = _light.color.xyz * spec;
	
	float distance = length(_light.position - FragPos);
	float attenuation = 1.f / (1.f + _light.linear * distance + _light.quadratic * pow(distance, 2));
	
	return (diffuse + specular) * attenuation;
}

vec3 calcSpotLight(Light _light, vec3 _normal, vec3 _viewDir)
{
	vec3 lightDir = normalize(_light.position - FragPos);
	vec3 ret = calcPointLight(_light, _normal, _viewDir);
	
	float angleCos = dot(lightDir, normalize(-_light.direction));
	float intensity = clamp((angleCos - _light.outerCutOff) / (_light.cutOff - _light.outerCutOff), 0.f, 1.f);
	
	return ret * intensity;
}