#include "Model.h"

const unsigned int width = 800;
const unsigned int height = 800;

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

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// Faz com que faces não fiquem sobrepondo
	glEnable(GL_DEPTH_TEST);

	//Cria o objeto camera
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	Model model("models/sword/scene.gltf");

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
		model.Draw(shaderProgram, camera);
		//Muda o buffer anterior com o posterior
		glfwSwapBuffers(window);
		//Processa os eventos
		glfwPollEvents();
	}

	//Deleta todos objetos criados
	shaderProgram.Delete();
	//Deleta a janela
	glfwDestroyWindow(window);
	//Finaliza GLFW
	glfwTerminate();
	//Fim do programa
	return 0;
}