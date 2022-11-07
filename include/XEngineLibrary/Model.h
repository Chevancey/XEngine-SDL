#pragma once

#include <Color.h>
#include <LIB_COMPILING.h>
#include <Renderable.h>
#include <Vector2.h>
#include <nlohmann/json_fwd.hpp> //< header spécial qui fait des déclarations anticipées des classes de la lib
#include <SDL.h>
#include <filesystem>
#include <memory>
#include <vector>

class SDLRenderer;
class SDLTexture;
class Transform;

struct ModelVertex
{
	Vector2f pos;
	Vector2f uv;
	Color color;
};

class LIB_API Model : public Renderable // Un ensemble de triangles
{
public:
	Model() = default;
	Model(std::shared_ptr<const SDLTexture> texture, std::vector<ModelVertex> vertices, std::vector<int> indices);
	Model(const Model&) = default;
	Model(Model&&) = default;
	~Model() = default;

	void Draw(SDLRenderer& renderer, const Transform& cameraTransform, const Transform& transform) override;

	bool IsValid() const;

	bool SaveToFile(const std::filesystem::path& filepath) const;
	nlohmann::ordered_json SaveToJSon() const;

	Model& operator=(const Model&) = delete;
	Model& operator=(Model&&) = default;

	static Model LoadFromFile(const std::filesystem::path& filepath);
	static Model LoadFromJSon(const nlohmann::json& doc);

private:
	bool SaveToFileRegular(const std::filesystem::path& filepath) const;
	bool SaveToFileCompressed(const std::filesystem::path& filepath) const;
	bool SaveToFileBinary(const std::filesystem::path& filepath) const;

	static Model LoadFromFileRegular(const std::filesystem::path& filepath);
	static Model LoadFromFileCompressed(const std::filesystem::path& filepath);
	static Model LoadFromFileBinary(const std::filesystem::path& filepath);

	std::shared_ptr<const SDLTexture> m_texture;
	std::vector<ModelVertex> m_vertices;
	std::vector<SDL_Vertex> m_sdlVertices;
	std::vector<int> m_indices;
};




//#include <vector>
//#include <array>
//#include <nlohmann/json.hpp>
//#include <SDL.h>
//#include <LIB_COMPILING.h>
//
//class Transform;
//class SDLRenderer;
//class SDLTexture;
//
//struct LIB_API Triangle
//{
//	std::vector<SDL_Vertex> _vertices;
//};
//
//class LIB_API Model
//{
//public:
//	Model(const Model&) = default;
//	Model(Model&&) = default;
//
//	Model(const std::string& filePath);
//
//	//Model(const std::string& textureFilePath);
//	~Model() = default;
//
//	void Draw(SDLRenderer& renderer);
//
//	void LoadModel(std::ifstream& f);
//	void CreateModel();
//	void SaveModel();
//
//	Model& operator=(const Model&) = delete;
//	Model& operator=(Model&&) = default;
//
//	void SetModel(const std::string& filePath);
//	void SetTexture(const std::string& filePath);
//	void SetIndices(std::vector<int> indices);
//
//	void SetColor(int index, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
//	void SetPostion(int index, float x, float y);
//	void SetUV(int index, float x, float y);
//
//
//
//private:
//
//	std::shared_ptr<const SDLTexture> m_texture;
//	std::vector<int> m_indices;
//	std::vector<SDL_Vertex> m_vertices;
//
//	std::string m_modelFilePath;
//	std::string m_textureFilePath;
//
//	//std::vector<std::string> Datatype;
//};