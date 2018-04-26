//
//  Shader.hpp
//  GLFWTest
//
//  Created by wynne on 2018/3/26.
//  Copyright © 2018年 wynne. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include "glm/glm.hpp"

class Shader
{
	public:
		unsigned int ID;
	public:
		Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
		void use();
		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;
		void setVec2(const std::string &name, const glm::vec2 &value) const;
		void setVec3(const std::string &name, const glm::vec3 &value) const;
		void setVec4(const std::string &name, const glm::vec4 &value) const;
		void setMat2(const std::string &name, const glm::mat2 &value) const;
		void setMat3(const std::string &name, const glm::mat3 &value) const;
		void setMat4(const std::string &name, const glm::mat4 &value) const;
};
#endif /* Shader_hpp */
