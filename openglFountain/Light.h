#pragma once
#include "glhead.h"
class Light
{
public:
	Light();
	Light(double r, double sig, double speed);
	~Light();
	void update(float delta);
	void speedUp(GLfloat deltaTime);
	void speedDown(GLfloat deltaTime);
	void dayNightSwitch();
	glm::vec3 getLightPos();
	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();

private:
	double radius;
	double sigma;
	double speed;
	glm::vec3 dftLight = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 lowSunA = glm::vec3(0.2, 0.2, 0.2);
	glm::vec3 highSunA = glm::vec3(0.45, 0.45, 0.4);
	glm::vec3 lowMoonA = glm::vec3(0.04, 0.04, 0.06);
	glm::vec3 highMoonA = glm::vec3(0.1, 0.1, 0.16);
	glm::vec3 lowSunD = glm::vec3(0.32, 0.3, 0.3);
	glm::vec3 highSunD = glm::vec3(0.5, 0.5, 0.5);
	glm::vec3 lowMoonD = glm::vec3(0.1, 0.1, 0.15);
	glm::vec3 highMoonD = glm::vec3(0.25, 0.25, 0.3);
	glm::vec3 lowSunS = glm::vec3(0.9, 0.4, 0.1);
	glm::vec3 highSunS = glm::vec3(1, 1, 1);
	glm::vec3 lowMoonS = glm::vec3(0.4, 0.4, 0.1);
	glm::vec3 highMoonS = glm::vec3(0.7, 0.8, 0.6);

	glm::vec3 getCoordParam(glm::vec3 &lowSun, glm::vec3 &highSun, glm::vec3 &lowMoon, glm::vec3 &highMoon);
};

