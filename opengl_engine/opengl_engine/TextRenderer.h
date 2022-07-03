#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include "Shader.h"
#include "Drawable.h"
#include <string>
namespace OpenGL_Engine {
	class TextRenderer
	{
	public:
		TextRenderer();
		TextRenderer(std::string pText, glm::vec4 pColour, glm::vec2 pSize, float pFontSize, Shader*pShader);

		void Render();
		void Load();

		glm::vec4 mColour;
		std::string mText;
	private:
		struct Character {
			GLuint TextureID;
			glm::ivec2 Size;
			glm::ivec2 Bearing;
			GLuint Advance;
		};

		std::map<GLchar, Character> Characters;
		unsigned int mVAOid;
		unsigned int mVBOid;
		Shader* mShader;
		void RenderText(Shader *pShader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec4 color, GLuint framebufferID);


		float mWidth, mHeight, mFontSize;
		Drawable renderedTexture;
	};
}

