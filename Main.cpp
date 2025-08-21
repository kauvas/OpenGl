#include "Mesh.h"

const unsigned int width = 800;
const unsigned int height = 800;
int a = 0;

Vertex vertices[] = {
	//     COORDENADAS                    /      C0RES                 /   TEXTURAS                /      NORMAIS        //                                     
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  1.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};


// Indices dos vertices para ordem
GLuint indices[] = {
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] = {
//     COORDENADAS     //
    Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
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

	//Dados da textura
	Texture textures[]{
		//Pega uma textura de um png 
		Texture("planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	//Faz o programa ler os arquvios shader
	Shader shaderProgram("default.vert", "default.frag");
	//Guarda dados da mesh em vetores
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	//Mesh do chão
	Mesh floor(verts, ind, tex);

	//Shader para a luz
	Shader lightShader("light.vert", "light.frag");
	//Guarda os dados da mesh em vetores
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	//Mesh da luz
	Mesh light(lightVerts, lightInd, tex);

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
		//Desenha as meshes
		floor.Draw(shaderProgram, camera);
		light.Draw(lightShader, camera);

		//Muda o buffer anterior com o posterior
		glfwSwapBuffers(window);
		//Processa os eventos
		glfwPollEvents();
	}

	//Deleta todos objetos criados

	shaderProgram.Delete();
	lightShader.Delete();
	//Deleta a janela
	glfwDestroyWindow(window);
	//Finaliza GLFW
	glfwTerminate();
	//Fim do programa
	return 0;

}