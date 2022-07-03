#include "Drawable.h"
#include "Engine.h"
///<summary>Makes vertices based on object properties!</summary>
void OpenGL_Engine::Drawable::MakeVertices()
{
	//Create the vertices
	//Perform checks to create the right set of vertices for whats given
	//-------------------------------------------------------------------
	float sizeX, sizeY, contextWidth, contextHeight, marginX, marginY, marginZ, marginW;

	contextWidth = mContextBounds.w - mContextBounds.y;//Top - bottom;
	contextHeight = mContextBounds.z - mContextBounds.x;//Right-left;
	glm::vec2 size(mSize.x, mSize.y);
	glm::vec4 margin(mMargin.x, mMargin.x, mMargin.z, mMargin.w);
	if (mUnitMode == UnitMode::percent) {
		//Create percentage based values

		sizeX = contextWidth * mSize.x;
		sizeY = contextHeight * mSize.y;

		marginX = contextHeight * mMargin.x;
		marginY = contextWidth * mMargin.y;
		marginZ = contextHeight * mMargin.z;
		marginW = contextWidth * mMargin.w;

		size = glm::vec2(sizeX, sizeY);
		margin = glm::vec4(marginX, marginY, marginZ, marginW);
	}

	if (size.x > 0 && size.y > 0) {
		switch (mGravity) {
		case OpenGL_Engine::Drawable::Gravity::center:
			glm::vec2 centerPoint(mContextBounds.y + contextWidth / 2.0f, mContextBounds.x + contextHeight / 2.0f);
				mVertices = {
				//|Vertices                                                                          |  |//Colour       |   | //Texture|
				centerPoint.x + size.x / 2.0f,	centerPoint.y + size.y / 2.0f,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,		1.0f,1.0f,  // top right
				centerPoint.x + size.x / 2.0f,	centerPoint.y - size.y / 2.0f,			0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,		1.0f,0.0f, // bottom right
				centerPoint.x - size.x / 2.0f,	centerPoint.y - size.y / 2.0f,			0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,	0.0f,0.0f,  // bottom left
				centerPoint.x - size.x / 2.0f,	centerPoint.y + size.y / 2.0f,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,	0.0f,1.0f   // top left 
			};
			break;
		default:
			mVertices = {
				//|Vertices                                                                          |  |//Colour       |   | //Texture|
				mContextBounds.y + margin.w + size.x,	mContextBounds.x + margin.x + size.y,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,		1.0f,1.0f,  // top right
				mContextBounds.y + margin.w + size.x,	mContextBounds.x + margin.x,			0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,		1.0f,0.0f, // bottom right
				mContextBounds.y + margin.y,			mContextBounds.x + margin.x,			0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,	0.0f,0.0f,  // bottom left
				mContextBounds.y + margin.y,			mContextBounds.x + margin.x + size.y,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,	0.0f,1.0f   // top left 
			};
			break;
		}
	}
	else if (size.y > 0) {
		//float contextHeight = mContextBounds.z - mContextBounds.x; //Top - bottom
		switch (mGravity) {
		case OpenGL_Engine::Drawable::Gravity::center:
			mVertices = {
				//|Vertices                                                                                         |  |//Colour       |   | //Texture|
				mContextBounds.w - margin.w,	mContextBounds.x + (contextHeight / 2.0f) + (size.y / 2.0f),	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,		1.0f,1.0f,  // top right
				mContextBounds.w - margin.w,	mContextBounds.x + (contextHeight / 2.0f) - (size.y / 2.0f),	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,		1.0f,0.0f, // bottom right
				mContextBounds.y + margin.y,	mContextBounds.x + (contextHeight / 2.0f) - (size.y / 2.0f),	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,	0.0f,0.0f,  // bottom left
				mContextBounds.y + margin.y,	mContextBounds.x + (contextHeight / 2.0f) + (size.y / 2.0f),	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,	0.0f,1.0f   // top left 
			};
			break;
		case OpenGL_Engine::Drawable::Gravity::bottomCenter:
			mVertices = {
				//|Vertices                                                                 |  |//Colour       |   | //Texture|
				mContextBounds.w - margin.w,	mContextBounds.x + margin.z + size.y,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,		1.0f,1.0f,  // top right
				mContextBounds.w - margin.w,	mContextBounds.x + margin.z,			0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,		1.0f,0.0f, // bottom right
				mContextBounds.y + margin.y,	mContextBounds.x + margin.x,			0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,	0.0f,0.0f,  // bottom left
				mContextBounds.y + margin.y,	mContextBounds.x + margin.x + size.y,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,	0.0f,1.0f   // top left 
			};
			break;
		case OpenGL_Engine::Drawable::Gravity::topCenter:
			mVertices = {
				//|Vertices                                                                 |  |//Colour       |   | //Texture|
				mContextBounds.w - margin.w,	mContextBounds.z - margin.z,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,		1.0f,1.0f,  // top right
				mContextBounds.w - margin.w,	mContextBounds.z - margin.z - size.y,			0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,		1.0f,0.0f, // bottom right
				mContextBounds.y + margin.y,	mContextBounds.z - margin.x - size.y,			0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,	0.0f,0.0f,  // bottom left
				mContextBounds.y + margin.y,	mContextBounds.z - margin.x,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,	0.0f,1.0f   // top left 
			};
			break;
		}
	}
	else if (size.x > 0) {
		//float contextWidth = mContextBounds.w - mContextBounds.y; //Right - left
		switch (mGravity) {
		case OpenGL_Engine::Drawable::Gravity::center:
			mVertices = {
				//|Vertices                                                                                                         |  |//Colour       |   | //Texture|
				mContextBounds.y + mContextBounds.y + (contextWidth / 2.0f) + (size.x / 2.0f),	mContextBounds.z - margin.z,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,		1.0f,1.0f,  // top right
				mContextBounds.y + mContextBounds.y + (contextWidth / 2.0f) + (size.x / 2.0f),	mContextBounds.x + margin.x,   0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,		1.0f,0.0f, // bottom right
				mContextBounds.y + mContextBounds.y + (contextWidth / 2.0f) - (size.x / 2.0f),	mContextBounds.x + margin.x,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,	0.0f,0.0f,  // bottom left
				mContextBounds.y + mContextBounds.y + (contextWidth / 2.0f) - (size.x / 2.0f),	mContextBounds.z - margin.z,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,	0.0f,1.0f   // top left 
			};
			break;
		case OpenGL_Engine::Drawable::Gravity::leftCenter:
			mVertices = {
				//|Vertices                                                                 |  |//Colour       |   | //Texture|
				mContextBounds.y + margin.w + size.x,	mContextBounds.z - margin.z,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,		1.0f,1.0f,  // top right
				mContextBounds.y + margin.w + size.x,	mContextBounds.x + margin.x,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,		1.0f,0.0f, // bottom right
				mContextBounds.y + margin.y,			mContextBounds.x + margin.x,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,	0.0f,0.0f,  // bottom left
				mContextBounds.y + margin.y,			mContextBounds.z - margin.z,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,	0.0f,1.0f   // top left 
			};
			break;
		case OpenGL_Engine::Drawable::Gravity::rightCenter:
			mVertices = {
				//|Vertices                                                                 |  |//Colour       |   | //Texture|
				mContextBounds.w - margin.w,			mContextBounds.z - margin.z,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,		1.0f,1.0f,  // top right
				mContextBounds.w - margin.w,			mContextBounds.x + margin.x,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,		1.0f,0.0f, // bottom right
				mContextBounds.w - margin.y - size.x,	mContextBounds.x + margin.x,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,	0.0f,0.0f,  // bottom left
				mContextBounds.w - margin.y - size.x,	mContextBounds.z - margin.z,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,	0.0f,1.0f   // top left 
			};
			break;
		}
	}
	else {
		mVertices = {
			//|Vertices                                                         |  |//Colour       |   | //Texture|
			mContextBounds.w - margin.w,	mContextBounds.z - margin.z,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,		1.0f,1.0f,  // top right
			mContextBounds.w - margin.w,	mContextBounds.x + margin.x,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,		1.0f,0.0f, // bottom right
			mContextBounds.y + margin.y,	mContextBounds.x + margin.x,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,	0.0f,0.0f,  // bottom left
			mContextBounds.y + margin.y,	mContextBounds.z - margin.z,	0.0f,	mColour.x,mColour.y,mColour.z,mColour.w,	0.0f,1.0f   // top left 
		};
	}
	//-------------------------------------------------------------------
	//float mVertices[] = {
	//	mTopRight.x,  mTopRight.y, 0.0f, 1.0f,0.0f,0.0f,1.0f,1.0f,  // top right
	//	mTopRight.x, mBottomLeft.y, 0.0f, 0.0f,1.0f,0.0f,1.0f,0.0f, // bottom right
	//	mBottomLeft.x, mBottomLeft.y, 0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,  // bottom left
	//	mBottomLeft.x, mTopRight.y, 0.0f,1.0f,0.0f,1.0f,0.0f,1.0f   // top left 
	//};
}
OpenGL_Engine::Drawable::Drawable(unsigned int VAO, unsigned int VBO, Shader* pShader, glm::vec2 bottomLeft, glm::vec2 topRight, unsigned int textureID)
{
	mVAOid = VAO;//These don't actually need to be passed
	mVBOid = VBO;//These don't actually need to be passed
	//^At best, these can be passed back out/made public to the world if anything needs to knw the VAO and VBO id of the object (not likely)^
	mShader = pShader;
	mTransform = glm::mat4(1.0f);
	mMargin = glm::vec4(bottomLeft.y, bottomLeft.x, topRight.y, topRight.x);
	mTextureId = textureID;
	hasTexture = true;
}

