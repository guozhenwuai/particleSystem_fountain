#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glhead.h"

class Shader
{
public:
	// ����ID
	GLuint Program;
	// ��������ȡ��������ɫ��
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	// ʹ�ó���
	void Use();
};