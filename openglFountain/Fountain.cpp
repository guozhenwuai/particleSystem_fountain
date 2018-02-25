#include "Fountain.h"


Fountain::Fountain()
	: position(glm::vec3(0, 0, 0))
	, poolX(40.0f)
	, poolZ(40.0f)
	, color(glm::vec4(1, 1, 1, 0.2))
{
	obj = new Object("./Resource/Obj/cube.obj");
	pool = new Pool(position, poolX, poolZ, 0.5, 0.4);
	basin = new Basin(glm::vec3(position.x, position.y - 0.5, position.z), 0.8f, 1.0f, poolX, poolZ, "./Resource/Textures/basin2.bmp");
}

Fountain::Fountain(glm::vec3 position, double poolWidth, double poolHeight)
	: position(position)
	, poolX(poolWidth)
	, poolZ(poolHeight)
	, color(glm::vec4(1, 1, 1, 0.2))
{
	obj = new Object("./Resource/Obj/cube.obj");
	pool = new Pool(position, poolX, poolZ, 0.5, 0.4);
	basin = new Basin(glm::vec3(position.x, position.y - 0.5, position.z), 0.8f, 1.0f, poolX, poolZ, "./Resource/Textures/basin2.bmp");
}

Fountain::Fountain(glm::vec3 position, double poolWidth, double poolHeight, GLchar *pathObj, GLchar *pathBasin, GLchar *pathBottom)
	: position(position)
	, poolX(poolWidth)
	, poolZ(poolHeight)
	, color(glm::vec4(1, 1, 0.3, 0.7f))
{
	obj = new Object(pathObj);
	pool = new Pool(position, poolX, poolZ, 0.5, 1, pathBottom);
	basin = new Basin(glm::vec3(position.x, position.y - 0.5, position.z), 2.0f, 1.0f, poolX, poolZ, pathBasin);
}

Fountain::~Fountain() {
	delete obj;
	delete pool;
	delete basin;
}

void Fountain::setWaterColor(glm::vec4 c) {
	color = c;
}

void Fountain::setAttri(glm::vec3 pos, double px, double pz) {
	position = pos;
	poolX = px;
	poolZ = pz;
}

GLint Fountain::getPoolBottom() {
	return pool->getTextureId();
}

void Fountain::play() {
	playStatus = !playStatus;
	int size = emitters.size();
	Emitter *emitter;
	for (int i = 0; i < size; i++) {
		emitter = emitters[i];
		emitter->allowEmit(playStatus);
	}
}

void Fountain::clearEmitters() {
	int size = emitters.size();
	Emitter *emitter;
	for (int i = 0; i < size; i++) {
		emitter = emitters[i];
		delete emitter;
	}
	emitters.clear();
}

void Fountain::loadObject(GLchar *filename) {
	obj->loadModel(filename);
	int size = emitters.size();
	Emitter *emitter;
	for (int i = 0; i < size; i++) {
		emitter = emitters[i];
		emitter->reset();
	}
}

void Fountain::resetObject() {
	obj->reset();
	int size = emitters.size();
	Emitter *emitter;
	for (int i = 0; i < size; i++) {
		emitter = emitters[i];
		emitter->reset();
	}
}

Emitter *Fountain::addEmitter(glm::vec3 pos, float speed, float theta, float gama, glm::vec3 accel, glm::vec3 scale, int emitNum) {
	if (pos.x < -poolX / 2 || pos.x > poolX / 2 || pos.z < -poolZ / 2 || pos.z > poolZ / 2)return NULL;
	Emitter *emitter = new Emitter(glm::vec3(pos.x + position.x, pos.y + position.y, pos.z + position.z),
		speed, theta, gama, accel, scale, emitNum, obj);
	emitters.push_back(emitter);
	return emitter;
}

Emitter *Fountain::addEmitter(glm::vec3 pos, float speed, float theta, float gama, glm::vec3 accel, glm::vec3 scale, int emitNum,
	double dv, double ds, double da, double dr) {
	if (pos.x < -poolX / 2 || pos.x > poolX / 2 || pos.z < -poolZ / 2 || pos.z > poolZ / 2)return NULL;
	Emitter *emitter = new Emitter(glm::vec3(pos.x + position.x, pos.y + position.y, pos.z + position.z),
		speed, theta, gama, accel, scale, emitNum, obj,
		dv, ds, da, dr, position.y);
	emitters.push_back(emitter);
	return emitter;
}

void Fountain::render(Shader *basinShader, Shader *poolShader, Shader *particleShader, float delta) {
	poolShader->Use();
	glUniform4f(glGetUniformLocation(poolShader->Program, "objectColor"), color.x, color.y, color.z, color.w);
	particleShader->Use();
	glUniform4f(glGetUniformLocation(particleShader->Program, "objectColor"), color.x, color.y, color.z, color.w);
	basin->render(basinShader);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	pool->render(poolShader, delta);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	int size = emitters.size();
	Emitter *emitter;
	for (int i = 0; i < size; i++) {
		emitter = emitters[i];
		emitter->render(particleShader, delta);
		dealWithSplash(emitter->getFloorParticles());
	}
	glDisable(GL_BLEND);
}

void Fountain::dealWithSplash(std::vector<Particle *> &particles) {
	Particle *particle;
	int size = particles.size();
	for (int i = 0; i < size; i++) {
		particle = particles[i];
		pool->splash(particle->getPosition().x, particle->getPosition().z, -0.02);
	}
}
