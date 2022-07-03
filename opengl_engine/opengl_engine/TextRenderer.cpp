#include "TextRenderer.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include "FontManager.h"
#include "Drawable.h"
#include "Engine.h"

OpenGL_Engine::TextRenderer::TextRenderer()
{
}

OpenGL_Engine::TextRenderer::TextRenderer(std::string pText, glm::vec4 pColour, glm::vec2 pSize, float pFontSize, Shader* pShader)
{
	mShader = pShader;
	mColour = pColour;
	mText = pText;
	mWidth = pSize.x;
	mHeight = pSize.y;
	mFontSize = pFontSize;
}



void OpenGL_Engine::TextRenderer::Load()
{
	mShader->Use();
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	FT_Face face;
	if (FT_New_Face(ft, "C:\\Users\\sssam\\Documents\\Projects\\opengl_engine\\fonts\\Aero Matics Bold Italic.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	
	FT_Set_Pixel_Sizes(face, 0, mFontSize);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);//Disable byte-alignment restriction
	for (GLubyte c = 0; c < 128; c++) {
		//Load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cout << "ERROR::FREETYPE: FAILED_TO_LOAD_GLYPH" << std::endl;
			continue;
		}
		//Gen texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		//set texture optoins
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//Now store char for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width,face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left,face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, Character>(c, character));

	}
	glBindTexture(GL_TEXTURE_2D, 0);
	//They call me the butler because i _clean up_
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindVertexArray(0);

	mVAOid = VAO;
	mVBOid = VBO;

	//render to texture stuff
	// The framebuffer, which regroups 0, 1, or more texture, and 0 or 1 depth buffer.
	GLuint frameBufferID;
	glGenFramebuffers(1, &frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	//Create texture to render to

	GLuint renderedTextureID;
	glGenTextures(1, &renderedTextureID);
	//bind
	glBindTexture(GL_TEXTURE_2D, renderedTextureID);
	//give empty image to opengl
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//Optional depth buffer
	/*GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1000, 1000);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);*/
	//configure framebuffer
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTextureID, 0);
	//Set the list of draw buffers.
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers);//1 is the size of DrawBuffers
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer is not ok!" << std::endl;
	RenderText(mShader, mText, 0.0f, mHeight/2, 1.0f, mColour,frameBufferID);
	//Drawable d = Drawable(0.0f, glm::vec2(0.5,0.0), (unsigned int)(renderedTextureID), Drawable::UnitMode::percent, glm::vec4(0, 0, 1000, 1000), &Engine::orthoShader,Drawable::Gravity::center);
	renderedTexture = Drawable(0.0f, (unsigned int)(renderedTextureID), Drawable::UnitMode::percent, glm::vec4(0, 0, 1000, 1000), &Engine::orthoShader);

	renderedTexture.Load();


}
void OpenGL_Engine::TextRenderer::Render()
{
	mShader->Use();


	int hasTextureLocation = glGetUniformLocation(mShader->ID, "hasTexture");
	glUniform1i(hasTextureLocation, true);

	//glm::mat4 model(1.0f);
	//int modelLoc = glGetUniformLocation(mShader->ID, "model");
	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//RenderText(mShader, mText, 0.0f, 50.0f, 1.0f, mColour, 0);
	renderedTexture.Render();

	//glDisable(GL_BLEND);
}
///<summary>Renders a line of text</summary>
void OpenGL_Engine::TextRenderer::RenderText(Shader* pShader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec4 color,GLuint framebufferID)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Activate render state
	pShader->Use();

	
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);


	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(mVAOid);
	glm::vec4 colour = glm::vec4(color);
	int colourLoc = glGetUniformLocation(pShader->ID, "colour");
	glUniform4fv(colourLoc, 1, glm::value_ptr(colour));
	//iterate through chars
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {
		Character ch = Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y)*scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		//Update VBO for each char
		GLfloat vertices[6][4] = {
			{xpos,		ypos + h,	0.0, 0.0},
			{xpos,		ypos,		0.0, 1.0},
			{xpos + w,	ypos,		1.0, 1.0},

			{xpos,		ypos + h,	0.0, 0.0},
			{xpos + w,	ypos,		1.0, 1.0},
			{xpos + w,	ypos + h,	1.0, 0.0}
		};
		//Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		//Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, mVBOid);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; //Bitshifht by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
}
