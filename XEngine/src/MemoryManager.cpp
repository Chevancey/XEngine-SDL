#include "MemoryManager.h"
#include "SDLTexture.h"
#include "SDLRenderer.h"
#include "SDLSurface.h"

MemoryManager* MemoryManager::m_instance = nullptr;

MemoryManager::MemoryManager()
{
}

MemoryManager::~MemoryManager()
{
	m_texturesMap.clear();
	std::cout << "All the map has been deleted: " << std::endl;
}

std::shared_ptr<SDLTexture> MemoryManager::getTexture(SDLRenderer& renderer, const std::string& filePath)
{
	bool isExisting = SDLSurface::textureExisting(filePath);
	std::cout << m_texturesMap.size() << std::endl;
	if (isExisting && m_texturesMap.size() > 0)
	{
		auto iterator = m_texturesMap.find(filePath);
		if (iterator != m_texturesMap.end()) 
		{
			if (iterator->first == filePath)
			{
				std::cout << "The file already exists: " + filePath << std::endl;
				return iterator->second;
			}
		}
	}
	else if (!isExisting)
	{
		std::cout << "ERROR - FILE DOES NOT EXIST: " + filePath << std::endl;
		//std::shared_ptr<SDLTexture> tempTexture = ;
		return std::make_shared<SDLTexture>(SDLTexture::LoadSurface(renderer, CreateSurface()));
		//return std::make_shared<SDLTexture>(SDLTexture::LoadSurface(renderer, CreateSurface()));
	}

	std::shared_ptr<SDLTexture> tempTexture = std::make_shared<SDLTexture>(SDLTexture::LoadFromFile(renderer, filePath));
	m_texturesMap.emplace(filePath, tempTexture);
	//m_texturesMap.emplace(filePath, std::make_shared<SDLTexture>(SDLTexture::LoadFromFile(renderer, filePath)));
	std::cout << "File is now added to list: " + filePath + " used: " << tempTexture.use_count() << " times. The size of the Map is now: " << m_texturesMap.size() << std::endl;
	//return std::make_shared<SDLTexture>(SDLTexture::LoadFromFile(renderer, filePath));
	return tempTexture;
}


void MemoryManager::Purge()
{
	for (auto it = m_texturesMap.begin(); it != m_texturesMap.end(); it++)
	{
		std::cout << it->first << " use count: " << it->second.use_count() << std::endl;
		if (it->second.unique())
		{
			std::cout << "Delete Map Elements: " << it->first << std::endl;
			it = m_texturesMap.erase(it);
			
			//for (auto it = m_texturesMap.begin(); it != m_texturesMap.end(); it++) 
			//{
			//	it.begin();
			//}
		} 
	}
}

SDL_Surface* MemoryManager::CreateSurface()
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

