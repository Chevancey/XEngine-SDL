#include <vector>
#include <array>
#include <nlohmann/json.hpp>
#include <SDL.h>

class Transform;
class SDLRenderer;
class SDLTexture;

struct Triangle
{
	std::vector<SDL_Vertex> _vertices;
};

class Model
{
public:
	Model(const Model&) = default;
	Model(Model&&) = default;

	Model(const std::string& filePath);

	//Model(const std::string& textureFilePath);
	~Model() = default;

	void Draw(SDLRenderer& renderer);

	void LoadModel(std::ifstream& f);
	void CreateModel();
	void SaveModel();

	Model& operator=(const Model&) = delete;
	Model& operator=(Model&&) = default;

private:
	int fileIndex;

	std::shared_ptr<const SDLTexture> m_texture;
	std::vector<int> m_indices;
	std::vector<SDL_Vertex> m_vertices;

	std::string m_modelFilePath;
	std::string m_textureFilePath;

	//std::vector<std::string> Datatype;
};