OpenGL_Engine::Drawable::Drawable(const float pMargin, const unsigned int pTextureId, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader)
{
	mMargin = glm::vec4(pMargin);
	mUnitMode = units;
	mContextBounds = pContextBounds;
	mTextureId = pTextureId;
	hasTexture = true;
	mTransform = glm::mat4(1.0f);
	mSize = glm::vec2(0.0);
	mColour = glm::vec4(1.0);
	mShader = pShader;
}

OpenGL_Engine::Drawable::Drawable(const float pMargin, const glm::vec3 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader)
{
	mMargin = glm::vec4(pMargin);
	mColour = glm::vec4(pColour, 0.1f);
	mUnitMode = units;
	mContextBounds = pContextBounds;
	hasTexture = false;
	mTransform = glm::mat4(1.0f);
	mTextureId = 0;
	mSize = glm::vec2(0.0);
	mShader = pShader;
}

OpenGL_Engine::Drawable::Drawable(const float pMargin, const glm::vec4 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader)
{
	mMargin = glm::vec4(pMargin);
	mColour = pColour;
	mUnitMode = units;
	mContextBounds = pContextBounds;
	hasTexture = false;
	mTransform = glm::mat4(1.0f);
	mTextureId = 0;
	mSize = glm::vec2(0.0);
	mShader = pShader;
}

