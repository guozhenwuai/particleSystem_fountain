#pragma once
#include <iostream>

#include "glhead.h"
#include "Camera.h"
#include "Fountain.h"
#include "Light.h"
#include "Skybox.h"
#include "EmitController.h"

// Properties
GLuint screenWidth = 1920, screenHeight = 1280;

enum PlayState { STATIC, DYNAMIC, INTERACTIVE };
PlayState state = STATIC;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement(float delta);

// Camera
Camera camera(glm::vec3(0.0f, 20.0f, 20.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

// Light
Light light(20, 60, 2);
void lightUpdate(float delta) {
	light.update(delta);
}

// EmitController
EmitController emitController;
float theta = 0;
void emitterUpdate(float delta) {
	theta += delta;
	theta = fmod(theta, 2 * PI);
	float ct = cos(theta);
	float st = sin(theta);
	emitController.shift("center", 0.3 * ct);
	emitController.shift("circle", 0.1 * st);
	emitController.shift("corner", -0.5 * ct);
	
	//emitController.blossom("center", -PI / 48 * ct);

	emitController.flood("center", ct);

	emitController.rotate("couple", delta);

	emitController.wave("circle", PI / 96 * ct);
	emitController.wave("corner", PI / 48 * st);
}

// Fountain
Fountain *fountain;
void fountainInit() {
	Emitter *e;
	e = fountain->addEmitter(glm::vec3(0, 0, 0), 10.0f, 0, 0, glm::vec3(0, -4.9f, 0), glm::vec3(1, 1, 1), 16,
		0.4, 0.01, 0, 0.1);
	if (e != NULL) {
		emitController.addShiftEmitter("center", e, 1.0f);
		emitController.addShiftEmitter("interact", e, 1.0f);
		//emitController.addBlossomEmitter("center", e, 0.3f);
	}
	e = fountain->addEmitter(glm::vec3(0, 0, 0), 8.0f, 0, 0, glm::vec3(0, -4.9f, 0), glm::vec3(1, 1, 1), 40,
		0.1, 0.01, PI / 24, 0.2);
	if (e != NULL) {
		emitController.addShiftEmitter("center", e, 0.8f);
		emitController.addShiftEmitter("interact", e, 1.0f);
		//emitController.addBlossomEmitter("center", e, 1.0f);
		//emitController.addFloodEmitter("center", e, 1.0f);
	}
	int rayNum = 12;
	double r = 0.8;
	double v = 6.0;
	for (int ray = 0; ray < rayNum; ray++) {
		double theta = 2 * PI * ray / rayNum;
		e = fountain->addEmitter(glm::vec3(r * cos(theta), 0, r * sin(theta)),
			2.0, theta, PI / 4,
			glm::vec3(0, -1.0f, 0),
			glm::vec3(0.8, 0.8, 0.8),
			20, 0, 0.01, 0, 0.3);
		if (e != NULL) {
			emitController.addShiftEmitter("circle", e, 1.0f);
			emitController.addWaveEmitter("circle", e, 1.0f);
			//emitController.addShiftEmitter("interact", e, 1.0f);
		}
	}
	rayNum = 4;
	r = 10;
	for (int ray = 0; ray < rayNum; ray++) {
		double theta = 2 * PI * ray / rayNum + PI / 4;
		e = fountain->addEmitter(glm::vec3(r * cos(theta), 0, r * sin(theta)),
			v, -theta, PI / 6,
			glm::vec3(0, -4.9f, 0),
			glm::vec3(1, 1, 1),
			8, 0.1, 0.01, 0, 0.3);
		if (e != NULL) {
			emitController.addRotateEmitter("couple", e, 1.0f);
			//emitController.addShiftEmitter("interact", e, 1.0f);
		}
		e = fountain->addEmitter(glm::vec3(r * cos(theta), 0, r * sin(theta)),
			v, PI-theta, PI / 6,
			glm::vec3(0, -4.9f, 0),
			glm::vec3(1, 1, 1),
			8, 0.1, 0.01, 0, 0.3);
		if (e != NULL) {
			emitController.addRotateEmitter("couple", e, -1.0f);
			//emitController.addShiftEmitter("interact", e, 1.0f);
		}
		e = fountain->addEmitter(glm::vec3(2 * r * cos(theta), 0, 2 * r * sin(theta)),
			12, theta - PI / 4, 0,
			glm::vec3(0, -4.9f, 0),
			glm::vec3(1, 1, 1),
			8, 1, 0.1, PI / 96, 0.1);
		if (e != NULL) {
			emitController.addWaveEmitter("corner", e, 1.0f);
			emitController.addShiftEmitter("corner", e, 1.0f);
			emitController.addShiftEmitter("interact", e, -1.0f);
		}
	}
}


// The MAIN function, from here we start our application and run our Game loop
int main()
{
	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Fountain", nullptr, nullptr); // Windowed
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	// Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Initialize GLEW to setup the OpenGL Function pointers
	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, screenWidth, screenHeight);

	glEnable(GL_DEPTH_TEST);

	// Setup and compile our shaders
	Shader *basinShader = new Shader("./Shader/basin.vs", "./Shader/basin.fs");
	Shader *particleShader = new Shader("./Shader/particle.vs", "./Shader/particle.fs");
	Shader *poolShader = new Shader("./Shader/pool.vs", "./Shader/pool.fs");
	Shader *skyboxShader = new Shader("./Shader/skybox.vs", "./Shader/skybox.fs");


	fountain = new Fountain(glm::vec3(0, 0, 0), 40.0f, 40.0f, 
		"./Resource/Obj/cube.obj", 
		"./Resource/Textures/basin2.bmp", 
		"./Resource/Textures/pebbles.bmp");

	Skybox skybox("./Resource/Skybox/organic/top.jpg",
		"./Resource/Skybox/organic/bottom.jpg",
		"./Resource/Skybox/organic/left.jpg",
		"./Resource/Skybox/organic/right.jpg",
		"./Resource/Skybox/organic/front.jpg",
		"./Resource/Skybox/organic/back.jpg");

	fountainInit();

	float lastTime, thisTime, deltaTime;
	lastTime = thisTime = glfwGetTime();

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		thisTime = glfwGetTime();
		deltaTime = (thisTime - lastTime) * TIME_DELTA;
		lastTime = thisTime;

		// Check and call events
		glfwPollEvents();
		Do_Movement(deltaTime);

		// Clear the colorbuffer
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightUpdate(deltaTime);
		if(state == DYNAMIC)emitterUpdate(deltaTime);
						
		glm::mat4 projection = glm::perspective(camera.Zoom, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::vec3 lightPos = light.getLightPos();
		glm::vec3 lightAmb = light.getAmbient();
		glm::vec3 lightDiff = light.getDiffuse();
		glm::vec3 lightSpec = light.getSpecular();

		particleShader->Use();
		glUniformMatrix4fv(glGetUniformLocation(particleShader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(particleShader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniform3f(glGetUniformLocation(particleShader->Program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		glUniform3f(glGetUniformLocation(particleShader->Program, "light.position"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(particleShader->Program, "light.ambient"), lightAmb.x, lightAmb.y, lightAmb.z);
		glUniform3f(glGetUniformLocation(particleShader->Program, "light.diffuse"), lightDiff.x, lightDiff.y, lightDiff.z);

		poolShader->Use();
		glUniformMatrix4fv(glGetUniformLocation(poolShader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(poolShader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniform3f(glGetUniformLocation(poolShader->Program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		glUniform3f(glGetUniformLocation(poolShader->Program, "light.position"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(poolShader->Program, "light.ambient"), lightAmb.x, lightAmb.y, lightAmb.z);
		glUniform3f(glGetUniformLocation(poolShader->Program, "light.diffuse"), lightDiff.x, lightDiff.y, lightDiff.z);
		glUniform3f(glGetUniformLocation(poolShader->Program, "light.specular"), lightSpec.x, lightSpec.y, lightSpec.z);
		glActiveTexture(GL_TEXTURE3);
		glUniform1i(glGetUniformLocation(poolShader->Program, "skybox"), 3);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.getID());

		basinShader->Use();
		glUniformMatrix4fv(glGetUniformLocation(basinShader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(basinShader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniform3f(glGetUniformLocation(basinShader->Program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		glUniform3f(glGetUniformLocation(basinShader->Program, "light.position"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(basinShader->Program, "light.ambient"), lightAmb.x, lightAmb.y, lightAmb.z);
		glUniform3f(glGetUniformLocation(basinShader->Program, "light.diffuse"), lightDiff.x, lightDiff.y, lightDiff.z);
		glUniform3f(glGetUniformLocation(basinShader->Program, "light.specular"), lightSpec.x, lightSpec.y, lightSpec.z);

		fountain->render(basinShader, poolShader, particleShader, deltaTime);

		skyboxShader->Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniform3f(glGetUniformLocation(skyboxShader->Program, "light.ambient"), lightAmb.x, lightAmb.y, lightAmb.z);
		glUniform3f(glGetUniformLocation(skyboxShader->Program, "light.diffuse"), lightDiff.x, lightDiff.y, lightDiff.z);
		skybox.render(skyboxShader);

		
		// Swap the buffers
		glfwSwapBuffers(window);
	}

	delete fountain;
	glfwTerminate();
	return 0;
}

#pragma region "User input"


bool cursorDisable = true;

void Do_Movement(float delta)
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, delta);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, delta);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, delta);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, delta);
	if (keys[GLFW_KEY_EQUAL])
		light.speedUp(delta);
	if (keys[GLFW_KEY_MINUS])
		light.speedDown(delta);
	if (state == INTERACTIVE && keys[GLFW_KEY_SPACE])
		emitController.shift("interact", delta * 3);
}

const glm::vec4 waterColors[4] = {
	glm::vec4(1.0f, 1.0f, 1.0f, 0.2f),
	glm::vec4(0.2f, 0.8f, 0.1f, 0.8f),
	glm::vec4(0.0f, 0.6f, 0.6f, 0.3f),
	glm::vec4(0.8f, 0.2f, 0.8f, 0.5f)
};

int colorIndex = 0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
		if (cursorDisable) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else {
			firstMouse = true;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		cursorDisable = !cursorDisable;
	}
	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		fountain->play();
	}
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
		if (state == STATIC) {
			state = DYNAMIC;
		}
		else if (state == DYNAMIC) {
			state = INTERACTIVE;
			fountain->clearEmitters();
			emitController.clear();
			fountainInit();
		}
		else {
			state = STATIC;
		}
	}
	if (key == GLFW_KEY_O && action == GLFW_PRESS) {
		fountain->loadObject("./Resource/Obj/sphere.obj");
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		fountain->resetObject();
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		colorIndex++;
		if (colorIndex == 4) {
			colorIndex = 0;
		}
		fountain->setWaterColor(waterColors[colorIndex]);
	}
	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		light.dayNightSwitch();
	}
	if (state == INTERACTIVE && key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
		emitController.resetSpeed("interact");
	}
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (!cursorDisable)return;
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}