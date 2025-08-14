#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>
class VBO {
public:
	//ID de referência
	GLuint ID;
	//Construtor VBO.cpp
	VBO(GLfloat* vertices, GLsizeiptr size);
	void Bind();
	void Unbind();
	void Delete();
};
#endif