OpenGL_Engine::Drawable::Drawable(const glm::vec4 pMargin, const unsigned int pTextureId, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader)
{
	mMargin = pMargin;
	mTextureId = pTextureId;
	mUnitMode = units;
	mContextBounds = pContextBounds;
	hasTexture = true;
	mTransform = glm::mat4(1.0f);
	mSize = glm::vec2(0.0);
	mColour = glm::vec4(1.0);
	mShader = pShader;
}

OpenGL_Engine::Drawable::Drawable(const glm::vec4 pMargin, const glm::vec3 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader)
{
	mMargin = pMargin;
	mColour = glm::vec4(pColour, 1.0f);
	mUnitMode = units;
	mContextBounds = pContextBounds;
	hasTexture = false;
	mTransform = glm::mat4(1.0f);
	mSize = glm::vec2(0.0);
	mTextureId = 0;
	mShader = pShader;
}

OpenGL_Engine::Drawable::Drawable(const glm::vec4 pMargin, const glm::vec4 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader)
{
	mMargin = pMargin;
	mColour = pColour;
	mUnitMode = units;
	mContextBounds = pContextBounds;
	hasTexture = false;
	mTransform = glm::mat4(1.0f);
	mTextureId = 0;
	mSize = glm::vec2(0.0);
	mShader = pShader;
}

OpenGL_Engine::Drawable::Drawable(const float pMargin, const glm::vec2 pSize, const unsigned int pTextureId, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader, OpenGL_Engine::Drawable::Gravity pGravity)
{
	mMargin = glm::vec4(pMargin);
	mSize = pSize;
	mTextureId = pTextureId;
	mUnitMode = units;
	mContextBounds = pContextBounds;
	hasTexture = true;
	mTransform = glm::mat4(1.0f);
	mColour = glm::vec4(1.0);
	mShader = pShader;
	mGravity = pGravity;
}

OpenGL_Engine::Drawable::Drawable(const float pMargin, const glm::vec2 pSize, const glm::vec3 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader, OpenGL_Engine::Drawable::Gravity pGravity)
{
	mMargin = glm::vec4(pMargin);
	mSize = pSize;
	mColour = glm::vec4(pColour, 1.0f);
	mUnitMode = units;
	mContextBounds = pContextBounds;
	hasTexture = false;
	mTransform = glm::mat4(1.0f);
	mTextureId = 0;
	mShader = pShader;
	mGravity = pGravity;
}

OpenGL_Engine::Drawable::Drawable(const float pMargin, const glm::vec2 pSize, const glm::vec4 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader, OpenGL_Engine::Drawable::Gravity pGravity)
{
	mMargin = glm::vec4(pMargin);
	mSize = pSize;
	mColour = pColour;
	mUnitMode = units;
	mContextBounds = pContextBounds;
	hasTexture = false;
	mTransform = glm::mat4(1.0f);
	mTextureId = 0;
	mShader = pShader;
	mGravity = pGravity;
}

