#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

GLfloat vertices[] = {
	//     CORDENADAS                                /      C0RES           /       TEXTURAS    //                                     
		-0.5f,  -0.5f, 0.0f,							1.0f, 0.0f,  0.0f,		0.0f,  0.0f,
		-0.5f,   0.5f, 0.0f,							0.0f, 1.0f,  0.0f,		0.0f,  1.0f,
		 0.5f,   0.5f, 0.0f,							0.0f, 0.0f,  1.0f,		1.0f,  1.0f,
		 0.5f,  -0.5f, 0.0f,							1.0f, 1.0f,  1.0f,		1.0f,  0.0f
};

// Indices dos vertices para ordem
GLuint indices[] = {
	0, 2, 1,
	0, 3, 2,
};

//Função principal
int main() {
	//Inicializa GLFW
	glfwInit();
	//Especifica a versão
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	//Cria a janela e retorna um erro se falhar
	GLFWwindow* window = glfwCreateWindow(800, 800, "Teste", NULL, NULL);
		if (window == NULL) {
			std::cout << "Falha na janela" << std::endl;
			return -1;
	}
	//Faz a janela um contexto
	glfwMakeContextCurrent(window);
	//Ativa Glad
	gladLoadGL();

	//Área onde é renderizado
	glViewport(0, 0, 800, 800);
	//Faz o programa ler os arquvios shader
	Shader shaderProgram("default.vert", "default.frag");

	//Cria um objeto de vertex array e executa um bIND
	VAO VAO1;
	VAO1.Bind();

	//Cria um Buffer para o vertex array e relaciona ele as vertices
	VBO VBO1(vertices, sizeof(vertices));
	//Cria um Buffer para os elementos e relaciona ele as vertices
	EBO EBO1(indices, sizeof(indices));

	//Relaciona  atributos como cor e coordenadas ao VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//Unbind nos objetos para previnir erros
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//Gera um atributo de um uniforme de escala
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//Pega uma textura de um png 
	Texture ops("Sem Título.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	ops.texUnit(shaderProgram, "tex0", 0);

	//Loop while para atualizar a janela
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		ops.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	//Deleta todos objetos criados
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	ops.Delete();
	shaderProgram.Delete();
	//Deleta a janela
	glfwDestroyWindow(window);
	//Finaliza GLFW
	glfwTerminate();
	//Fim do programa
	return 0;

}