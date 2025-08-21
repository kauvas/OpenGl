#version 330 core

//Saida de cores (RGBA)
out vec4 FragColor;

//Entrada da posição atual do Default.vert
in vec3 crntPos;
//Entrada das normais do Default.vert
in vec3 Normal;
//Entrada de cores do Default.vert
in vec3 color;
//Entrada de coordenas de textura do Default.vert
in vec2 texCoord;

//Pega a unidade de textura da main
uniform sampler2D diffuse0;
uniform sampler2D specular0;

//Cor da luz
uniform vec4 lightColor;
//Posição da luz
uniform vec3 lightPos;
//Posição da câmera
uniform vec3 camPos;

vec4 pointLight(){

	vec3 lightVec = lightPos - crntPos;

	//intensidade da luz quanto a distância
	float dist = length(lightVec);
	float a = 1.0f;
	float b = 0.2f;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	//luz do ambiente
	float ambient = 0.2f;

	//luz difusa
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	
	//luz especular
	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

vec4 direcLight(){
	
	//luz do ambiente
	float ambient = 0.2f;

	//luz difusa
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	
	//luz especular
	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 spotLight(){
	//area iluminada
	float outerCone = 0.9f;
	float innerCone = 0.95f;

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
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;
	//intensidade da luz baseado no seu ângulo para o centro do cone de luz
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}


void main(){ 
	//Cor final
	FragColor = direcLight();
};	