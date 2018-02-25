#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glhead.h"

class Shader
{
public:
	// 程序ID
	GLuint Program;
	// 构造器读取并构建着色器
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	// 使用程序
	void Use();
};