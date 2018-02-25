#pragma once
#include <vector>
#include "glhead.h"
#include "Mesh.h"

struct Oscillator {
	float speedY;
	float newY;
};

class Pool
{
public:
	Pool(glm::vec3 center, double x, double z, double height, double dist);
	Pool(glm::vec3 center, double x, double z, double height, double dist, GLchar *bottomPath);
	void setDistance(double dist);
	void reset();
	void render(Shader *shader, float delta);
	void splash(double x, double z, double splash);
	void setTexture(char *path);
	GLint getTextureId();

private:
	int numX;
	int numZ;
	glm::vec3 centerPos;
	double lenX;
	double lenZ;
	int indiceNum;
	double height;
	double distance;
	float texRepeat = 3.0f;
	GLuint VAO, VBO, EBO;
	Mesh mesh;
	std::vector<Oscillator> oscillators;

	GLuint textureId;

	void update(float delta);
};