#pragma once

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath) {

		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vshaderFile;
		std::ifstream fshaderFile;

		vshaderFile.exceptions(std::ifstream::failbit | std::ifstream::goodbit);
		fshaderFile.exceptions(std::ifstream::failbit | std::ifstream::goodbit);

		try
		{
			vshaderFile.open(vertexPath);
			fshaderFile.open(fragmentPath);
			std::stringstream vertexstream;
			std::stringstream fragmentstream;
			vertexstream << vshaderFile.rdbuf();
			fragmentstream << fshaderFile.rdbuf();

			vshaderFile.close();
			fshaderFile.close();

			vertexCode = vertexstream.str();
			fragmentCode = fragmentstream.str();

		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
		}

		const char* vshadercode = vertexCode.c_str();
		const char* fshadercode = fragmentCode.c_str();

		unsigned int vertexShader;
		unsigned int fragmentShader;

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vshadercode,NULL);
		glCompileShader(vertexShader);
		checkCompileErrors(vertexShader,"vertexshader");

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader,1,&fshadercode,NULL);
		glCompileShader(fragmentShader);
		checkCompileErrors(fragmentShader, "fragmentshader");

		ID = glCreateProgram();
		glAttachShader(ID,vertexShader);
		glAttachShader(ID,fragmentShader);
		glLinkProgram(ID);
		checkCompileErrors(ID,"program");
		
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

	}

	void use() {
		glUseProgram(ID);
	}

	void setBool(const std::string &name,bool value) {
		glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)value);
	}

	void setInt(const std::string& name, int value) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()),value);
	}

	void setFloat(const std::string& name, float value) {
		glUniform1f(glGetUniformLocation(ID,name.c_str()),value);
	}
	void setVec2(const std::string& name, const glm::vec2& value) const {
		glUniform2fv(glGetUniformLocation(ID, name.c_str()),1,&value[0]);
	}
	void setVec2(const std::string& name, float x, float y) const {
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}
	void setVec3(const std::string& name, const glm::vec3& value) const {
		glUniform3fv(glGetUniformLocation(ID,name.c_str()),1,&value[0]);
	}
	void setVec3(const std::string& name, float x,float y,float z) const {
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	void setVec4(const std::string& name, const glm::vec4& value) const {
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string& name, float x, float y, float z, float w) const {
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}
	void setMat2(const std::string& name, const glm::mat2& mat) const {
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void setMat3(const std::string& name, const glm::mat3& mat) const {
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void setMat4(const std::string& name, const glm::mat4& mat) const {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
private:

	void checkCompileErrors(unsigned int program,std::string type) {
		int success;
		char infoLog[1024];
		if (type != "program") {
			glGetShaderiv(program, GL_LINK_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(program,1024,NULL,infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n" << std::endl;
			}
		}
		else {
			glGetProgramiv(program,GL_LINK_STATUS,&success);
			if (!success) {
				glGetProgramInfoLog(program,1024,NULL,infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n" << std::endl;
			}
		}
	}

};