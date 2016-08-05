#include "Shader.h"

Shader::Shader() {

}

bool Shader::createShader(std::string p_vertexFilePath, std::string p_fragmentFilePath) {

	vertexFilePath = p_vertexFilePath;
	fragmentFilePath = p_fragmentFilePath;

	/* create the vertex shader */
	if (!createVertexShader()) {
		return false;
	}

	/* create the fragment shader */
	if (!createFragmentShader()) {
		return false;
	}

	if (!checkShaderStatus()) {
		return false;
	}

	shaderProgramme = glCreateProgram();
	glAttachShader(shaderProgramme, fs);
	glAttachShader(shaderProgramme, vs);
	glLinkProgram(shaderProgramme);

	return true;

}

bool Shader::createVertexShader() {

	std::string loadedString;
	const char* shaderString;

	if (!loadShaderFile(loadedString, vertexFilePath)) {
		return false;
	}

	shaderString = loadedString.c_str();
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &shaderString, NULL);
	glCompileShader(vs);

}

bool Shader::createFragmentShader() {

	std::string loadedString;
	const char* shaderString;

	if (!loadShaderFile(loadedString, fragmentFilePath)) {
		return false;
	}

	shaderString = loadedString.c_str();
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &shaderString, NULL);
	glCompileShader(fs);

}

/*
check if the shaders compiled successfully
print any errors that are present
*/
bool Shader::checkShaderStatus() {

	GLint status;

	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE) {

		char buffer[512];
		glGetShaderInfoLog(vs, 512, NULL, buffer);
		printf("%s:\n %s\n", "Vertex shader:", buffer);
		return false;

	}

	glGetShaderiv(fs, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE) {

		char buffer[512];
		glGetShaderInfoLog(fs, 512, NULL, buffer);
		printf("%s:\n %s\n", "Fragment shader:", buffer);

		return false;

	}

	return true;

}

bool Shader::loadShaderFile(std::string& loadedString, std::string& fileToLoad) {

	std::ifstream input(fileToLoad, std::ios::in);

	if (input.is_open() && input.good() && !input.bad()) {
		loadedString.assign((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
		input.close();
		input.clear();
		return true;
	} else {
		printf("Error opening the file\n");
		return false;
	}


}

void Shader::setActive() {
	glUseProgram(shaderProgramme);
}