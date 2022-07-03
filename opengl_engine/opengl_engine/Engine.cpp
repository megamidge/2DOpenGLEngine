#include "Engine.h"
#include "TextRenderer.h"
//Instantiate statics
//-------------------
GLFWwindow* OpenGL_Engine::Engine::Window = glfwCreateWindow(100, 100, "init", NULL, NULL);
OpenGL_Engine::Shader OpenGL_Engine::Engine::orthoShader = Shader();
OpenGL_Engine::Shader OpenGL_Engine::Engine::projectionShader = Shader();
OpenGL_Engine::Shader OpenGL_Engine::Engine::textShader = Shader();
OpenGL_Engine::Drawable OpenGL_Engine::Engine::rect3 = OpenGL_Engine::Drawable();
OpenGL_Engine::Clickable OpenGL_Engine::Engine::click1 = OpenGL_Engine::Clickable();
OpenGL_Engine::Engine* OpenGL_Engine::Engine::engine_instance = NULL;
//-------------------

///<summary>Handles the window changing size.
///Updates the projectin matrices in the process.</summary>
///<TODO>Should fire an event that any object can subscribe to do scaling updates etc</TODO>
void OpenGL_Engine::Engine::FrameBuffer_Size_Callback(GLFWwindow * window, int width, int height)
{

	glViewport(0, 0, width, height);


	//projection
	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.0f, 100.0f);
	int projLoc = glGetUniformLocation(projectionShader.ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glm::mat4 ortho(1.0f);
	ortho = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.0f, 100.0f);

	orthoShader.Use();
	int orthLoc = glGetUniformLocation(orthoShader.ID, "projection");
	glUniformMatrix4fv(orthLoc, 1, GL_FALSE, glm::value_ptr(ortho));
	textShader.Use();
	orthLoc = glGetUniformLocation(textShader.ID, "projection");
	glUniformMatrix4fv(orthLoc, 1, GL_FALSE, glm::value_ptr(ortho));
}
///<summary>Handles the cursor moving.</summary>
void OpenGL_Engine::Engine::Cursor_Pos_Callback(GLFWwindow * window, double xpos, double ypos)
{
	//std::cout << "Click:" << xpos << "/" << ypos << std::endl;
	int width;
	int height;
	glfwGetFramebufferSize(window, &width, &height);
	double posX = xpos;
	double posY = height - ypos;
	double glPosX = ((2 / (double)width) * posX) - 1.0;
	double glPosY = ((2 / (double)height) * posY) - 1.0;
	glm::mat4 newTransform(1.0);
	newTransform = glm::translate(newTransform, glm::vec3(posX, posY, 0.0));
	rect3.SetTransform(newTransform);

}
void OpenGL_Engine::Engine::Mouse_Button_Callback(GLFWwindow * window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		Engine::engine_instance->LeftMouseButtonClickSig(xpos, ypos);
	}
}
///<summary>Processes input into the window</summary>
///<TODO>In future, should raise an event that using applications can use to handle input theirself</TODO>
void OpenGL_Engine::Engine::ProcessInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
///<summary>Create an instance of this engine with a specified windo width and height</summary>
OpenGL_Engine::Engine::Engine(int pWindowWidth, int pWindowHeight)
{
	Engine::engine_instance = this;
	windowHeight = pWindowHeight;
	windowWidth = pWindowWidth;
}
///<summary>Initialise the engine and opengl states</summary>
OpenGL_Engine::Engine::Error_States OpenGL_Engine::Engine::Initialise()
{
	//Set up the window
	//-----------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);//MAC OS X
	window = glfwCreateWindow(windowWidth, windowHeight, "Sam Smith's OpenGL Engine", NULL, NULL);
	Window = window;
	//Error detection
	if (window == NULL)
		return Error_States(FAILED_WINDOW_CREATE);
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return Error_States(FAILED_GLAD_INITIALISE);
	//-----------------

	//Set up viewport and shaders
	//--------------------------------------------
	glViewport(0, 0, windowWidth, windowHeight);
	//Callbacks
	glfwSetFramebufferSizeCallback(window, OpenGL_Engine::Engine::FrameBuffer_Size_Callback);
	glfwSetCursorPosCallback(window, OpenGL_Engine::Engine::Cursor_Pos_Callback);
	glfwSetMouseButtonCallback(window,OpenGL_Engine::Engine::Mouse_Button_Callback);
	//Shaders
	orthoShader = Shader("OrthoVertexShader.GLSL", "FragmentShader.GLSL");
	projectionShader = Shader("ProjectionVertexShader.GLSL", "FragmentShader.GLSL");
	textShader = Shader("TextVertexShader.GLSL", "TextFragmentShader.GLSL");
	//projection
	projectionShader.Use();
	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.0f, 100.0f);
	int projLoc = glGetUniformLocation(projectionShader.ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	//orthographic
	orthoShader.Use();
	glm::mat4 ortho(1.0f);
	ortho = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, 0.0f, 100.0f);
	int orthLoc = glGetUniformLocation(orthoShader.ID, "projection");
	glUniformMatrix4fv(orthLoc, 1, GL_FALSE, glm::value_ptr(ortho));

	//text
	textShader.Use();
	ortho = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, 0.0f, 100.0f);
	orthLoc = glGetUniformLocation(textShader.ID, "projection");
	glUniformMatrix4fv(orthLoc, 1, GL_FALSE, glm::value_ptr(ortho));

	orthoShader.Use();
	//view
	glm::mat4 view(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));
	int viewLoc = glGetUniformLocation(orthoShader.ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	textShader.Use();
	viewLoc = glGetUniformLocation(textShader.ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	//--------------------------------------------
	//Done
	//-------------------------
	return Error_States(NONE);
	//-------------------------
}
///<summary>Load anything that needs to be loaded</summary>
///<TODO>Application should override (but also call this too just in case) To load its objects</TODO>
void OpenGL_Engine::Engine::Load()
{
	//This is all just debug really
	//-----------------------------
	std::string path2 = "C:\\Users\\sssam\\Pictures\\pcars2_bmw_bw.png";
	unsigned int textureID2 = OpenGL_Engine::Texture::AddTexture(path2);
	std::string path = "C:\\Users\\sssam\\Pictures\\Circle.png";
	unsigned int textureID = OpenGL_Engine::Texture::AddTexture(path);
	rect1 = Drawable(10.0f, glm::vec2(0.55f, 0.55f), glm::vec4(1.0f, 1.0f, 0.25f, 1.0f), OpenGL_Engine::Drawable::UnitMode::percent, glm::vec4(0, 0, windowWidth, windowHeight), &orthoShader, OpenGL_Engine::Drawable::Gravity::center);
	rect1.Load();
	rect2 = Drawable(0.1f, glm::vec2(0.5f, 0.5f), textureID2, OpenGL_Engine::Drawable::UnitMode::percent, glm::vec4(0, 0, windowWidth, windowHeight), &orthoShader, OpenGL_Engine::Drawable::Gravity::center);
	rect2.Load();
	rect3 = Drawable(0.0f, textureID, OpenGL_Engine::Drawable::UnitMode::pixel, glm::vec4(-50, -50, 50, 50), &orthoShader);
	rect3.Load();

	click1 = Clickable(10.0f, glm::vec2(50.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.25f, 1.0f), OpenGL_Engine::Drawable::UnitMode::pixel, glm::vec4(0, 0, windowWidth, windowHeight), &orthoShader, OpenGL_Engine::Drawable::Gravity::rightCenter);
	click1.Load();
	click1.ButtonClickSig.connect(boost::bind(&Engine::Click1Clicked, this));


	textRenderer = TextRenderer("OpenGL Engine",glm::vec4(1.0,0.5,0.0,1.0), glm::vec2(1000,1000),72,&textShader);
	textRenderer.Load();

	//-----------------------------
}
void OpenGL_Engine::Engine::Click1Clicked() {
	std::cout << "Clicked" << std::endl;
}
///<summary>Call update functions, but also process input. (Should be overridden but still called)</summary>
void OpenGL_Engine::Engine::Update(double deltaTime)
{
	//Call the process window input function
	//---------------------------------------
	ProcessInput(window);
	//---------------------------------------
	//Update any objects
	//-------------------
	rect1.Update(deltaTime);
	rect2.Update(deltaTime);
	rect3.Update(deltaTime);
	click1.Update(deltaTime);
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	rect1.UpdateBounds(glm::vec4(0.0f, 0.0f, (float)height, (float)width));
	rect2.UpdateBounds(glm::vec4(0.0f, 0.0f, (float)height, (float)width));
	click1.UpdateBounds(glm::vec4(0.0f, 0.0f, (float)height, (float)width));
	//-------------------
}
///<summary>Perform rendering operations</summary>
void OpenGL_Engine::Engine::Render()
{
	//Enable transparency
	//-------------------
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//-------------------

	//Use the ortho shader (isn't strictly required here)
	//---------------------------------------------------
	//orthoShader.Use();
	//---------------------------------------------------

	//Set clear colour and clear the screen
	//-------------------------------------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//-------------------------------------

	//Set polygon mode to draw front and back faces, and fill (again, not strictly required but just a fail-safe)
	//-----------------------------------------------------------------------------------------------------------
	//In future, this could use a variable or 2. These variables could be changed in settings to say.. draw everything wireframed for debug
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//------------------------------------------------------------------------------------------------------------


	//Render objects to buffer
	//------------------------
	//This should only be here for debug, when finished this loop shouldn't actually render any objects,
	//The application itself (as this is an engine) should make things to render and then render them in an overridden Render loop.
	rect1.Render();
	rect2.Render();
	rect3.Render();
	click1.Render();
	//-------------------------

	//Debug text rendering
	//---------------------
	textRenderer.Render();
	//---------------------

	//Use the orthoShader after rending any text. Not sure why but somewhere something is relying on this as it messes up scaling
	//------------------------------------------
	//orthoShader.Use();
	//------------------------------------------

	//Swap the buffers (draw to the window)
	//-------------------------------------
	glfwSwapBuffers(window);
	//-------------------------------------
	//Poll window events
	//------------------
	glfwPollEvents();
	//------------------
}

///<summary>Starts the operations of the engine going (enters the loop and starts updating and rendering).</summary>
void OpenGL_Engine::Engine::Run()
{
	double old_t = glfwGetTime(); //Get the current time and store it.
	while (!glfwWindowShouldClose(window)) {
		//Get delta time
		//-------------------------
		double t = glfwGetTime(); //Get current time.
		double deltaT = (t - old_t); //The different in time is the current time - the last recorded time.
		old_t = t; //The last recorded time is updated
		//--------------------------

		//Call update with the delta time
		//-------------------------------
		Update(deltaT);
		//-------------------------------
		//Call the render function
		//------------------------
		Render();
		//------------------------
	}
	glfwTerminate();
}
