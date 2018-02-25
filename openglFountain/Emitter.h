#pragma once
#include <vector>
#include "Particle.h"

class Emitter
{
public:
	Emitter();
	Emitter(glm::vec3 pos, float speed, float theta, float gama, glm::vec3 accel, glm::vec3 scale, int emitNum, Object *obj,
		double dv = 0.05f, double ds = 0.05f, double da = 0.1, double dr = 0.1f, double zh = 0);
	void pause(Shader *shader);
	void reset();
	void render(Shader *shader, float delta);
	void allowEmit(bool status);
	void setAccel(glm::vec3 accel);
	void setEmitSpeed(float speed);
	void setDeltaSpeed(double delta);
	void setDeltaAngle(double delta);
	void setDeltaRadius(double radius);
	void setEmitNumPerFrame(int num);
	void setScale(glm::vec3 scl);
	void setDeltaScale(double delta);
	void setObject(Object *obj);
	void renewSpeed(float dSpeed);
	void renewTheta(float dtheta);
	void renewGama(float gama);
	void renewEmitNum(int dNum);
	void renewDeltaAngle(float ddelta);
	void resetSpeed();
	std::vector<Particle *> &getFloorParticles();

private:
	std::vector<Particle *> particles;
	std::vector<Particle *> touchFloorParticles;
	glm::vec3 position;
	float initSpeed;
	float emitSpeed;
	float theta;
	float gama;
	glm::vec3 acceleration;
	glm::vec3 scale;
	double deltaSpeed;
	double deltaScale;
	double deltaAngle;
	double deltaRadius;
	double zeroHeight;
	int emitNumPerFrame;
	bool emitAllowed;

	Object *obj;

	void emitParticle();
	bool touchZeroHeight(Particle *particle);
};