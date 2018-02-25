#version 330 core
out vec4 color;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;

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
uniform Light light;
uniform vec3 viewPos;
uniform vec4 objectColor;
uniform sampler2D bottom;
uniform samplerCube skybox;

void main()
{    
	Material material;
	material.ambient = vec3(0.4, 0.4, 0.4);
	material.diffuse = vec3(0.05, 0.05, 0.05);
	material.specular = vec3(1.0, 1.0, 1.0);
	material.shininess = 12.0f;
	float refractRatio = 1.00 / 1.33;
	float depth = fragPos.y;
	float objColorEfficient = objectColor.w;
	
	vec3 ambient = light.ambient * material.ambient;
	
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), material.shininess);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);
	
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);
	
	vec4 reflect = texture(skybox, reflect(-viewDir, norm));
	
	float theta = degrees(abs(asin(viewDir.y / length(viewDir))));

	float factor = 0.0f;
	if(theta > 15){
		factor = (theta - 15) / 75.0f;
	}
	
	vec3 refractDir = refract(viewDir, norm, refractRatio);
	float depthRatio = depth / reflectDir.y;
	vec2 newTexCoord = (reflectDir * depthRatio).xz + texCoords;
	
	vec3 refract = texture(bottom, newTexCoord).xyz * factor;
	
	vec3 result = (ambient + diffuse + specular) * 
	(refract * (1 - objColorEfficient) + objectColor.xyz * objColorEfficient);
	color = vec4(result + reflect.xyz * (light.ambient + light.diffuse), objColorEfficient);
}