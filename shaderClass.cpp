#include"shaderClass.h"

//Lê um arquivo de texto e retorna seu conteudo como String
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

//Construtor que faz o programa de shaders com os 2 arquivos
Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	//Lê os arquivos Default.vert e Default.frag e guarda as Strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	//Converte as Strings em arrays char
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//Cria o objeto Vertex Shader e pega sua refêrencia
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Transfere a fonte do Shader para o objeto Vertex Shader
 	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//Compila o Vertex Shader
	glCompileShader(vertexShader);
	//Checar se a compilção foi bem sucedida
	compileErrors(vertexShader, "VERTEX");

	//Cria o objeto Fragmente Shader e pega sua refêrencia
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Transfere a fonte do Shader para o objeto Fragment Shader
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//Compila o Fragment Shader
	glCompileShader(fragmentShader);
	//Checar se a compilção foi bem sucedida
	compileErrors(fragmentShader, "FRAGMENT");

	//Cria o objeto Shader Program e pega sua referência
	ID = glCreateProgram();
	//Tranfere os Vertex e Fragment Shader para o programa
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//Conecta tudo no programa
	glLinkProgram(ID);
	//Checar se não houve erros
	compileErrors(ID, "PROGRAM");
	//Deleta os objetos que não serão usados
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

//Ativa o programa
void Shader::Activate() {
	glUseProgram(ID);
}

//Deleta o programa
void Shader::Delete() {
	glDeleteProgram(ID);
}


//Checagem de erros
void Shader::compileErrors(unsigned int shader, const char* type) {
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERRO NA COMPILACAO SHADER: " << type << "\n" << std::endl;
		}
		else {
			glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE) {
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERRO NO LINKING SHADER: " << type << "\n" << std::endl;
			}
		}
	}
}