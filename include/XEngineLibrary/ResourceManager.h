#pragma once
#include <memory> //< std::shared_ptr
#include <unordered_map> //< std::unordered_map est plus efficace que std::map pour une association clé/valeur
#include <LIB_COMPILING.h>

class SDLRenderer;
class SDLTexture;
class SDL_Surface;
class Model;

class LIB_API ResourceManager
{
public:
	ResourceManager(SDLRenderer& renderer);
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	~ResourceManager();

	void Clear();

	const std::shared_ptr<Model>& GetModel(const std::string& texturePath);
	const std::shared_ptr<SDLTexture>& GetTexture(const std::string& texturePath);

	void Purge();

	static ResourceManager& Instance();

	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;;

private:
	std::shared_ptr<Model> m_missingModel;
	std::shared_ptr<SDLTexture> m_missingTexture;
	std::unordered_map<std::string /*texturePath*/, std::shared_ptr<Model>> m_models;
	std::unordered_map<std::string /*texturePath*/, std::shared_ptr<SDLTexture>> m_textures;

	SDLRenderer& m_renderer;
	static ResourceManager* s_instance;
};