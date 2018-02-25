#include "Emitter.h"

double randf(double range) {
	return (double)rand() / (double)RAND_MAX * range * 2 - range;
}

Emitter::Emitter()
	: emitAllowed(true)
{

}

Emitter::Emitter(glm::vec3 pos, float speed, float theta, float gama, glm::vec3 accel, glm::vec3 scale, int emitNum, Object *obj,
	double dv, double ds, double da, double dr, double zh)
	: position(pos)
	, emitSpeed(speed)
	, initSpeed(speed)
	, theta(theta)
	, gama(gama)
	, acceleration(accel)
	, scale(scale)
	, emitNumPerFrame(emitNum)
	, obj(obj)
	, deltaSpeed(dv)
	, deltaScale(ds)
	, deltaAngle(da)
	, deltaRadius(dr)
	, zeroHeight(zh)
	, emitAllowed(true)
{

}

void Emitter::resetSpeed() {
	emitSpeed = initSpeed;
}

void Emitter::allowEmit(bool status) {
	emitAllowed = status;
}

void Emitter::reset() {
	int size = touchFloorParticles.size();
	for (int i = 0; i < size; i++) {
		delete touchFloorParticles[i];
	}
	touchFloorParticles.clear();
	size = particles.size();
	for (int i = 0; i < size; i++) {
		delete particles[i];
	}
	particles.clear();
}

void Emitter::pause(Shader *shader) {
	int size = particles.size();
	Particle *particle;
	for (std::vector<Particle *>::iterator it = particles.begin(); it != particles.end();it++) {
		particle = *it;
		particle->render(shader);
	}
}

void Emitter::render(Shader *shader, float delta) {
	if (emitAllowed) {
		emitParticle();
	}
	int size = touchFloorParticles.size();
	for (int i = 0; i < size; i++) {
		delete touchFloorParticles[i];
	}
	touchFloorParticles.clear();
	size = particles.size();
	Particle *particle;
	for (std::vector<Particle *>::iterator it = particles.begin(); it != particles.end();) {
		particle = *it;
		particle->update(delta);
		if (touchZeroHeight(particle)) {
			touchFloorParticles.push_back(particle);
			it = particles.erase(it);
		}
		else {
			particle->render(shader);
			it++;
		}
	}
}

bool Emitter::touchZeroHeight(Particle *particle) {
	if (particle->getPosition().y < zeroHeight) {
		return true;
	}
	return false;
}

void Emitter::emitParticle() {
	Particle *particle;
	glm::vec3 pos;
	double scaleFactor = obj->getSuggestScale();
	double randScale = randf(deltaScale);
	glm::vec3 scl;
	glm::vec3 speed;
	glm::vec3 accel;
	glm::vec3 tempV;
	float sp;
	float cd, sd, ct, st, cg, sg, ca, sa;
	double alpha;
	for (int i = 0; i < emitNumPerFrame; i++) {
		alpha = randf(2 * PI);
		cd = cos(deltaAngle);
		sd = sin(deltaAngle);
		ct = cos(theta);
		st = sin(theta);
		cg = cos(gama);
		sg = sin(gama);
		ca = cos(alpha);
		sa = sin(alpha);
		pos.x = position.x + randf(deltaRadius);
		pos.y = position.y + randf(deltaRadius);
		pos.z = position.z + randf(deltaRadius);
		scl.x = scale.x * scaleFactor + randScale;
		scl.y = scale.y * scaleFactor + randScale;
		scl.z = scale.z * scaleFactor + randScale;
		sp = emitSpeed + randf(deltaSpeed);
		
		speed.x = sp * (sqrt(cg*cg + st*st*sg*sg)*sd*ca + ct*sg*cd);
		speed.y = sp * (sg*sd + cg*cd);
		speed.z = sp * (sqrt(cg*cg + ct*ct*sg*sg)*sd*sa + st*sg*cd);
		accel = acceleration;
		particle = new Particle(pos, scl, speed, accel, obj);
		particles.push_back(particle);
	}
}

void Emitter::renewSpeed(float dSpeed) {
	emitSpeed += dSpeed;
	if (emitSpeed <= 0.5f) {
		emitSpeed = 0.5f;
	}
}

void Emitter::renewTheta(float dtheta) {
	theta += dtheta + 2 * PI;
	theta = fmodf(theta, 2 * PI);
}

void Emitter::renewGama(float dgama) {
		float p = PI / 2 - gama;
		p += dgama;
		if (p < - PI / 2) {
			gama = -p - PI / 2;
		}
		else if (p < 0) {
			gama = PI / 2 - p;
			theta += PI;
		}
		else if (p > PI / 2) {
			gama = p - PI / 2;
			theta += PI;
		}
		else {
			gama = PI / 2 - p;
		}
}

void Emitter::renewEmitNum(int dNum) {
	emitNumPerFrame += dNum;
	if (emitNumPerFrame < 0) {
		emitNumPerFrame = 0;
	}
}

void Emitter::renewDeltaAngle(float ddelta) {
	deltaAngle += ddelta;
	if (deltaAngle < 0) {
		deltaAngle = 0;
	}
	else if (deltaAngle >= PI / 2) {
		deltaAngle = PI / 16 * 7;
	}
}

std::vector<Particle *> &Emitter::getFloorParticles() {
	return touchFloorParticles;
}

void Emitter::setScale(glm::vec3 scl) {
	scale = scl;
}

void Emitter::setEmitSpeed(float s) {
	emitSpeed = s;
	if (emitSpeed <= 0.5f) {
		emitSpeed = 0.5f;
	}
}

void Emitter::setEmitNumPerFrame(int num) {
	emitNumPerFrame = num;
}

void Emitter::setDeltaScale(double delta) {
	deltaScale = delta;
}

void Emitter::setObject(Object *newObj) {
	obj = newObj;

	int size = particles.size();
	Particle *particle;
	for (int i = 0; i < size; i++) {
		particle = particles[i];
		particle->setObj(newObj);
	}
}

void Emitter::setAccel(glm::vec3 accel) {
	acceleration = accel;

	int size = particles.size();
	Particle *particle;
	for (int i = 0; i < size; i++) {
		particle = particles[i];
		particle->setAccel(accel);
	}
}

void Emitter::setDeltaAngle(double delta) {
	deltaAngle = delta;
}

void Emitter::setDeltaRadius(double radius) {
	deltaRadius = radius;
}

void Emitter::setDeltaSpeed(double delta) {
	deltaSpeed = delta;
}