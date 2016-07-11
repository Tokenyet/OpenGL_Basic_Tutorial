#ifndef SHADER_H
#define SHADER_H

#include "GL/glew.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Shader
{
public:
	Shader(const char *vertex_path, const char *fragment_path);
	void UseProgram() { glUseProgram(program); }
	GLuint GetProgram() { return program; }
private:
	std::string readFile(const char *filePath);
	GLuint loadShader(const char *vertex_path, const char *fragment_path);
	GLuint createBasicShader(int shaderCmd, const char * path);
	GLuint compileShader(int shaderCmd, GLuint shader, const char* Source);
	void debugShader(GLuint shader);
	GLuint program;
};

#endif