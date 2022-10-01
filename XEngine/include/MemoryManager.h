#include<SDL.h>
#include<SDL_Image.h>
#include<memory>
#include<iostream>
#include<map>
#include<string>


class SDLTexture;
class SDLRenderer;

class MemoryManager
{
public:
	~MemoryManager();

	static MemoryManager* GetInstance()
	{
		return m_instance = (m_instance != nullptr) ? m_instance : new MemoryManager;
	}

	std::shared_ptr<SDLTexture> getTexture(SDLRenderer& renderer, std::string filePath);


	void Purge();
private:
	MemoryManager();
	static MemoryManager* m_instance;
	SDL_Surface* CreateSurface();

	std::map<std::string, std::shared_ptr<SDLTexture>> m_texturesMap;
};