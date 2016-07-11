#include "Shader.h"


Shader::Shader(const char *vertex_path, const char *fragment_path)
{
	this->program = loadShader(vertex_path, fragment_path);
}


std::string Shader::readFile(const char *filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}


GLuint Shader::loadShader(const char *vertex_path, const char *fragment_path) {
	// 準備頂點著色器  // 創造頂點著色器
	GLuint vertShader = createBasicShader(0, vertex_path);
	// 準備像素著色器  // 創造像素著色器
	GLuint fragShader = createBasicShader(1, fragment_path);

	/*********************建立程式綁定著色器**********************/
	std::cout << "Linking program" << std::endl;
	// 建立著色器程式 // 創造著色器程式
	GLuint program = glCreateProgram();
	// 將需要的著色器載入到著色器程式中
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	// 載入完後連結到著色器
	glLinkProgram(program);

	// 確認著色器程式是否成功連結
	debugShader(program);

	// 刪除不用的著色器
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return program;
}

// 0 vertex 1 fragment
GLuint Shader::createBasicShader(int shaderCmd, const char * path)
{
	// 準備著色器  // 創造著色器
	GLuint shader;
	if (shaderCmd == 0)
		shader = glCreateShader(GL_VERTEX_SHADER);
	else if (shaderCmd == 1)
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	// Read shaders
	std::string shaderStr = readFile(path);
	const char *shaderSrc = shaderStr.c_str();
	return compileShader(shaderCmd, shader, shaderSrc);
}

GLuint Shader::compileShader(int shaderCmd, GLuint shader, const char* shaderSrc)
{
	if (shaderCmd == 0)
		std::cout << "Compiling vertex shader." << std::endl;
	else if (shaderCmd == 1)
		std::cout << "Compiling fragment shader." << std::endl;
	// 將著色器的原始碼(們)綁定到著色器中
	glShaderSource(shader, 1, &shaderSrc, NULL);
	// 編譯著色器
	glCompileShader(shader);

	// Check vertex shader
	//確認著色器是否綁定成功
	debugShader(shader);
	return shader;
}

void Shader::debugShader(GLuint shader)
{
	GLint result = GL_FALSE;
	int logLength;
	// Check vertex shader
	//確認著色器是否綁定成功
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> shaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(shader, logLength, NULL, &shaderError[0]);
	std::cout << &shaderError[0] << std::endl;
}

