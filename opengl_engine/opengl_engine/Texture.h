#pragma once
#include <glad\glad.h>
#include <iostream>
#include "stb_image.h"
namespace OpenGL_Engine {
	static class Texture {
	public:
		static unsigned int AddTexture(std::string texturePath);
	};
}