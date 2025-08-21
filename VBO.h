#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>
//struct para padronizar vertices usando em meshes
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VBO {
public:
	//ID de referência
	GLuint ID;
	//Construtor VBO.cpp
	VBO(std::vector <Vertex>& vertices);
	void Bind();
	void Unbind();
	void Delete();
};
#endif