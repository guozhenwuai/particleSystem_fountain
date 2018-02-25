#include "Light.h"
#include <math.h>

#define SENSITIVITY 5.0f

Light::Light()
	: radius(30)
	, sigma(60)
	, speed(5)
{
}

Light::Light(double r, double sig, double s)
	: radius(r)
	, sigma(sig)
	, speed(s)
{}

Light::~Light()
{
}

void Light::update(float delta) {
	sigma += speed * delta;
	sigma = fmod(sigma, 360);
}

void Light::dayNightSwitch() {
	sigma += 180.0;
	sigma = fmod(sigma, 360);
}

void Light::speedUp(GLfloat delta) {
	speed += delta * SENSITIVITY;
}

void Light::speedDown(GLfloat delta) {
	speed -= delta * SENSITIVITY;
	if (speed <= 0) {
		speed = 0;
	}
}

glm::vec3 Light::getLightPos() {
	glm::vec3 pos;
	double sig;
	if (sigma < 180) {
		sig = sigma;
	}
	else {
		sig = sigma - 180;
	}
	if (sig < 15) {
		sig = 15;
	}
	else if (sig > 165) {
		sig = 165;
	}
	sig = sig * PI / 180;
	pos.x = radius * cos(sig);
	pos.y = radius * sin(sig);
	pos.z = 0;
	return pos;
}

glm::vec3 Light::getAmbient() {
	return getCoordParam(lowSunA, highSunA, lowMoonA, highMoonA);
}

glm::vec3 Light::getDiffuse() {
	return getCoordParam(lowSunD, highSunD, lowMoonD, highMoonD);
}

glm::vec3 Light::getSpecular() {
	return getCoordParam(lowSunS, highSunS, lowMoonS, highMoonS);
}

glm::vec3 Light::getCoordParam(glm::vec3 &lowSun, glm::vec3 &highSun, glm::vec3 &lowMoon, glm::vec3 &highMoon) {
	glm::vec3 lowColor;
	glm::vec3 highColor;
	glm::vec3 color;
	double sig;
	bool low = false;
	if (sigma < 180) {
		sig = sigma;
		lowColor = lowSun;
		highColor = highSun;
	}
	else {
		sig = sigma - 180;
		lowColor = lowMoon;
		highColor = highMoon;
	}
	if (sig < 15 || sig > 165) {
		low = true;
	}
	if (sig > 90) sig = 180 - sig;
	if (low) {
		color = (lowColor - dftLight) * (float)(sig / 15) + dftLight;
	}
	else color = (highColor - lowColor) * (float)sin(0.6 * PI * sig / 180 - PI / 10) + lowColor;
	return color;
}