#pragma once
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
namespace OpenGL_Engine {
	static class FontManager
	{
	public:
		static FT_Face* CreateFont(std::string pIdentifier, std::string pPath, int size);
		//static FT_Face* GetFont(std::string pIdentifier);

		//static std::map<std::string, FT_Face*> Fonts;
	private:
		static FT_Library ft;
	};
}

