#pragma once
#include "glhead.h"
#include "Mesh.h"



class Skybox
{
public:
	Skybox();
	Skybox(char *upPath, char *downPath, char *leftPath, char *rightPath, char *frontPath, char *backPath);
	~Skybox();
	void setPaths(char *upPath, char *downPath, char *leftPath, char *rightPath, char *frontPath, char *backPath);
	void setUp(char *path);
	void setDown(char *path);
	void setLeft(char *path);
	void setRight(char *path);
	void setFront(char *path);
	void setBack(char *path);
	void render(Shader *shader);
	GLuint getID();

private:
	enum SkyboxFaces { RIGHT = 0, LEFT, TOP, BOTTOM, BACK, FRONT };
	GLuint id;
	GLuint VAO, VBO;

	std::vector<const GLchar*> faces;

	void initVertices();
	void setTex(int index, char *path);
	void loadCubemap();
};

