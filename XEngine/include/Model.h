#include <nlohmann/json.hpp>
#include <SDL.h>

class Transform;
class SDLRenderer;

struct Triangle
{
	SDL_Vertex verrices[3];
};

class Model
{
public:
	Model();
	void Draw(SDLRenderer& renderer, const Transform& transform);
	~Model();

private:

	std::vector<Triangle> m_triangles;
};