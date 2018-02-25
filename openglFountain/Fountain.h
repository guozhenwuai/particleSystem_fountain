#pragma once
#include "glhead.h"
#include "Pool.h"
#include "Emitter.h"
#include "Basin.h"
#include <vector>

class Fountain
{
public:
	Fountain();
	Fountain(glm::vec3 position, double poolWidth, double poolHeight);
	Fountain(glm::vec3 position, double poolWidth, double poolHeight, GLchar *pathObj, GLchar *pathBasin, GLchar *pathBottom);
	~Fountain();
	void setAttri(glm::vec3 pos, double px, double pz);
	void render(Shader *basinShader, Shader *poolShader, Shader *particleShader, float delta);
	void play();
	void clearEmitters();
	Emitter *addEmitter(glm::vec3 pos, float speed, float theta, float gama, glm::vec3 accel, glm::vec3 scale, int emitNum);
	Emitter *addEmitter(glm::vec3 pos, float speed, float theta, float gama, glm::vec3 accel, glm::vec3 scale, int emitNum,
		double dv, double ds, double da, double dr);
	void loadObject(GLchar *filename);
	void resetObject();
	void setWaterColor(glm::vec4 c);

private:
	std::vector<Emitter *> emitters;
	Basin *basin;
	Pool *pool;
	Object *obj;
	glm::vec3 position;
	glm::vec4 color;
	double poolX;
	double poolZ;
	bool playStatus = true;

	void dealWithSplash(std::vector<Particle *> &particles);
	GLint getPoolBottom();
};