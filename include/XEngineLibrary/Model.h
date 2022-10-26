#include <vector>
#include <array>
#include <nlohmann/json.hpp>
#include <SDL.h>
#include <LIB_COMPILING.h>

class Transform;
class SDLRenderer;
class SDLTexture;

struct LIB_API Triangle
{
	std::vector<SDL_Vertex> _vertices;
};

class LIB_API Model
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

	void SetModel(const std::string& filePath);
	void SetTexture(const std::string& filePath);
	void SetIndices(std::vector<int> indices);

	void SetColor(int index, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void SetPostion(int index, float x, float y);
	void SetUV(int index, float x, float y);



private:

	std::shared_ptr<const SDLTexture> m_texture;
	std::vector<int> m_indices;
	std::vector<SDL_Vertex> m_vertices;

	std::string m_modelFilePath;
	std::string m_textureFilePath;

	//std::vector<std::string> Datatype;
};