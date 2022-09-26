#include "MemoryManagement.h"

MemoryManagement::MemoryManagement()
{
	//auto sps = std::make_shared<std::string>("Hello");
}

SDL_Texture& MemoryManagement::checkExistance(std::string name, SDL_Texture& texture)
{
	if (name == textureMap.find(name)->first)
	{
		return textureMap.find(name)->second;
	}
	else 
	{
		textureMap.insert({name, texture});
		return texture;
	}
}