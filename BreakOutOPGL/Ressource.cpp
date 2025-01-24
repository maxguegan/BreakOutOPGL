#include "Ressource.h"

std::map<std::string, Texture>    Ressource::textures;
std::map<std::string, Shader>       Ressource::shaders;

void Ressource::LoadShader(const char* vsPath, const char* gsPath, const char* fsPath , std::string name) {
	Shader shader;
	if (gsPath != NULL) {
		shader.genShader(vsPath, gsPath, fsPath);
	}
	else {
		shader.genShader(vsPath, fsPath);
	}
	shaders.insert({ name, shader });
}

void Ressource::LoadTexture(const char* path,std::string name) {

	Texture tex;
	tex.generate(path);
	textures.insert({ name,tex });
}

 Shader& Ressource::GetShader(std::string nom) {
	return shaders[nom];
}
 Texture& Ressource::GetTexture(std::string nom) {
	return textures[nom];
}

 void Ressource::Clear() {
	 std::map<std::string, Texture>::iterator itTex;
	 for (itTex = textures.begin(); itTex != textures.end(); itTex++) {
		 glDeleteTextures(1, &itTex->second.idTex);
	 }
	 std::map<std::string, Shader>::iterator itShader;
	 for (itShader = shaders.begin(); itShader != shaders.end(); itShader++) {
		 glDeleteProgram(itShader->second.ID);
	 }
 }

 Ressource::Ressource() {
	 
 }