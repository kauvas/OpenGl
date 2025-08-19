#version 330 core
//Coordenadas
layout (location = 0) in vec3 aPos;
//Cores
layout (location = 1) in vec3 aColor;
//Coordenadas texturas
layout (location = 2) in vec2 aTex;
//Normais
layout (location = 3) in vec3 aNormal;

//Saida das cores para Default.frag
out vec3 color;
//Saida das coordenadas texturas para Default.frag
out vec2 texCoord;
//Saida dos normais para Default.frag
out vec3 Normal;
out vec3 crntPos;

//Recebe a matriz da camera
uniform mat4 camMatrix;
uniform mat4 model;

void main(){
	crntPos = vec3(model * vec4(aPos,1.0f));

   //Gera as coordenadas do vetices
   gl_Position = camMatrix * vec4(aPos, 1.0);
   //Atribui os dados das cores 
   color = aColor;
   //Atribui os dados de coordnadas para texturas
   texCoord = aTex;
   Normal = aNormal;
}