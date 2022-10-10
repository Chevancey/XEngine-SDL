#include "ResourceManager.h"
#include "SDLTexture.h"
#include "SDLRenderer.h"
#include "SDLSurface.h"
#include <stdexcept>


ResourceManager::ResourceManager(SDLRenderer& renderer) :
	m_renderer(renderer)
{
	if (s_instance != nullptr)
		throw std::runtime_error("only one ResourceManager can be created");

	s_instance = this;
}

ResourceManager::~ResourceManager()
{
	s_instance = nullptr;
}

void ResourceManager::Clear()
{
	m_missingTexture.reset();
	m_textureMap.clear();
}


const std::shared_ptr<SDLTexture>& ResourceManager::GetTexture(const std::string& filePath)
{

	auto it = m_textureMap.find(filePath);
	if (it != m_textureMap.end())
		return it->second;

	SDLSurface surface = SDLSurface::LoadFromFile(filePath);
	if (!surface.textureExisting(filePath))
	{
		if (!m_missingTexture)
		{
			m_missingTexture = std::make_shared<SDLTexture>(SDLTexture::LoadSurface(m_renderer, CreateSurface()));

		}
		m_textureMap.emplace(filePath, m_missingTexture);
		return m_missingTexture;
	}

	std::shared_ptr<SDLTexture> texture = std::make_shared<SDLTexture>(SDLTexture::LoadFromSurface(m_renderer, surface));

	it = m_textureMap.emplace(filePath, std::move(texture)).first;

	return it->second;
}


void ResourceManager::Purge()
{
	for (auto it = m_textureMap.begin(); it != m_textureMap.end(); it++)
	{
		std::cout << it->first << " use count: " << it->second.use_count() << std::endl;
		if (it->second.unique())
		{
			std::cout << "Delete Map Elements: " << it->first << std::endl;
			it = m_textureMap.erase(it);
			it = m_textureMap.begin();
		} 
	}
}

SDL_Surface* ResourceManager::CreateSurface()
{
	int surfacesize = 100;
	int rectSize = 100 / 10;
	SDL_Surface* surface = SDL_CreateRGBSurface(0, surfacesize, surfacesize, 32, 0, 0, 0, 0);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			SDL_Rect rect({ i * rectSize, j * rectSize, (i + 1) * rectSize, (j + 1) * rectSize });
			if ((i + j + 1) % 2 == 0)
			{
				SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 255, 0, 255));
			}
			else
			{
				SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0, 0, 0));
			}
		}
	}

	return surface;
}

ResourceManager& ResourceManager::Instance()
{
	if (s_instance == nullptr)
		throw std::runtime_error("ResourceManager hasn't been instantied");

	return *s_instance;
}

ResourceManager* ResourceManager::s_instance = nullptr;