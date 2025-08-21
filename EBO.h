#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>
#include<vector>

class EBO {
public:
	//ID de Referência
	GLuint ID;
	//Construtor EBO.cpp
	EBO(std::vector <GLuint>& indices);
	void Bind();
	void Unbind();
	void Delete();
};
#endif