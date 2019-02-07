// Plantilla OpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC 

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

#include <math.h>

using namespace std;

//Declaramos apuntador de ventana
GLFWwindow *window;

float xTriangulo = 0.0f;
float yTriangulo = 0.0f;


float velocidad = 0.05f;

void dibujarUnTriangulo()
{
	//Utiliza matriz identidad
	glPushMatrix();

	//Transformaciones
	glTranslatef(xTriangulo, yTriangulo, 0.0f);
	
	//Dibuja los vertices
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.8f, 0.0f);
	glVertex3f(-0.2f, -0.2f, 0);
	glVertex3f(0.2f, -0.2f, 0);
	glVertex3f(0.0f, 0.2f, 0);
	glEnd();

	//Soltar matriz
	glPopMatrix();

}

void moverTriangulo() {
	int estadoTeclaDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if(estadoTeclaDerecha == GLFW_PRESS) {
		xTriangulo += velocidad;
	}

	int estadoTeclaIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoTeclaIzquierda == GLFW_PRESS) {
		xTriangulo -= velocidad;
	}

	int estadoTeclaAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoTeclaAbajo == GLFW_PRESS) {
		yTriangulo -= velocidad;
	}

	int estadoTeclaArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoTeclaArriba == GLFW_PRESS) {
		yTriangulo += velocidad;
	}
}

void dibujar() {
	dibujarUnTriangulo();
	//dibujarTriangulos();
	//dibujarPoligonos();
	//dibujarCuadrado();
}

void actualizar() {
	moverTriangulo();
}

void teclado_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {

	//Si se presionó la tecla de ña fñecha derecha... 
	if (key == GLFW_KEY_RIGHT && ( action == GLFW_PRESS || action == GLFW_REPEAT))
		//se realizara...
	{
		xTriangulo += velocidad;
	}

	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
		//se realizara...
	{
		xTriangulo -= velocidad;
	}

	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
		//se realizara...
	{
		yTriangulo += velocidad;
	}

	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
		//se realizara...
	{
		yTriangulo -= velocidad;
	}
}

int main()
{
	//Si no se pudo iniciar glfw
	//terminamos ejecucion
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	//Si se pudo iniciar el glfw
	//Entonces inicializamos la ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);
	
	//Si no se puede iniciar la ventana
	//terminamos la ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecemos el control
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto
	//Activa funciones modernas
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	//Cuando se reconosca los eventos, se realice dicha funcion
	//glfwSetKeyCallback(window, teclado_callback);

	//Ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 1024, 768);
		//Establece el color de borrado
		glClearColor(0, 0, 0.2, 0);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		dibujar();
		actualizar();

		//Cambiar los Buffer
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}

