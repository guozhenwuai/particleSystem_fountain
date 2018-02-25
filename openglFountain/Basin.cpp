#include "Basin.h"


Basin::Basin()
	: position(glm::vec3(0, 0, 0))
	, height(0.8)
	, borderWidth(0.4)
	, innerSizeX(3)
	, innerSizeZ(3)
{
	glGenTextures(1, &textureId);
	setTexture("./Resource/Textures/basin2.bmp");
	initMeshs();
}

Basin::Basin(glm::vec3 pos, float h, float w, float x, float z, char *tex)
	: position(pos)
	, height(h)
	, borderWidth(w)
	, innerSizeX(x)
	, innerSizeZ(z)
{
	glGenTextures(1, &textureId);
	setTexture(tex);
	initMeshs();
}


Basin::~Basin()
{
}

void Basin::setAttr(glm::vec3 pos, float h, float w, float x, float z, char *tex) {
	position = pos;
	height = h;
	borderWidth = w;
	innerSizeX = x;
	innerSizeZ = z;
	setTexture(tex);
	initMeshs();
}

void Basin::setTexture(char *path) {
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

void Basin::initMeshs() {
	mesh.clear();
	float texBorder = borderWidth / (innerSizeX + 2 * borderWidth);
	Vertex v1, v2, v3, v4;
	GLuint i = 0;

	Texture texture;
	texture.id = textureId;
	texture.type = "texture_diffuse";
	mesh.textures.push_back(texture);

	// top surface
	v1.Normal = v2.Normal = v3.Normal = v4.Normal = glm::vec3(0.0f, 1.0f, 0.0f);

	v1.TexCoords = glm::vec2(texBorder, texBorder);
	v1.Position = glm::vec3(0.0f, height, 0.0f);
	v2.TexCoords = glm::vec2(1.0f - texBorder, texBorder);
	v2.Position = glm::vec3(innerSizeX, height, 0.0f);
	v3.TexCoords = glm::vec2(1.0f - texBorder, 0);
	v3.Position = glm::vec3(innerSizeX, height, -borderWidth);
	v4.TexCoords = glm::vec2(texBorder, 0);
	v4.Position = glm::vec3(0.0f, height, -borderWidth);
	mesh.vertices.push_back(v1);
	mesh.vertices.push_back(v2);
	mesh.vertices.push_back(v3);
	mesh.vertices.push_back(v4);
	i++;

	v1.TexCoords = glm::vec2(texBorder, 0.0f);
	v1.Position = glm::vec3(0.0f, height, -borderWidth);
	v2.TexCoords = glm::vec2(0.0f, 0.0f);
	v2.Position = glm::vec3(-borderWidth, height, -borderWidth);
	v3.TexCoords = glm::vec2(0.0f, 1.0f - texBorder);
	v3.Position = glm::vec3(-borderWidth, height, innerSizeZ);
	v4.TexCoords = glm::vec2(texBorder, 1.0f - texBorder);
	v4.Position = glm::vec3(0.0f, height, innerSizeZ);
	mesh.vertices.push_back(v1);
	mesh.vertices.push_back(v2);
	mesh.vertices.push_back(v3);
	mesh.vertices.push_back(v4);
	i++;

	v1.TexCoords = glm::vec2(1.0f, 0.0f);
	v1.Position = glm::vec3(innerSizeX + borderWidth, height, -borderWidth);
	v2.TexCoords = glm::vec2(1.0f - texBorder, 0.0f);
	v2.Position = glm::vec3(innerSizeX, height, -borderWidth);
	v3.TexCoords = glm::vec2(1.0f - texBorder, 1.0f - texBorder);
	v3.Position = glm::vec3(innerSizeX, height, innerSizeZ);
	v4.TexCoords = glm::vec2(1.0f, 1.0f - texBorder);
	v4.Position = glm::vec3(innerSizeX + borderWidth, height, innerSizeZ);
	mesh.vertices.push_back(v1);
	mesh.vertices.push_back(v2);
	mesh.vertices.push_back(v3);
	mesh.vertices.push_back(v4);
	i++;

	v1.TexCoords = glm::vec2(1.0f, 1.0f - texBorder);
	v1.Position = glm::vec3(innerSizeX + borderWidth, height, innerSizeZ);
	v2.TexCoords = glm::vec2(0.0f, 1.0f - texBorder);
	v2.Position = glm::vec3(-borderWidth, height, innerSizeZ);
	v3.TexCoords = glm::vec2(0.0f, 1.0f);
	v3.Position = glm::vec3(-borderWidth, height, innerSizeZ + borderWidth);
	v4.TexCoords = glm::vec2(1.0f, 1.0f);
	v4.Position = glm::vec3(innerSizeX + borderWidth, height, innerSizeZ + borderWidth);
	mesh.vertices.push_back(v1);
	mesh.vertices.push_back(v2);
	mesh.vertices.push_back(v3);
	mesh.vertices.push_back(v4);
	i++;

	// front
	v1.Normal = v2.Normal = v3.Normal = v4.Normal = glm::vec3(0.0f, 0.0f, 1.0f);

	v1.TexCoords = glm::vec2(texBorder, texBorder);
	v1.Position = glm::vec3(0.0f, height, 0.0f);
	v2.TexCoords = glm::vec2(1.0f - texBorder, texBorder);
	v2.Position = glm::vec3(innerSizeX, height, 0.0f);
	v3.TexCoords = glm::vec2(1.0f - texBorder, 0);
	v3.Position = glm::vec3(innerSizeX, 0.0f, 0.0f);
	v4.TexCoords = glm::vec2(texBorder, 0);
	v4.Position = glm::vec3(0.0f, 0.0f, 0.0f);
	mesh.vertices.push_back(v1);
	mesh.vertices.push_back(v2);
	mesh.vertices.push_back(v3);
	mesh.vertices.push_back(v4);
	i++;

	v1.TexCoords = glm::vec2(0.0f, 1.0f - texBorder);
	v1.Position = glm::vec3(-borderWidth, height, innerSizeZ + borderWidth);
	v2.TexCoords = glm::vec2(1.0f, 1.0f - texBorder);
	v2.Position = glm::vec3(innerSizeX + borderWidth, height, innerSizeZ + borderWidth);
	v3.TexCoords = glm::vec2(1.0f, 1.0f);
	v3.Position = glm::vec3(innerSizeX + borderWidth, 0.0f, innerSizeZ + borderWidth);
	v4.TexCoords = glm::vec2(0.0f, 0.0f);
	v4.Position = glm::vec3(-borderWidth, 0.0f, innerSizeZ + borderWidth);
	mesh.vertices.push_back(v1);
	mesh.vertices.push_back(v2);
	mesh.vertices.push_back(v3);
	mesh.vertices.push_back(v4);
	i++;

	// back
	v1.Normal = v2.Normal = v3.Normal = v4.Normal = glm::vec3(0.0f, 0.0f, -1.0f);

	v1.TexCoords = glm::vec2(texBorder, texBorder);
	v1.Position = glm::vec3(0.0f, height, innerSizeZ);
	v2.TexCoords = glm::vec2(1.0f - texBorder, texBorder);
	v2.Position = glm::vec3(innerSizeX, height, innerSizeZ);
	v3.TexCoords = glm::vec2(1.0f - texBorder, 0);
	v3.Position = glm::vec3(innerSizeX, 0.0f, innerSizeZ);
	v4.TexCoords = glm::vec2(texBorder, 0);
	v4.Position = glm::vec3(0.0f, 0.0f, innerSizeZ);
	mesh.vertices.push_back(v1);
	mesh.vertices.push_back(v2);
	mesh.vertices.push_back(v3);
	mesh.vertices.push_back(v4);
	i++;

	v1.TexCoords = glm::vec2(0.0f, 1.0f - texBorder);
	v1.Position = glm::vec3(-borderWidth, height, -borderWidth);
	v2.TexCoords = glm::vec2(1.0f, 1.0f - texBorder);
	v2.Position = glm::vec3(innerSizeX + borderWidth, height, -borderWidth);
	v3.TexCoords = glm::vec2(1.0f, 1.0f);
	v3.Position = glm::vec3(innerSizeX + borderWidth, 0.0f, -borderWidth);
	v4.TexCoords = glm::vec2(0.0f, 0.0f);
	v4.Position = glm::vec3(-borderWidth, 0.0f, -borderWidth);
	mesh.vertices.push_back(v1);
	mesh.vertices.push_back(v2);
	mesh.vertices.push_back(v3);
	mesh.vertices.push_back(v4);
	i++;

	// left
	v1.Normal = v2.Normal = v3.Normal = v4.Normal = glm::vec3(-1.0f, 0.0f, 0.0f);

	v1.TexCoords = glm::vec2(1.0f - texBorder, texBorder);
	v1.Position = glm::vec3(innerSizeX, height, 0.0f);
	v2.TexCoords = glm::vec2(1.0f, 1.0f - texBorder);
	v2.Position = glm::vec3(innerSizeX, height, innerSizeZ);
	v3.TexCoords = glm::vec2(1.0f - texBorder, 1.0f - texBorder);
	v3.Position = glm::vec3(innerSizeX, 0.0f, innerSizeZ);
	v4.TexCoords = glm::vec2(1.0f, texBorder);
	v4.Position = glm::vec3(innerSizeX, 0.0f, 0.0f);
	mesh.vertices.push_back(v1);
	mesh.vertices.push_back(v2);
	mesh.vertices.push_back(v3);
	mesh.vertices.push_back(v4);
	i++;

	v1.TexCoords = glm::vec2(0.0f, 0.0f);
	v1.Position = glm::vec3(-borderWidth, height, -borderWidth);
	v2.TexCoords = glm::vec2(1.0f, 0.0f);
	v2.Position = glm::vec3(-borderWidth, height, innerSizeZ + borderWidth);
	v3.TexCoords = glm::vec2(1.0f, texBorder);
	v3.Position = glm::vec3(-borderWidth, 0.0f, innerSizeZ + borderWidth);
	v4.TexCoords = glm::vec2(0.0f, texBorder);
	v4.Position = glm::vec3(-borderWidth, 0.0f, -borderWidth);
	mesh.vertices.push_back(v1);
	mesh.vertices.push_back(v2);
	mesh.vertices.push_back(v3);
	mesh.vertices.push_back(v4);
	i++;

	// right
	v1.Normal = v2.Normal = v3.Normal = v4.Normal = glm::vec3(1.0f, 0.0f, 0.0f);

	v1.TexCoords = glm::vec2(1.0f - texBorder, texBorder);
	v1.Position = glm::vec3(0.0f, height, innerSizeZ);
	v2.TexCoords = glm::vec2(texBorder, 0.0f);
	v2.Position = glm::vec3(0.0f, height, 0.0f);
	v3.TexCoords = glm::vec2(texBorder, texBorder);
	v3.Position = glm::vec3(0.0f, 0.0f, 0.0f);
	v4.TexCoords = glm::vec2(1.0f - texBorder, texBorder);
	v4.Position = glm::vec3(0.0f, 0.0f, innerSizeZ);
	mesh.vertices.push_back(v1);
	mesh.vertices.push_back(v2);
	mesh.vertices.push_back(v3);
	mesh.vertices.push_back(v4);
	i++;

	v1.TexCoords = glm::vec2(1.0f, 1.0f);
	v1.Position = glm::vec3(innerSizeX + borderWidth, height, innerSizeZ + borderWidth);
	v2.TexCoords = glm::vec2(1.0f, 0.0f);
	v2.Position = glm::vec3(innerSizeX + borderWidth, height, -borderWidth);
	v3.TexCoords = glm::vec2(1.0f - texBorder, 0.0f);
	v3.Position = glm::vec3(innerSizeX + borderWidth, 0.0f, -borderWidth);
	v4.TexCoords = glm::vec2(1.0f - texBorder, 1.0f);
	v4.Position = glm::vec3(innerSizeX + borderWidth, 0.0f, innerSizeZ + borderWidth);
	mesh.vertices.push_back(v1);
	mesh.vertices.push_back(v2);
	mesh.vertices.push_back(v3);
	mesh.vertices.push_back(v4);
	i++;

	for (int index = 0; index < i; index++) {
		mesh.indices.push_back(index * 4);
		mesh.indices.push_back(index * 4 + 1);
		mesh.indices.push_back(index * 4 + 2);
		mesh.indices.push_back(index * 4);
		mesh.indices.push_back(index * 4 + 2);
		mesh.indices.push_back(index * 4 + 3);
	}

}

void Basin::render(Shader *shader) {
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position.x - innerSizeX / 2, position.y, position.z - innerSizeZ / 2));
	shader->Use();
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	mesh.Draw(shader);
}