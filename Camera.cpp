#include"Camera.h"

Camera::Camera(int width, int height, glm::vec3 position) {
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane) {
	//inicializa as matrizes para não serem nulas
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	//Ajusta a posição e orientação da camera
	view = glm::lookAt(Position, Position + Orientation, Up);
	//Adiciona perspectiva
	projection = glm::perspective(glm::radians(45.0f), (float)(width / height), nearPlane, farPlane);
	//Atribui nova matriz
	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform) {
	//Manda a matriz para o Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Inputs(GLFWwindow* window) {
	//Ajusta as teclas para controlar a câmera
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		Position += speed * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed = 0.04f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		speed = 0.1f;
	}

	//Ajusta os controle do mouse
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		//Esconde o mouse ao clicar
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		//Previne a câmera de pular de posições
		if (firstClick) {
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}
		//Coordenadas do mouse
		double mouseX;
		double mouseY;
		//Atribui as coordenadas do mouse na janela
		glfwGetCursorPos(window, &mouseX, &mouseY);
		//Normaliza a posição do mouse para ser no centro da janela
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (height / 2)) / height;
		//Calcula a mudança vertical quanto a orientação
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));
		//Previne que a câmera possa girar infitamente
		if (!((glm::angle(newOrientation, Up) <= glm::radians(5.0f)) or (glm::angle(newOrientation, -Up) <= glm::radians(5.0f)))) {
			Orientation = newOrientation;
		}
		//Permite ritação para a direita e esquerda
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
		//Fixa o cursor para o centro da janela
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	//Mostra o cursor novamente ao soltar o botão direito
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		//Previne a camera de pular no proximo clique
		firstClick = true;
	}
}