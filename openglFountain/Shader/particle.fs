#version 330 core
out vec4 color;

in vec3 normal;
in vec3 fragPos;

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	float shininess;
};

uniform vec3 viewPos;
uniform Light light;
uniform vec4 objectColor;
uniform float unparentness;
uniform samplerCube skybox;

void main()
{    
	float objColorEfficient = objectColor.w;
	Material material;
	material.ambient = vec3(0.1, 0.1, 0.1);
	material.diffuse = vec3(0.1, 0.1, 0.1);
	material.shininess = 32.0f;
	
	
	vec3 ambient = light.ambient * material.ambient;
	
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), material.shininess);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);
	
	vec3 viewDir = normalize(viewPos - fragPos);
	
	vec3 refract = texture(skybox, -viewDir).xyz;
	
	vec3 newColor = (objectColor.xyz + vec3(1, 1, 1)) * 0.5 * objColorEfficient;
	vec3 result = (ambient + diffuse) * (refract * (1 - unparentness) + newColor * unparentness);
	
	color = vec4(result, objColorEfficient);

}