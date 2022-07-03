#include "FontManager.h"
#include <iostream>

FT_Face* OpenGL_Engine::FontManager::CreateFont(std::string pIdentifier, std::string pPath,int size)
{
	if (ft != NULL) {
		if (FT_Init_FreeType(&ft))
			std::cout << "ERROR::FONTMANAGER::FREETYPE: COULD_NOT_INIT_FREETYPE_LIB" << std::endl;
	}
	FT_Face face;
	if (FT_New_Face(ft, pPath.c_str(), 0, &face)) {
		std::cout << "ERROR::FONTMANAGER::FREETYPE: FAILED_LOADING_FONT" << std::endl;
		return &face;
	}
	FT_Set_Pixel_Sizes(face, 0, size);
	//Fonts.insert(std::pair<std::string, FT_Face*>(pIdentifier, &face));
	//FT_Done_FreeType(ft);
	return &face;
}

//FT_Face* OpenGL_Engine::FontManager::GetFont(std::string pIdentifier)
//{
//	return Fonts[pIdentifier];
//}

