#pragma once
#include "glhead.h"
#include "Mesh.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

class Model
{
public:
	/*  ��Ա����   */
	Model();
	Model(GLchar* path);
	void loadModel(std::string path);
	void Draw(Shader *shader);
	double getMaxDiff();
	void setTex(Texture t);
	void clearTex();
private:
	/*  ģ������  */
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;

	glm::vec3 vertMin;
	glm::vec3 vertMax;

	/*  ˽�г�Ա����   */
	
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};