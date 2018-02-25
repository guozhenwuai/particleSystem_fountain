#version 330 core
in vec3 TexCoords;
out vec4 color;

uniform samplerCube skybox;
struct Light
{
	vec3 ambient;
	vec3 diffuse;
};

uniform Light light;

void main()
{
	vec3 factor = light.ambient * 2 + light.diffuse;
    color = vec4(texture(skybox, TexCoords).xyz * 
		vec3(min(factor.x, 1.0f), min(factor.y, 1.0f), min(factor.z, 1.0f)), 1.0f);
}