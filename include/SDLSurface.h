#include <iostream>
#include <string>
#include <SDL_image.h>

class SDLSurface
{
public:
	SDLSurface(const SDLSurface&) = delete;
	SDLSurface(SDLSurface&& surface);

	SDLSurface();
	~SDLSurface();
	SDLSurface& operator=(SDLSurface&& surface) noexcept;

	SDL_Surface* get();
	static SDLSurface LoadFromFile(const std::string& filepath);
private:
	SDLSurface(SDL_Surface* surface);
	SDL_Surface* m_surface;
};