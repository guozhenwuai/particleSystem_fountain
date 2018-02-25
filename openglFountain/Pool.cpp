#include "Pool.h"

Pool::Pool(glm::vec3 center, double x, double z, double height, double dist)
	: centerPos(center)
	, height(height)
	, distance(dist)
	, lenX(x)
	, lenZ(z)
{
	numX = x / dist + 1;
	numZ = z / dist + 1;

	glGenTextures(1, &textureId);
	setTexture("./Resource/Textures/pebbles.bmp");

	reset();
}

Pool::Pool(glm::vec3 center, double x, double z, double height, double dist, GLchar *bottomPath)
	: centerPos(center)
	, height(height)
	, distance(dist)
	, lenX(x)
	, lenZ(z)
{
	numX = x / dist + 1;
	numZ = z / dist + 1;

	glGenTextures(1, &textureId);
	setTexture(bottomPath);

	reset();
}

void Pool::setDistance(double dist) {
	distance = dist;
	numX = lenX / dist;
	numZ = lenZ / dist;
	reset();
}

void Pool::reset() {
	oscillators.clear();
	mesh.clear();

	mesh.vertices.resize(numX * numZ);
	oscillators.resize(numX * numZ);
	for (int i = 0; i < numX; i++) {
		for (int j = 0; j < numZ; j++) {
			int idx = i + j * numX;
			Vertex &v = mesh.vertices[idx];
			v.Position = glm::vec3(i * distance, 0.0f, j * distance);
			v.Normal = glm::vec3(0.0f, 1.0f, 0.0f);
			v.TexCoords = glm::vec2((float)i / numX * texRepeat, 1 - (float)j / numZ * texRepeat);

			oscillators[idx].speedY = 0;

			if (i < numX - 1 && j < numZ - 1) {
				mesh.indices.push_back(i + j * numX);
				mesh.indices.push_back(i + 1 + j * numX);
				mesh.indices.push_back(i + 1 + (j + 1) * numX);

				mesh.indices.push_back(i + j * numX);
				mesh.indices.push_back(i + 1 + (j + 1) * numX);
				mesh.indices.push_back(i + (j + 1) * numX);
			}
		}
	}
	indiceNum = mesh.indices.size();
}

void Pool::update(float delta) {
	for (int i = 0; i < numX; i++) {
		for (int j = 0; j < numZ; j++) {
			int idx = i + j * numX;
			Oscillator &os = oscillators[idx];
			if (i == 0 || i == numX - 1 || j == 0 || j == numZ - 1) {

			}
			else {
				float avgDiff = mesh.vertices[idx - 1].Position.y
					+ mesh.vertices[idx + 1].Position.y
					+ mesh.vertices[idx - numX].Position.y
					+ mesh.vertices[idx + numX].Position.y
					- 4 * mesh.vertices[idx].Position.y;
				os.speedY += avgDiff * 50 * delta;
				os.speedY *= 0.9f;
				os.newY += os.speedY * 0.025;
			}
		}
	}

	for (int i = 0; i < numX; i++) {
		for (int j = 0; j < numZ; j++) {
			int idx = i + j * numX;
			mesh.vertices[idx].Position.y = oscillators[idx].newY;
		}
	}

	for (int i = 0; i < numX; i++) {
		for (int j = 0; j < numZ; j++) {
			int idx = i + j * numX,
				ileft = i - 1 + j * numX, iright = i + 1 + j * numX,
				iup = i + (j + 1) * numX, idown = i + (j - 1) * numX;
			glm::vec3 u, v;
			int ip1 = idx, ip2 = idx;

			ip1 = i > 0 ? ileft : idx;
			ip2 = i < numX - 1 ? iright : idx;
			glm::vec3 p1 = mesh.vertices[ip1].Position;
			glm::vec3 p2 = mesh.vertices[ip2].Position;
			u = p2 - p1;
			
			ip1 = j > 0 ? idown : idx;
			ip2 = j < numZ - 1 ? iup : idx;
			p1 = mesh.vertices[ip1].Position;
			p2 = mesh.vertices[ip2].Position;
			v = p2 - p1;

			glm::vec3 normal = glm::normalize(glm::cross(u, v));

			float sign = normal.y > 0.0 ? 1.0f : -1.0f;
			glm::vec3 &nor = mesh.vertices[idx].Normal;
			nor = glm::vec3(normal.x * sign,  normal.y * sign, normal.z * sign);
		}
	}
}

void Pool::splash(double x, double z, double splash) {
	int idx = (x + lenX / 2) / distance;
	int idz = (z + lenZ / 2) / distance;
	if (idx >= 0 && idx < numX && idz >= 0 && idz < numZ) {
		int i = idx + idz * numX;
		if (mesh.vertices[i].Position.y > -height) {
			mesh.vertices[i].Position.y += splash;
		}
	}
}

GLint Pool::getTextureId() {
	return textureId;
}

void Pool::render(Shader *shader, float delta) {
	update(delta);
	shader->Use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(centerPos.x - lenX / 2, centerPos.y, centerPos.z - lenZ / 2));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glActiveTexture(GL_TEXTURE4);
	glUniform1i(glGetUniformLocation(shader->Program, "bottom"), 4);
	glBindTexture(GL_TEXTURE_2D, textureId);

	mesh.Draw(shader);
}

void Pool::setTexture(char *path) {
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