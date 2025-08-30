#include"Texture.h"

Texture::Texture(const char* image, const char* texType, GLuint slot) {
	//Atribui o tipo de textura ao objeto
	type = texType;
	//Dimensões da textura e numeros de canais de cor
	int widthImg, heightImg, numColCh;
	//Gira a imagem de cabeça pra cima
	stbi_set_flip_vertically_on_load(true);
	//Lê a imagem e armazena ela em bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
	//Gera o objeto de textura
	glGenTextures(1, &ID);
	//Atribui a textura a uma unidade
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);
	//Algoritmo usado para fazer a imagem maior ou menor
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//Controla a repetição da Imagem
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	/* Usado para em outras funções
	float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);
	*/

	if (numColCh == 4) {
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			bytes
		);
	}
	else if (numColCh == 3) {
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			bytes
		);
	}
	else if (numColCh == 1) {
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			bytes
		);
	}
	else
		throw std::invalid_argument("Falha ao atribuir textura");

	//Gera o mipmap
	glGenerateMipmap(GL_TEXTURE_2D);
	//Deleta os dados já que agora estão no objeto
	stbi_image_free(bytes);
	//Unbind para o objeto textura
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	//Pega o local do uniform 
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	//Ativa o shader e atribui o valor do uniform
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind() {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete() {
	glDeleteTextures(1, &ID);
}