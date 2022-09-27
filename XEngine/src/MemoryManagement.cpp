#include "MemoryManagement.h"
#include "SDLTexture.h"
#include "SDLRenderer.h"
#include "SDLSurface.h"

//MemoryManagement* MemoryManagement::m_instance = nullptr;

MemoryManagement::MemoryManagement()
{
}

MemoryManagement::~MemoryManagement()
{
}

//std::shared_ptr<SDLTexture> MemoryManagement::getTexture(SDLRenderer& renderer, std::string filePath)
//{
//	bool isExisting = SDLSurface::textureExisting(filePath);
//
//	if (isExisting && m_texturesMap.size() > 0)
//	{
//		for (auto iterator = m_texturesMap.begin(); iterator != m_texturesMap.end(); iterator++) 
//		{
//			if (iterator->first == filePath) 
//			{
//				std::cout << "The file already exists: " + filePath << std::endl;
//				return iterator->second;
//			}
//		}
//	}
//	else if (!isExisting)
//	{
//		std::cout << "ERROR - FILE DOES NOT EXIST: " + filePath << std::endl;
//		std::shared_ptr<SDLTexture> tempTexture = std::make_shared<SDLTexture>(SDLTexture::LoadSurface(renderer, CreateSurface()));
//		return tempTexture;
//	}
//
//	std::shared_ptr<SDLTexture> tempTexture = std::make_shared<SDLTexture>(SDLTexture::LoadFromFile(renderer, filePath));
//	m_texturesMap.insert({ filePath, tempTexture });
//	std::cout << "File is now added to list: " + filePath << std::endl;
//
//	return tempTexture;
//}

std::shared_ptr<SDLTexture> MemoryManagement::getTexture(SDLRenderer& renderer, std::string filePath)
{
	bool isExisting = SDLSurface::textureExisting(filePath);

	if (isExisting && m_texturesMap.size() > 0)
	{
		for (auto iterator = m_texturesMap.begin(); iterator != m_texturesMap.end(); iterator++)
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
		std::shared_ptr<SDLTexture> tempTexture = std::make_shared<SDLTexture>(SDLTexture::LoadSurface(renderer, CreateSurface()));
		return tempTexture;
	}

	std::shared_ptr<SDLTexture> tempTexture = std::make_shared<SDLTexture>(SDLTexture::LoadFromFile(renderer, filePath));
	m_texturesMap.emplace(filePath, tempTexture);
	std::cout << "File is now added to list: " + filePath << std::endl;

	return tempTexture;
}


void MemoryManagement::Purge()
{
	for (auto it = m_texturesMap.begin(); it != m_texturesMap.end(); it++)
	{
		std::cout << "Delete Map Elements: " << it->first << std::endl;
		m_texturesMap.erase(it);
	}

	m_texturesMap.clear();
}

SDL_Surface* MemoryManagement::CreateSurface()
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

