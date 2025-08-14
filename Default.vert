#version 330 core
//Coordenadas
layout (location = 0) in vec3 aPos;
//Cores
layout (location = 1) in vec3 aColor;
//Coordenadas texturas
layout (location = 2) in vec2 aTex;

//Saida das cores para Default.frag
out vec3 color;
//Saida das coordenadas texturas para Default.frag
out vec2 texCoord;
//Controla a escala
uniform float scale;

void main(){
   //Gera as coordenadas do vetices
   gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
   //Atribui os dados das cores 
   color = aColor;
   //Atribui os dados de coordnadas para texturas
   texCoord = aTex;
}