#include "Shader.h"

Shader::Shader() {
	this->ID = glCreateProgram();
}

void Shader::genShader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;

	//var de stockage de fichier
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		//met le contenue des fichiers dans le stream
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		//convertie le stream en string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "Erreur de lecture du fichier de shader" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//on assigne le shader de vertex
   //un shader s'écrit vraiment de manière si barabare ? 


	unsigned int vertex, fragment;
	int succes;
	char log[512];
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &succes);
	if (!succes) {
		glGetShaderInfoLog(vertex, 512, NULL, log);
		std::cout << "Erreur shader vertex : \n" << log << std::endl;
	}
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &succes);
	if (!succes) {
		glGetShaderInfoLog(fragment, 512, NULL, log);
		std::cout << "Erreur shader fragment : \n" << log << std::endl;
	}
	
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &succes);
	if (!succes) {
		glGetProgramInfoLog(ID, 512, NULL, log);
		std::cout << "Erreur shader complet : \n" << log << std::endl;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
};
 void Shader::genShader(const char* vertexPath, const char* geometryPath, const char* fragmentPath) {
	std::string vertexCode;
	std::string geometryCode;
	std::string fragmentCode;

	//var de stockage de fichier
	std::ifstream vShaderFile;
	std::ifstream gShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vShaderFile.open(vertexPath);
		gShaderFile.open(geometryPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, gShaderStream, fShaderStream;

		//met le contenue des fichiers dans le stream
		vShaderStream << vShaderFile.rdbuf();
		gShaderStream << gShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		gShaderFile.close();
		fShaderFile.close();

		//convertie le stream en string
		vertexCode = vShaderStream.str();
		geometryCode = gShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "Erreur de lecture du fichier de shader" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* gShaderCode = geometryCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//on assigne le shader de vertex
   //un shader s'écrit vraiment de manière si barabare ? 


	unsigned int vertex, geometry, fragment;
	int succes;
	char log[512];
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &succes);
	if (!succes) {
		glGetShaderInfoLog(vertex, 512, NULL, log);
		std::cout << "Erreur shader vertex : \n" << log << std::endl;
	}
	geometry = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometry, 1, &gShaderCode, NULL);
	glCompileShader(geometry);

	glGetShaderiv(geometry, GL_COMPILE_STATUS, &succes);
	if (!succes) {
		glGetShaderInfoLog(geometry, 512, NULL, log);
		std::cout << "Erreur shader gémotry : \n" << log << std::endl;
	}
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &succes);
	if (!succes) {
		glGetShaderInfoLog(fragment, 512, NULL, log);
		std::cout << "Erreur shader fragment : \n" << log << std::endl;
	}
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, geometry);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &succes);
	if (!succes) {
		glGetProgramInfoLog(ID, 512, NULL, log);
		std::cout << "Erreur shader complet : \n" << log << std::endl;
	}
	glDeleteShader(vertex);
	glDeleteShader(geometry);
	glDeleteShader(fragment);
}
void Shader::use() {
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::setVec4(const std::string& name, glm::vec4 value) const {
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::setVec3(const std::string& name, glm::vec3 value) const {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::setVec2(const std::string& name, glm::vec2 value) const {
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}