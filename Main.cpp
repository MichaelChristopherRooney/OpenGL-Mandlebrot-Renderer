
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GLFW\glfw3.h>
#include "Shader.h"

GLFWwindow *window;
int xRes = 1080;
int yRes = 1080;

bool initOpenGL() {

	window = NULL;

	const GLubyte* renderer;
	const GLubyte* version;

	if (!glfwInit()) {
		return 1;
	}

	window = glfwCreateWindow(xRes, yRes, "OpenGL Mandlebrot Renderer", NULL, NULL);
	glfwSetWindowSizeLimits(window, xRes, yRes, xRes, yRes);

	if (!window) {
		return 1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

}

int main(int argc, char** argv) {

	if (!initOpenGL()) {
		printf("Error in creating OpenGL instance\n");
		printf("Press any key to continue...\n");
		getchar();
		return 1;
	}

	Shader s;
	if (!s.createShader("Shaders/vert.glsl", "Shaders/frag.glsl")) {
		printf("Error in creating shader\n");
		printf("Press any key to continue...\n");
		getchar();
		return 1;
	}
	s.setActive();

	double lastTime = 0;
	float zoom = 0.8f;
	GLuint zoomLocation = glGetUniformLocation(s.shaderProgramme, "m");
	GLuint xResLocation = glGetUniformLocation(s.shaderProgramme, "xRes");
	GLuint yResLocation = glGetUniformLocation(s.shaderProgramme, "yRes");

	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();

		glUniform1f(zoomLocation, zoom);
		glUniform1i(xResLocation, xRes);
		glUniform1i(yResLocation, yRes);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		lastTime = glfwGetTime();

		zoom *= 1.005f;

	}

	return 0;

}