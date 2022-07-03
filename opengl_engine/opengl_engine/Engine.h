#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include "Shader.h"
#include "Drawable.h"
#include "Clickable.h"
#include "TextRenderer.h"
#include "stb_image.h"
#include <vector>
#include "Texture.h"
#include <boost/signals2/signal.hpp>
namespace OpenGL_Engine {
	class Engine {
	public:
		enum Error_States {
			NONE,
			FAILED_WINDOW_CREATE,
			FAILED_GLAD_INITIALISE,
			FAILED_READ_SHADER,
			FAILED_COMPILE_SHADER,
			FAILED_LINK_SHADER
		};

		static OpenGL_Engine::Drawable drawables[10];
		static OpenGL_Engine::Drawable rect3;
		static OpenGL_Engine::Clickable click1;
		static void FrameBuffer_Size_Callback(GLFWwindow * window, int width, int height);
		static void Cursor_Pos_Callback(GLFWwindow * window, double xpos, double ypos);
		static void Mouse_Button_Callback(GLFWwindow * window, int button, int action, int mods);
		Engine(int pWindowWidth, int pWindowHeight);//Constructor for engine
		Error_States Initialise();//Initialise the engine. Returns an Error_State based on any errors. Error state is NONE if successful.
		void Load();//Load objects
		void Run();//Start the loop
		static GLFWwindow * Window;
		static Engine* engine_instance;
		boost::signals2::signal<void(double, double)> LeftMouseButtonClickSig;
		static OpenGL_Engine::Shader orthoShader;
		static OpenGL_Engine::Shader projectionShader;
		static OpenGL_Engine::Shader textShader;
		void Click1Clicked();
	private: GLFWwindow * window; //The window in use
			 int windowHeight;
			 int windowWidth;

			 

			 unsigned int VAOs[200];
			 unsigned int VBOs[200];

			 void ProcessInput(GLFWwindow * window);
			 void Update(double deltaTime);//Update objects
			 void Render();//Render objects


			 Drawable rect1, rect2;
			 TextRenderer textRenderer;
	};
}