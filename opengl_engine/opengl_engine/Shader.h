#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
namespace OpenGL_Engine {
	class Shader {
	public:
		enum Error_States {
			NONE,
			FAILED_READ_SHADER,
			FAILED_COMPILE_SHADER,
			FAILED_LINK_SHADER
		};
		unsigned int ID;
		Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
		Shader();
		void Use();
		void SetBool(const std::string &name, bool value) const;
		void SetInt(const std::string &name, int value) const;
		void SetFloat(const std::string &name, float value) const;
	private:
	};
}
#endif
