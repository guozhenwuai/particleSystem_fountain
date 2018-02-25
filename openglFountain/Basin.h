#pragma once
#include "glhead.h"
#include "Mesh.h"
class Basin
{
public:
	Basin();
	Basin(glm::vec3 pos, float h, float w, float x, float z, char *tex);
	~Basin();
	void setAttr(glm::vec3 pos, float h, float w, float x, float z, char *tex);
	void setTexture(char *tex);
	void render(Shader *shader);

private:
	glm::vec3 position;
	float height;
	float borderWidth;
	float innerSizeX;
	float innerSizeZ;

	Mesh mesh;

	GLuint textureId;

	void initMeshs();
	
};

