#include "Object.h"


Object::Object(GLchar *defaultModel)
{
	dftModel = Model(defaultModel);
	dftModel.clearTex();
	radius = 0.2;
	objStatus = NONE;
	glGenTextures(1, &textureId);
	setTexture("./Resource/Textures/water.bmp");
}

Object::~Object() {
}

void Object::setTexture(GLchar *path) {
	glBindTexture(GL_TEXTURE_2D, textureId);
	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	
}

double Object::getSuggestScale() {
	if (objStatus == NONE) {
		return radius / dftModel.getMaxDiff();
	}
	else {
		return radius / model.getMaxDiff();
	}
}

void Object::loadModel(GLchar *path) {
	model = Model(path);
	model.clearTex();
	objStatus = LOADED;
}

void Object::reset() {
	objStatus = NONE;
}

void Object::draw(Shader *shader) {
	shader->Use();
	glActiveTexture(GL_TEXTURE5);
	glUniform1i(glGetUniformLocation(shader->Program, "water"), 5);
	glBindTexture(GL_TEXTURE_2D, textureId);
	if (objStatus == NONE) {
		dftModel.Draw(shader);
	}
	else {
		model.Draw(shader);
	}
}