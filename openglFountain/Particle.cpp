#include "Particle.h"

Particle::Particle()
	: position(glm::vec3(0, 0, 0))
	, scale(glm::vec3(1, 1, 1))
	, velocity(glm::vec3(0, 0, 0))
	, acceleration(glm::vec3(0, 0, 0))
	, obj(NULL)
{
}

Particle::Particle(glm::vec3 pos, glm::vec3 scl, Object *obj)
	: position(pos)
	, scale(scl)
	, velocity(glm::vec3(0, 0, 0))
	, acceleration(glm::vec3(0, 0, 0))
	, obj(obj)
{
}

Particle::Particle(glm::vec3 pos, glm::vec3 scl, glm::vec3 velo, glm::vec3 accel, Object *obj)
	: position(pos)
	, scale(scl)
	, velocity(velo)
	, acceleration(accel)
	, obj(obj)
{
}

void Particle::update(float delta) {
	//position = velocity + 0.5f * acceleration * delta * delta;
	position.x = position.x + velocity.x * delta + 0.5 * acceleration.x * delta * delta;
	position.y = position.y + velocity.y * delta + 0.5 * acceleration.y * delta * delta;
	position.z = position.z + velocity.z * delta + 0.5 * acceleration.z * delta * delta;
	velocity.x = velocity.x + acceleration.x * delta;
	velocity.y = velocity.y + acceleration.y * delta;
	velocity.z = velocity.z + acceleration.z * delta;
}

void Particle::render(Shader *shader) {
	glm::mat4 model;
	model = glm::translate(model, position);
	model = glm::scale(model, scale);
	shader->Use();
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform1f(glGetUniformLocation(shader->Program, "unparentness"), calcUnparentness());
	obj->draw(shader);
}

void Particle::setAccel(glm::vec3 accel) {
	acceleration = accel;
}

glm::vec3 Particle::getPosition() {
	return position;
}

glm::vec3 Particle::getVelocity() {
	return velocity;
}

void Particle::setParameter(glm::vec3 pos, glm::vec3 scl, glm::vec3 velo, glm::vec3 accel, Object *o) {
	position = pos;
	scale = scl;
	velocity = velo;
	acceleration = accel;
	obj = o;
}

void Particle::setObj(Object *o) {
	obj = o;
}

float Particle::calcUnparentness() {
	float s;
	if (velocity.y < 0) {
		s = fabs(velocity.y);
		if (s < midS) {
			return midP;
		}
		else if (s > highS) {
			return lowP;
		}
		return (lowP - midP) / (highS - midS) * (s - midS) + midP;
	}
	s = glm::length(velocity);
	if (s < lowS) {
		return midP;
	}
	else if (s > highS) {
		return highP;
	}
	return (highP - midP) / (highS - lowS) * (s - lowS) + midP;
}