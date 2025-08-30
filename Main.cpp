#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;
int a = 0;

GLfloat vertices[] = {
	//     COORDENADAS   /      C0RES             /   TEXTURAS     /      NORMAIS        //                                     
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Lado inferior
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Lado inferior
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Lado inferior
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Lado inferior

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Lado esquerdo
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Lado esquerdo
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Lado esquerdo

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Lado interior
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Lado interior
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Lado interior

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Lado direito
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Lado direito
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Lado direito

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Lado frontal
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Lado frontal
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Lado frontal            
};

// Indices dos vertices para ordem
GLuint indices[] = {
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

GLfloat lightVertices[] = {
//     COORDENADAS     //
   -0.1f, -0.1f,  0.1f,
   -0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, -0.1f,
	0.1f, -0.1f,  0.1f,
   -0.1f,  0.1f,  0.1f,
   -0.1f,  0.1f, -0.1f,
	0.1f,  0.1f, -0.1f,
	0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
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
	GLFWwindow* window = glfwCreateWindow(width, height, "Teste", NULL, NULL);
		if (window == NULL) {
			std::cout << "Falha na janela" << std::endl;
			return -1;
	}
	//Faz a janela um contexto
	glfwMakeContextCurrent(window);
	//Ativa Glad
	gladLoadGL();
	//Área onde é renderizado
	glViewport(0, 0, width, height);
	//Faz o programa ler os arquvios shader
	Shader shaderProgram("default.vert", "default.frag");
	//Cria um objeto de vertex array e executa um bIND
	VAO VAO1;
	VAO1.Bind();
	//Cria um Buffer para o vertex array e relaciona ele as vertices
	VBO VBO1(vertices, sizeof(vertices));
	//Cria um Buffer para os elementos e relaciona ele aos indeces
	EBO EBO1(indices, sizeof(indices));
	//Relaciona  atributos como cor e coordenadas ao VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	//Unbind nos objetos para previnir erros
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	//Shader para a luz
	Shader lightShader("light.vert", "light.frag");
	//Cria um Vertex Array Object e da bind
	VAO lightVAO;
	lightVAO.Bind();
	//Cria um Vertex Buffer Object e atribui as vertices
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	//Cria um Element Buffer Object e atribui aos indices
 	EBO lightEBO(lightIndices, sizeof(lightIndices));
	//Relaciona atributos do VBO (coordenadas, cores) para o VAO
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	//Unbind para os objetos
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	//Pega uma textura de um png 
	Texture ops("Sem Título.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	ops.texUnit(shaderProgram, "tex0", 0);

	// Faz com que faces não fiquem sobrepondo
	glEnable(GL_DEPTH_TEST);

	//Cria o objeto camera
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	//Loop while para atualizar a janela
	while (!glfwWindowShouldClose(window)) {
		//Cor do fundo
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Apaga os buffers e atribui uma nova buffer de cor ou de profundidade
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Adiciona controles
		camera.Inputs(window);
		//Atualiza e manda a matriz da camera para o Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		//Ativa o programa de shader
		shaderProgram.Activate();
		//Exporta a posição da camera para Default.frag para iluminação especular
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		//Exporta o camMatrix para Default.vert da pirâmide
		camera.Matrix(shaderProgram, "camMatrix");
		//Bind na textura para ela aparecer
		ops.Bind();
		//Bind do VAO para o OpenGL
		VAO1.Bind();
		//Desenha primitivos(Formas), numero de indice, seu tipo e indexação
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		//Ativa o programa de iluminação
		lightShader.Activate();
		//Exporta camMatrix para light.vert
		camera.Matrix(lightShader, "camMatrix");
		//Bind do VAO para o OpenGL
		lightVAO.Bind();
		//Desenha primitivos(Formas), numero de indice, seu tipo e indexação
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		//Muda o buffer anterior com o posterior
		glfwSwapBuffers(window);
		//Processa os eventos
		glfwPollEvents();
	}

	//Deleta todos objetos criados
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	ops.Delete();
	shaderProgram.Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightShader.Delete();
	//Deleta a janela
	glfwDestroyWindow(window);
	//Finaliza GLFW
	glfwTerminate();
	//Fim do programa
	return 0;

}