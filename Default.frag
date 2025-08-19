#version 330 core

//Saida de cores (RGBA)
out vec4 FragColor;
//Entrada de cores do Default.vert
in vec3 color;
//Entrada de coordenas de textura do Default.vert
in vec2 texCoord;
//Entrada das normais do Default.vert
in vec3 Normal;
//Entrada da posição atual do Default.vert
in vec3 crntPos;

//Pega a unidade de textura da main
uniform sampler2D tex0;
//Cor da luz
uniform vec4 lightColor;
//Posição da luz
uniform vec3 lightPos;
//Posição da câmera
uniform vec3 camPos;

void main(){
	//luz do ambiente
	float ambient = 0.2f;
	//luz difusa
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	
	//luz especular
	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	//Cor final
	FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
};	