OpenGL_Engine::Drawable::Drawable(const glm::vec4 pMargin, const glm::vec2 pSize, const unsigned int pTextureId, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader, OpenGL_Engine::Drawable::Gravity pGravity)
{
	mMargin = pMargin;
	mSize = pSize;
	mTextureId = pTextureId;
	mUnitMode = units;
	mContextBounds = pContextBounds;
	hasTexture = true;
	mTransform = glm::mat4(1.0f);
	mColour = glm::vec4(1.0);
	mShader = pShader;
	mGravity = pGravity;
}

OpenGL_Engine::Drawable::Drawable(const glm::vec4 pMargin, const glm::vec2 pSize, const glm::vec3 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader, OpenGL_Engine::Drawable::Gravity pGravity)
{
	mMargin = pMargin;
	mSize = pSize;
	mColour = glm::vec4(pColour, 1.0f);
	mUnitMode = units;
	mContextBounds = pContextBounds;
	hasTexture = false;
	mTransform = glm::mat4(1.0f);
	mTextureId = 0;
	mShader = pShader;
	mGravity = pGravity;
}

OpenGL_Engine::Drawable::Drawable(const glm::vec4 pMargin, const glm::vec2 pSize, const glm::vec4 pColour, const UnitMode units, const glm::vec4 pContextBounds, OpenGL_Engine::Shader* pShader, OpenGL_Engine::Drawable::Gravity pGravity)
{
	mMargin = pMargin;
	mSize = pSize;
	mColour = pColour;
	mUnitMode = units;
	mContextBounds = pContextBounds;
	hasTexture = false;
	mTransform = glm::mat4(1.0f);
	mTextureId = 0;
	mShader = pShader;
	mGravity = pGravity;
}

OpenGL_Engine::Drawable::Drawable()
{
}

void OpenGL_Engine::Drawable::UpdateBounds(const glm::vec4 pContextBounds)
{
	mContextBounds = pContextBounds;
	MakeVertices();
	ReLoad();
}

void OpenGL_Engine::Drawable::SetTransform(glm::mat4 pTransformation)
{
	mTransform = pTransformation;
}

glm::mat4 OpenGL_Engine::Drawable::GetTransform()
{
	return mTransform;
}

void OpenGL_Engine::Drawable::Load()
{
	mShader->Use();
	glGenVertexArrays(1, &mVAOid);
	glBindVertexArray(mVAOid);
	glGenBuffers(1, &mVBOid);
	glBindBuffer(GL_ARRAY_BUFFER, mVBOid);

	MakeVertices();
	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};
	glGenBuffers(1, &mEBOid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBOid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), &mVertices.front(), GL_STATIC_DRAW);

	MakeVertices();
	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Colour attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Texture coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);
}
///<summary>ReLoads the object without generating new buffers (uses the same buffers)</summary>
void OpenGL_Engine::Drawable::ReLoad()
{
	mShader->Use();
	//glGenVertexArrays(1, &mVAOid);
	glBindVertexArray(mVAOid);
	//glGenBuffers(1, &mVBOid);
	glBindBuffer(GL_ARRAY_BUFFER, mVBOid);

	MakeVertices();
	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};
	//glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBOid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), &mVertices.front(), GL_STATIC_DRAW);

	//MakeVertices();
	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Colour attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//Texture loading + binding //TODO Move texture loading to its own class that just returns an ID, use that ID here
	//-------------------------
	/*glGenTextures(1, &mTextureId);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	std::string str = "C:\\Users\\sssam\\Pictures\\TestTexture.png";
	unsigned char *data = stbi_load(str.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
	std::cout << "DRAWABLE::FAILED_TO_LOAD_TEXTURE" << std::endl;
	}
	stbi_image_free(data);*/
	//Texture coordiante attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);
}
void OpenGL_Engine::Drawable::Render()
{

	mShader->Use();
	//Transformation stuff
	//--------------------
	glm::mat4 model(1.0f);
	model = mTransform;
	//send to shader
	int modelLoc = glGetUniformLocation(mShader->ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	int hasTextureLocation = glGetUniformLocation(mShader->ID, "hasTexture");
	glUniform1i(hasTextureLocation, hasTexture);
	//Rendering
	//-------------------
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glDrawArrays(GL_TRIANGLES, 0, 4);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextureId);
	glBindVertexArray(mVAOid);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//-------------------
}

void OpenGL_Engine::Drawable::Update(double deltaTime)
{
	//Update object properties here e.g: animating the transformation
}

glm::vec4 OpenGL_Engine::Drawable::Bounds()
{
	//x = bottom, y = left, z = top, w = right
	float bottom = mVertices[10];
	float top = mVertices[1];
	float left = mVertices[18];
	float right = mVertices[0];
	//std::cout << "B" << bottom << " L" << left << " T" << top << " R" << right << std::endl;
	return glm::vec4(bottom, left, top, right);
}
