#include<SDL.h>
#include<SDL_Image.h>
#include<memory>
#include<map>
#include<string>

class MemoryManagement 
{
public:
	MemoryManagement();

	std::shared_ptr<SDL_Texture> getTexture();


private:
	//std::map<SDL_Texture a, std::string b>;
};