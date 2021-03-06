// opengl_engine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "misc_functions.h"
#include <fstream>
#include <string>
#include "Engine.h"
int main(){
	//OpenGL_Engine::Engine engine = OpenGL_Engine::Engine(974, 478);
	OpenGL_Engine::Engine engine = OpenGL_Engine::Engine(1000, 1000);
	engine.Initialise();
	engine.Load();
	engine.Run();
	return 0;
}

