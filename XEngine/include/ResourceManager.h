#pragma once

#include <memory> //< std::shared_ptr
#include <unordered_map> //< std::unordered_map est plus efficace que std::map pour une association clé/valeur

class SDLRenderer;
class SDLTexture;
class SDL_Surface;

class ResourceManager
{
public:
	ResourceManager(SDLRenderer& renderer);
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	~ResourceManager();

	void Clear();

	const std::shared_ptr<SDLTexture>& GetTexture(const std::string& texturePath);

	void Purge();

	static ResourceManager& Instance();

	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

private:
	std::shared_ptr<SDLTexture> m_missingTexture;
	std::unordered_map<std::string, std::shared_ptr<SDLTexture>> m_textureMap;
	SDLRenderer& m_renderer;

	SDL_Surface* CreateSurface();
	static ResourceManager* s_instance;
};