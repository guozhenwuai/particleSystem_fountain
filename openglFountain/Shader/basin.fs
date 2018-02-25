#version 330 core
out vec4 FragColor;

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec2 TexCoords;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D texture_diffuse1;

uniform vec3 viewPos;
uniform Light light;

void main()
{    
	Material material;
	material.ambient = vec3(0.3, 0.3, 0.3);
	material.diffuse = vec3(0.2, 0.2, 0.2);
	material.specular = vec3(0.2, 0.2, 0.2);
	material.shininess = 12.0f;
	
	vec3 ambient = light.ambient * material.ambient;
	
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), material.shininess);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);
	
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);
	
	vec3 result = (ambient + diffuse + specular) * texture(texture_diffuse1, TexCoords).xyz;
	FragColor = vec4(result, 1.0f);
}