#include "Clickable.h"
#include "Engine.h"
OpenGL_Engine::Clickable::Clickable()
{
}
void OpenGL_Engine::Clickable::Load()
{
	Drawable::Load();
	//OpenGL_Engine::Engine::engine_instance->LeftMouseButtonClickSig.connect(this);
	OpenGL_Engine::Engine::engine_instance->LeftMouseButtonClickSig.connect(boost::bind(&Clickable::On_LeftClickDown,this,_1,_2));
}
void OpenGL_Engine::Clickable::ReLoad()
{
	Drawable::ReLoad();
}
void OpenGL_Engine::Clickable::Render()
{
	Drawable::Render();
}
void OpenGL_Engine::Clickable::Update(double deltaTime)
{
	Drawable::Update(deltaTime);
}
///<summary>Returns true if the given position is within the bounds of the object</summary>
bool OpenGL_Engine::Clickable::InBounds(glm::vec2 pPos)
{
	//Tested working
	glm::vec4 bounds = Bounds();
	if (pPos.x > bounds.y && pPos.x < bounds.w) {
		if (pPos.y > bounds.x && pPos.y < bounds.z) {
			return true;
		}
	}
	return false;
}

void OpenGL_Engine::Clickable::On_LeftClickDown(double xpos, double ypos)
{
	if (InBounds(glm::vec2(xpos, ypos)))
		ButtonClickSig();//Call my click signal.
}
