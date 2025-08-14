#include"Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
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
	glActiveTexture(slot);
	glBindTexture(texType, ID);
	//Algoritmo usado para fazer a imagem maior ou menor
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//Controla a repetição da Imagem
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	/* Usado para em outras funções
	float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);
	*/

	//Atribui a imagem ao objeto textura
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	//Gera o mipmap
	glGenerateMipmap(texType);
	//Deleta os dados já que agora estão no objeto
	stbi_image_free(bytes);
	//Unbind para o objeto textura
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	//Pega o local do uniform 
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	//Ativa o shader e atribui o valor do uniform
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind() {
	glBindTexture(type, ID);
}

void Texture::Unbind() {
	glBindTexture(type, 0);
}

void Texture::Delete() {
	glDeleteTextures(1, &ID);
}