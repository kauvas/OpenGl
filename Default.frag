#version 330 core

//Saida de cores (RGBA)
out vec4 FragColor;
//Entrada de cores do Default.vert
in vec3 color;
//Entrada de coordenas de textura do Default.vert
in vec2 texCoord;
//Pega a unidade de textura da main
uniform sampler2D tex0;

void main()
{
   FragColor = texture(tex0, texCoord);
}; 