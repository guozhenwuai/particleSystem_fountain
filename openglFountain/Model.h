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
	/*  成员函数   */
	Model();
	Model(GLchar* path);
	void loadModel(std::string path);
	void Draw(Shader *shader);
	double getMaxDiff();
	void setTex(Texture t);
	void clearTex();
private:
	/*  模型数据  */
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;

	glm::vec3 vertMin;
	glm::vec3 vertMax;

	/*  私有成员函数   */
	
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};