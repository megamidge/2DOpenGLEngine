#pragma once
#include <glad/glad.h>
#include "Drawable.h"
#include <glm\common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <boost/signals2/signal.hpp>
namespace OpenGL_Engine {
	class Clickable : public Drawable {
	public:
		Clickable(float pMargin, unsigned int pTextureId, UnitMode units, glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader) :Drawable(pMargin, pTextureId, units, pContextBounds, pShader) {};//For margin and texture
		Clickable(const float pMargin, const glm::vec3 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader) :Drawable(pMargin, pColour, units, pContextBounds, pShader) {};//For margin and colour with no alpha
		Clickable(const float pMargin, const glm::vec4 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader) :Drawable(pMargin, pColour, units, pContextBounds, pShader) {};//For margin and colour with alpha
		Clickable(const glm::vec4 pMargin, const unsigned int pTextureId, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader) :Drawable(pMargin, pTextureId, units, pContextBounds, pShader) {};//For margin and texture. Margin is defined as vec4(bottom,left,top,right);
		Clickable(const glm::vec4 pMargin, const glm::vec3 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader) :Drawable(pMargin, pColour, units, pContextBounds, pShader) {};
		Clickable(const glm::vec4 pMargin, const glm::vec4 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader) :Drawable(pMargin, pColour, units, pContextBounds, pShader) {};
		Clickable(const float pMargin, const glm::vec2 pSize, const unsigned int pTextureId, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader, OpenGL_Engine::Drawable::Gravity pGravity) :Drawable(pMargin, pSize, pTextureId, units, pContextBounds, pShader, pGravity) {};
		Clickable(const float pMargin, const glm::vec2 pSize, const glm::vec3 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader, OpenGL_Engine::Drawable::Gravity pGravity) :Drawable(pMargin, pSize, pColour, units, pContextBounds, pShader, pGravity) {};
		Clickable(const float pMargin, const glm::vec2 pSize, const glm::vec4 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader, OpenGL_Engine::Drawable::Gravity pGravity) :Drawable(pMargin, pSize, pColour, units, pContextBounds, pShader, pGravity) {};
		Clickable(const glm::vec4 pMargin, const glm::vec2 pSize, const unsigned int pTextureId, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader, OpenGL_Engine::Drawable::Gravity pGravity) :Drawable(pMargin, pSize, pTextureId, units, pContextBounds, pShader, pGravity) {};
		Clickable(const glm::vec4 pMargin, const glm::vec2 pSize, const glm::vec3 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader, OpenGL_Engine::Drawable::Gravity pGravity) :Drawable(pMargin, pSize, pColour, units, pContextBounds, pShader, pGravity) {};
		Clickable(const glm::vec4 pMargin, const glm::vec2 pSize, const glm::vec4 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader, OpenGL_Engine::Drawable::Gravity pGravity) :Drawable(pMargin, pSize, pColour, units, pContextBounds, pShader, pGravity) {};

		Clickable();

		void Load();
		void ReLoad();
		void Render();
		void Update(double deltaTime);
		bool InBounds(glm::vec2 pPos);

		void On_LeftClickDown(double xpos, double ypos);

		boost::signals2::signal<void()> ButtonClickSig;

	};
}