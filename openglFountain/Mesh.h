#pragma once
#include "glhead.h"
#include "Shader.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	GLuint id;
	std::string type;
	aiString path;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> texture);
	void Draw(Shader *shader, GLenum mode = GL_TRIANGLES);
	void clear();

private:
	GLuint VAO, VBO, EBO;
	void setupMesh();
	void renewMesh();
};