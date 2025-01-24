#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader
{
public:
	unsigned int ID;
	Shader();
	
	void genShader(const char* vertexPath, const char* fragmentPath);
	void genShader(const char* vertexPath, const char* geometryPath, const char* fragmentPath);
	void use();

	void setBool(const std::string& name, bool value)const;
	void setInt(const std::string& name, int value)const;
	void setFloat(const std::string& name, float value)const;
	void setMat4(const std::string& name, glm::mat4 value)const;
	void setVec4(const std::string& name, glm::vec4 value)const;
	void setVec3(const std::string& name, glm::vec3 value)const;
	void setVec2(const std::string& name, glm::vec2 value)const;
};

