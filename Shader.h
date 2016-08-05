#include <string>
#include <stdio.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GLFW\glfw3.h>
#include <fstream>
#include <unordered_map>

class Shader {

public:

	Shader();
	bool createShader(std::string vertexFilePath, std::string fragmentFilePath);
	bool createVertexShader();
	bool createFragmentShader();
	bool loadShaderFile(std::string& loadedString, std::string& fileToLoad);
	void setActive();
	bool checkShaderStatus();

	std::string vertexFilePath;
	std::string fragmentFilePath;

	GLuint vs, fs;
	GLuint shaderProgramme;

};
