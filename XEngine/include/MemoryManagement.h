#include<SDL.h>
#include<SDL_Image.h>
#include<memory>
#include<iostream>
#include<map>
#include<string>


class SDLTexture;
class SDLRenderer;

class MemoryManagement
{
public:

	MemoryManagement();
	~MemoryManagement();

	std::shared_ptr<SDLTexture> getTexture(SDLRenderer& renderer, std::string filePath);


	void Purge();
private:
	//static MemoryManagement* m_instance;
	SDL_Surface* CreateSurface();

	std::map<std::string, std::shared_ptr<SDLTexture>> m_texturesMap;
};