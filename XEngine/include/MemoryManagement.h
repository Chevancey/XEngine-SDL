#include<SDL.h>
#include<SDL_Image.h>
#include<memory>
#include<iostream>
#include<map>
#include<string>
#include "SDLTexture.h"

class MemoryManagement 
{
public:
	MemoryManagement();
	~MemoryManagement();

	static SDL_Texture& checkExistance(std::string name, SDL_Texture& texture);

	std::map<std::string, SDL_Texture> textureMap;

private:
	//std::map<std::string, SDL_Texture&> textureMap;
};