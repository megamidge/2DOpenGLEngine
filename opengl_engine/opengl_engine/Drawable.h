#pragma once
#include <glad\glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>
namespace OpenGL_Engine {
	class Drawable {
	public:
		enum class UnitMode : unsigned int;//Forward declare the enum
		enum class Gravity : unsigned int;//Forward declare
	private:
		unsigned int mVAOid;
		unsigned int mVBOid;
		unsigned int mEBOid;

		std::array<float, 36> mVertices;//My vertices. Should be length 32 as 32 vertices WILL be defined

		Shader* mShader;//The shader i should use

		glm::mat4 mTransform;

		glm::vec4 mMargin;//(bottom,left,top,right)
		glm::vec2 mSize;//width and height. A value of 0=don't care. When mode is percentage this value should be less than 1.
		UnitMode mUnitMode;

		unsigned int mTextureId;
		glm::vec4 mColour;

		glm::vec4 mContextBounds; //The area i can draw in (for example, just pass the window bounds)

		GLboolean hasTexture;

		Gravity mGravity;

		void MakeVertices();

	public:
		enum class UnitMode : unsigned int {//Declare the enum (i want it to be public)
			pixel = 0,
			percent = 1
		};
		enum class Gravity : unsigned int {
			none = 0,
			
			center = 1,

			topCenter = 2,
			bottomCenter = 3,
			leftCenter = 4,
			rightCenter = 5
		};
		Drawable(unsigned int VAO, unsigned int VBO, OpenGL_Engine::Shader* pShader, glm::vec2 bottomLeft, glm::vec2 topRight, unsigned int textureID);

		Drawable(float pMargin, unsigned int pTextureId, UnitMode units, glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader);//For margin and texture
		Drawable(const float pMargin, const glm::vec3 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader);//For margin and colour with no alpha
		Drawable(const float pMargin, const glm::vec4 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader);//For margin and colour with alpha
		Drawable(const glm::vec4 pMargin, const unsigned int pTextureId, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader);//For margin and texture. Margin is defined as vec4(bottom,left,top,right);
		Drawable(const glm::vec4 pMargin, const glm::vec3 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader);
		Drawable(const glm::vec4 pMargin, const glm::vec4 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader);
		Drawable(const float pMargin, const glm::vec2 pSize, const unsigned int pTextureId, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader, OpenGL_Engine::Drawable::Gravity pGravity);
		Drawable(const float pMargin, const glm::vec2 pSize, const glm::vec3 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader, OpenGL_Engine::Drawable::Gravity pGravity);
		Drawable(const float pMargin, const glm::vec2 pSize, const glm::vec4 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader, OpenGL_Engine::Drawable::Gravity pGravity);
		Drawable(const glm::vec4 pMargin, const glm::vec2 pSize, const unsigned int pTextureId, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader, OpenGL_Engine::Drawable::Gravity pGravity);
		Drawable(const glm::vec4 pMargin, const glm::vec2 pSize, const glm::vec3 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader, OpenGL_Engine::Drawable::Gravity pGravity);
		Drawable(const glm::vec4 pMargin, const glm::vec2 pSize, const glm::vec4 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader, OpenGL_Engine::Drawable::Gravity pGravity);

		Drawable();

		void UpdateBounds(const glm::vec4 pContextBounds);
		void SetTransform(glm::mat4 pTransformation);
		glm::mat4 GetTransform();
		void virtual Load();
		void virtual ReLoad();
		void virtual Render();
		void virtual Update(double deltaTime);
	protected:
		glm::vec4 Bounds();
	};
}