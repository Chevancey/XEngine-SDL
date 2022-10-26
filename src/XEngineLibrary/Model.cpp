#include <fstream>
#include <iostream>
#include "Model.h"
#include "SDLRenderer.h"
#include "ResourceManager.h"
#include "SDLTexture.h"

Model::Model(const std::string& filePath) :
	m_modelFilePath(filePath)
{
	std::ifstream f(filePath);
	if (!f.is_open())
	{
		std::cout << "This doesnt exist" << std::endl;
		CreateModel();
	}
	else
	{
		std::cout << filePath << " exists" << std::endl;
		LoadModel(f);
	}
}


//READ
void Model::LoadModel(std::ifstream& f)
{
	nlohmann::json model;
	f >> model;

	if (model.contains("texture")) 
	{
		m_textureFilePath = model["texture"];
		m_texture = ResourceManager::Instance().GetTexture(m_textureFilePath);
	}
	
	if (model.contains("indices")) 
	{
		m_indices = model["indices"].get<std::vector<int>>();
	}

	if (model.contains("vertices")) 
	{
		nlohmann::json vertices = model["vertices"];
		m_vertices.resize(vertices.size());

		for (int i = 0; i < vertices.size(); ++i)
		{
			nlohmann::json position = vertices[i]["position"];
			nlohmann::json color = vertices[i]["color"];
			nlohmann::json uv = vertices[i]["uv"];

			m_vertices[i].position =
			{
				position[0].get<float>(),
				position[1].get<float>()
			};

			m_vertices[i].color =
			{
				color[0].get<Uint8>(),
				color[1].get<Uint8>(),
				color[2].get<Uint8>(),
				color[3].get<Uint8>()
			};

			m_vertices[i].tex_coord =
			{
				uv[0].get<float>(),
				uv[1].get<float>()
			};
		}
	}
}

//WRITE
void Model::SaveModel()
{
	std::ofstream fw(m_modelFilePath);
	nlohmann::json model;

	model["texture"] = m_textureFilePath;
	std::cout << m_textureFilePath << std::endl;

	model["indices"] = m_indices;

	for (int i = 0; i < m_indices.size(); ++i)
	{
		std::cout << model["indices"][i] << std::endl;
	}

	std::vector<std::unordered_map<std::string, std::vector<float>>> vertices;
	vertices.resize(m_vertices.size());

	model["vertices"] = vertices;

	for (int i = 0; i < model["vertices"].size(); ++i)
	{
		model["vertices"][i]["position"] =
		{
			m_vertices[i].position.x,
			m_vertices[i].position.y
		};

		model["vertices"][i]["uv"] =
		{
			m_vertices[i].tex_coord.x,
			m_vertices[i].tex_coord.y
		};

		model["vertices"][i]["color"] =
		{
			m_vertices[i].color.r,
			m_vertices[i].color.g,
			m_vertices[i].color.b,
			m_vertices[i].color.a
		};
	};

	fw << model.dump(4);
	fw.close();
}

void Model::CreateModel() 
{
	std::cout << "THIS WAS CALLED" << std::endl;
}

void Model::Draw(SDLRenderer& renderer)
{
	SDL_RenderGeometry(renderer.get(), m_texture->get(), m_vertices.data(), m_vertices.size(), m_indices.data(), m_indices.size());
}


// Set things to check whether the file has changed when saved....


void Model::SetModel(const std::string& filePath)
{
	m_modelFilePath = filePath;
}

void Model::SetTexture(const std::string& filePath) 
{
	m_textureFilePath = filePath;
}

void Model::SetIndices(std::vector<int> indices) 
{
	m_indices = indices;
}

void Model::SetColor(int index, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	m_vertices[index].color = { r, g, b, a };
}

void Model::SetPostion(int index, float x, float y)
{
	m_vertices[index].position = { x, y};
}

void Model::SetUV(int index, float x, float y)
{
	m_vertices[index].tex_coord = { x, y };
}