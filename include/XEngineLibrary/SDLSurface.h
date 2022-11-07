#pragma once
#include <iostream>
#include <string>
#include <SDL_image.h>
#include <LIB_COMPILING.h>

class LIB_API SDLSurface
{
public:
	SDLSurface(int width, int height);
	SDLSurface(const SDLSurface&) = delete; // constructeur par copie
	SDLSurface(SDLSurface&& surface) noexcept; // constructeur par mouvement
	~SDLSurface();

	void FillRect(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	const std::string& GetFilePath() const;
	SDL_Surface* get() const;
	Uint8* GetPixels();
	const Uint8* GetPixels() const;

	bool IsValid() const;

	SDLSurface& operator=(const SDLSurface&) = delete; // opérateur d'assignation par copie
	SDLSurface& operator=(SDLSurface&& surface) noexcept; // opérateur d'assignation par mouvement

	static SDLSurface LoadFromFile(std::string filepath);

private:
	SDLSurface(SDL_Surface* surface, std::string filepath = "");

	SDL_Surface* m_surface;
	std::string m_filepath;
};