#pragma once
#include <math.h>
#include <iostream>
#include "Object.h"

class Particle
{
public:
	Particle();
	Particle(glm::vec3 pos, glm::vec3 scl, Object *obj);
	Particle(glm::vec3 pos, glm::vec3 scl, glm::vec3 velo, glm::vec3 accel, Object *obj);

	void update(float delta);
	void render(Shader *shader);
	glm::vec3 getPosition();
	glm::vec3 getVelocity();
	void setObj(Object *o);
	void setAccel(glm::vec3 accel);
	void setParameter(glm::vec3 pos, glm::vec3 scl, glm::vec3 velo, glm::vec3 accel, Object *o);

private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	Object *obj;
	float lowS = 3.5f;
	float midS = 4.0f;
	float highS = 6.0f;
	float midP = 0.6f;
	float lowP = 0.3f;
	float highP = 1.0f;

	float calcUnparentness();
};