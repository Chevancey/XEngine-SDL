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


	std::shared_ptr<SDLTexture> tempTexture = std::make_shared<SDLTexture>(SDLTexture::LoadFromFile(renderer, filePath));
	m_texturesMap.insert({ filePath, tempTexture });
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

