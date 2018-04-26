//
//  Shader.cpp
//  GLFWTest
//
//  Created by wynne on 2018/3/26.
//  Copyright © 2018年 wynne. All rights reserved.
//

#include "Shader.hpp"

Shader::Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath)
{
	try
	{
		//const char*  vertexShaderCode;
		//const char*  fragmentShaderCode;

		std::ifstream vertexShaderFile;
		std::ifstream fragmentShaderFile;

		vertexShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  		fragmentShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

		vertexShaderFile.open(vertexShaderPath);
		fragmentShaderFile.open(fragmentShaderPath);

		std::stringstream vertexShaderSteam;
		std::stringstream fragmentShaderSteam;

		vertexShaderSteam << vertexShaderFile.rdbuf();
		vertexShaderSteam << "\n\0";
		fragmentShaderSteam << fragmentShaderFile.rdbuf();
		fragmentShaderSteam << "\n\0";

		vertexShaderFile.close();
		fragmentShaderFile.close();

		std::string vertexShaderCodeStr = vertexShaderSteam.str();
		const char*  vertexShaderCode = vertexShaderCodeStr.c_str();

		std::string fragmentShaderCodeStr = fragmentShaderSteam.str();
		const char*  fragmentShaderCode = fragmentShaderCodeStr.c_str();

		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
		glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);

		glCompileShader(vertexShader);
		glCompileShader(fragmentShader);

		int success;
		char log[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glad_glGetShaderInfoLog(vertexShader, 512, NULL, log);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << std::endl;
		}

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glad_glGetShaderInfoLog(fragmentShader, 512, NULL, log);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << std::endl;
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, log);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log << std::endl;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << e.code().message() << std::endl;
	}
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
	setInt(name, (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{ 
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{ 
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{ 
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}