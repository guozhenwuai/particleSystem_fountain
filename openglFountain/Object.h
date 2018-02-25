#pragma once
#include "glhead.h"
#include "Model.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>


class Object
{
public:
	Object(GLchar *defaultModel);
	~Object();
	double getSuggestScale();
	//    int genDrawListId();
	void draw(Shader *shader);
	void setTexture(GLchar *texPath);
	void reset();
	void loadModel(GLchar *path);

private:
	enum State { NONE, LOADED };
	State objStatus;
	double radius;
	Model dftModel;
	Model model;

	GLuint textureId;
};
