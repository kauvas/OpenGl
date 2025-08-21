#version 330 core
//Coordenadas
layout (location = 0) in vec3 aPos;
//Normais
layout (location = 1) in vec3 aNormal;
//Cores
layout (location = 2) in vec3 aColor;
//Coordenadas texturas
layout (location = 3) in vec2 aTex;

//Saida da posição atual para Default.frag
out vec3 crntPos;
//Saida dos normais para Default.frag
out vec3 Normal;
//Saida das cores para Default.frag
out vec3 color;
//Saida das coordenadas texturas para Default.frag
out vec2 texCoord;



//Recebe a matriz da camera
uniform mat4 camMatrix;
uniform mat4 model;

void main(){
	//Calcula a posição atual
	crntPos = vec3(model * vec4(aPos,1.0f));
    //Atribui os daods da normal
	Normal = aNormal;
    //Atribui os dados das cores 
    color = aColor;
    //Atribui os dados de coordnadas para texturas
    texCoord = aTex;

    //Gera as coordenadas do vertices
    gl_Position = camMatrix * vec4(aPos, 1.0);
}