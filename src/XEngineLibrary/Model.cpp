#include <Model.h>
#include <ResourceManager.h>
#include <SDLRenderer.h>
#include <SDLTexture.h>
#include <Transform.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/std.h>
#include <lz4.h>
#include <nlohmann/json.hpp>
#include <cassert>
#include <fstream>

constexpr unsigned int FileVersion = 1;

Model::Model(std::shared_ptr<const SDLTexture> texture, std::vector<ModelVertex> vertices, std::vector<int> indices) :
	m_texture(std::move(texture)),
	m_vertices(std::move(vertices)),
	m_indices(std::move(indices))
{
	/*
	Pour afficher notre mod�le, nous devons donner � la SDL un vector<SDL_Vertex>, nous aurions pu directement en prendre un (au lieu d'un vector<ModelVertex>) mais nous aurions �t�
	confront� au m�me probl�me : lors de l'affichage, pour appliquer le Transform, nous devons calculer la nouvelle position.
	Pour affecter la transformation aux vertices (sans perdre leur valeur originale) nous devons dupliquer l'information, avec un autre std::vector<SDL_Vertex>.
	N�anmoins, faire un nouveau vector � chaque affichage (= op�ration tr�s fr�quente) signifierait faire une grosse allocation m�moire tr�s souvent, ce qui est g�n�ralement � �viter.
	On peut ici �tre astucieux et conserver le vector en membre, d'une ex�cution � l'autre et r�utiliser sa m�moire.
	De plus, comme tex_coord et color ne sont pas affect�s par le Transform, on peut les pr�calculer � la construction directement
	*/

	m_sdlVertices.resize(m_vertices.size());
	for (std::size_t i = 0; i < m_vertices.size(); ++i)
	{
		const ModelVertex& modelVertex = m_vertices[i];
		SDL_Vertex& sdlVertex = m_sdlVertices[i];

		// Conversion de nos structures vers les structures de la SDL
		sdlVertex.tex_coord = SDL_FPoint{ modelVertex.uv.x, modelVertex.uv.y };

		Uint8 r, g, b, a;
		modelVertex.color.ToRGBA8(r, g, b, a);

		sdlVertex.color = SDL_Color{ r, g, b, a };
	}
}

void Model::Draw(SDLRenderer& renderer, const Transform& cameraTransform, const Transform& transform)
{
	// On s'assure que les deux tableaux font la m�me taille (assert crash imm�diatement le programme si la condition pass�e est fausse)
	assert(m_vertices.size() == m_sdlVertices.size());
	for (std::size_t i = 0; i < m_vertices.size(); ++i)
	{
		const ModelVertex& modelVertex = m_vertices[i];
		SDL_Vertex& sdlVertex = m_sdlVertices[i];

		// tex_coord et color sont d�j� g�r�s par le constructeur
		Vector2f transformedPos = transform.TransformPoint(modelVertex.pos);
		transformedPos = cameraTransform.TransformInversePoint(transformedPos);
		sdlVertex.position = SDL_FPoint{ transformedPos.x, transformedPos.y };
	}

	if (!m_indices.empty())
	{
		SDL_RenderGeometry(renderer.get(),
			(m_texture) ? m_texture->get() : nullptr,
			m_sdlVertices.data(), static_cast<int>(m_sdlVertices.size()),
			m_indices.data(), static_cast<int>(m_indices.size()));
	}
	else
	{
		SDL_RenderGeometry(renderer.get(),
			(m_texture) ? m_texture->get() : nullptr,
			m_sdlVertices.data(), static_cast<int>(m_sdlVertices.size()),
			nullptr, 0);
	}
}

bool Model::IsValid() const
{
	// Un mod�le peut ne pas avoir de texture/indices, mais il a forc�ment des vertices
	return !m_vertices.empty();
}

bool Model::SaveToFile(const std::filesystem::path& filepath) const
{
	if (filepath.extension() == ".model")
		return SaveToFileRegular(filepath);
	else if (filepath.extension() == ".cmodel")
		return SaveToFileCompressed(filepath);
	else if (filepath.extension() == ".bmodel")
		return SaveToFileBinary(filepath);
	else
	{
		fmt::print(stderr, fg(fmt::color::red), "unknown extension {}\n", filepath.extension());
		return false;
	}
}

nlohmann::ordered_json Model::SaveToJSon() const
{
	// nlohmann::json et nlohmann::ordered_json ont les m�mes fonctionnalit�s, mais ce dernier pr�serve l'ordre d'insertion des cl�s (qui ne change rien aux donn�es, c'est juste plus joli :D )

	// On va sauvegarder tous les champs int�ressants � l'aide de l'op�rateur [] de nlohmann::json qui, comme pour std::(unordered_)map, cr�� une cl�/valeur si la cl� n'existe pas
	// une autre approche aurait �t� d'instancier les documents puis de les affecter
	nlohmann::ordered_json doc;

	// L'ajout d'un champ "version" permet de faire �voluer le format dans le futur
	doc["version"] = FileVersion;

	// Faisons r�f�rence � la texture via son chemin, si elle en a un
	if (m_texture)
	{
		const std::string& texturePath = m_texture->GetFilePath();
		if (!texturePath.empty())
			doc["texture"] = texturePath;
	}

	// On enregistre les indices si nous en avons
	if (!m_indices.empty())
	{
		nlohmann::ordered_json& indices = doc["indices"];
		for (int i : m_indices)
			indices.push_back(i);
	}

	nlohmann::ordered_json& vertices = doc["vertices"];
	for (const ModelVertex& modelVertex : m_vertices)
	{
		nlohmann::ordered_json& vertex = vertices.emplace_back();

		nlohmann::ordered_json& pos = vertex["pos"];
		pos["x"] = modelVertex.pos.x;
		pos["y"] = modelVertex.pos.y;

		nlohmann::ordered_json& uv = vertex["uv"];
		uv["u"] = modelVertex.uv.x;
		uv["v"] = modelVertex.uv.y;

		nlohmann::ordered_json& color = vertex["color"];
		color["r"] = modelVertex.color.r;
		color["g"] = modelVertex.color.g;
		color["b"] = modelVertex.color.b;

		// Le champ "a" (alpha) est optionnel et sa valeur sera de 1 si on ne l'enregistre pas
		// Cela permet d'�conomiser un peu de place
		if (modelVertex.color.a != 1.f)
			color["a"] = modelVertex.color.a;
	}

	return doc;
}

Model Model::LoadFromFile(const std::filesystem::path& filepath)
{
	if (filepath.extension() == ".model")
		return LoadFromFileRegular(filepath);
	else if (filepath.extension() == ".cmodel")
		return LoadFromFileCompressed(filepath);
	else if (filepath.extension() == ".bmodel")
		return LoadFromFileBinary(filepath);
	else
	{
		fmt::print(stderr, fg(fmt::color::red), "unknown extension {}\n", filepath.extension());
		return {};
	}
}

Model Model::LoadFromJSon(const nlohmann::json& doc)
{
	// Le champ version nous permet de savoir si le format a �t� g�n�r� par une version ult�rieure de notre programme
	// qui serait incompatible avec notre propre version
	unsigned int version = doc["version"];
	if (version > FileVersion)
	{
		fmt::print(stderr, fg(fmt::color::red), "model file has unsupported version {} (current version is {})", version, FileVersion);
		return {}; //< on retourne un Model construit par d�faut (on pourrait �galement lancer une exception)
	}

	std::string texturePath = doc.value("texture", "");

	// Textures
	std::shared_ptr<const SDLTexture> texture;
	if (!texturePath.empty())
		texture = ResourceManager::Instance().GetTexture(texturePath);

	// Indices
	std::vector<int> indices;

	// Astuce: en C++ l'�criture `if (init; cond)` est autoris�e et permet d'initialiser une variable temporaire
	// mais de sp�cifier la fa�on dont on va faire le test (la condition du if est donc ici `it != doc.end()`)
	if (auto it = doc.find("indices"); it != doc.end())
	{
		const nlohmann::json& indiceArray = it.value();
		for (int i : indiceArray)
			indices.push_back(i);
	}

	// Vertices
	const nlohmann::json& verticeArray = doc["vertices"];

	std::vector<ModelVertex> vertices;
	for (const nlohmann::json& vertex : verticeArray)
	{
		// emplace_back construit un �l�ment dans un vector et retourne une r�f�rence sur celui-ci
		ModelVertex& modelVertex = vertices.emplace_back();

		const nlohmann::json& positionDoc = vertex["pos"];
		modelVertex.pos = Vector2f(positionDoc["x"], positionDoc["y"]);

		if (auto it = vertex.find("uv"); it != vertex.end())
		{
			const nlohmann::json& uvDoc = it.value();
			modelVertex.uv = Vector2f(uvDoc["u"], uvDoc["v"]);
		}

		if (auto it = vertex.find("color"); it != vertex.end())
		{
			const nlohmann::json& colorDoc = it.value();
			modelVertex.color = Color(colorDoc["r"], colorDoc["g"], colorDoc["b"], colorDoc.value("a", 1.f));
		}
	}

	return Model(std::move(texture), std::move(vertices), std::move(indices));
}

bool Model::SaveToFileRegular(const std::filesystem::path& filepath) const
{
	// Ouverture d'un fichier en �criture
	std::ofstream outputFile(filepath);
	if (!outputFile.is_open())
	{
		fmt::print(stderr, fg(fmt::color::red), "failed to open model file {}\n", filepath);
		return false;
	}

	nlohmann::ordered_json doc = SaveToJSon();
	outputFile << doc.dump(4);

	// Pas besoin de fermer le fichier, le destructeur de std::ofstream s'en occupe (c'est bon les destructeurs, mangez-en !)
	return true;
}

bool Model::SaveToFileCompressed(const std::filesystem::path& filepath) const
{
	// Ouverture d'un fichier en �criture (et en mode binaire car nous ne stockons pas du texte)
	std::ofstream outputFile(filepath, std::ios::binary);
	if (!outputFile.is_open())
	{
		fmt::print(stderr, fg(fmt::color::red), "failed to open model file {}\n", filepath);
		return false;
	}

	nlohmann::ordered_json doc = SaveToJSon();

	std::string jsonStr = doc.dump();

	// Nous devons allouer un tableau d'une taille suffisante pour stocker la version compress�e
	// La fonction LZ4_compressBound nous donne la taille compress�e maximale possible avec une taille donn�e
	int maxSize = LZ4_compressBound(static_cast<int>(jsonStr.size()));

	// Lors de la d�compression en revanche, nous n'avons pas d'�quivalent pour calculer la taille maximale d�compress�e
	// nous allons donc stocker la taille au d�but du fichier, en binaire.
	// note: il est important d'utiliser un type � taille fixe pour que ce soit lisible sur plusieurs machines
	// il faudrait �galement prendre l'endianness en compte mais cela d�passe le cadre de cet exercice
	Uint32 decompressedSize = static_cast<Uint32>(jsonStr.size());
	outputFile.write(reinterpret_cast<const char*>(&decompressedSize), sizeof(Uint32));

	// Nous pouvons ensuite allouer un tableau d'octets (char), std::vector<char> ferait l'affaire ici mais un unique_ptr suffit amplement
	std::unique_ptr<char[]> compressedStr = std::make_unique<char[]>(maxSize);

	// On peut ensuite compresser avec la fonction LZ4_compress_default
	// celle-ci prend :
	// 1) une suite d'octets � compresser en entr�e, 
	// 2) un pointeur vers l'endroit o� stocker le r�sultat
	// 3) ainsi que la taille des donn�es � compresser
	// 4) la taille du buffer final, par s�curit�
	int finalSize = LZ4_compress_default(jsonStr.data(), compressedStr.get(), static_cast<int>(jsonStr.size()), static_cast<int>(maxSize));
	if (finalSize == 0)
	{
		// La compression a �chou� (�a ne devrait pas arriver)
		fmt::print(stderr, fg(fmt::color::red), "failed to compress model file\n");
		return false;
	}

	// En cas de succ�s, LZ4_compress_default renvoie la taille finale des donn�es compress�es, nous pouvons alors l'�crire directement
	// en mode binaire on utilisera alors plut�t .write
	outputFile.write(compressedStr.get(), finalSize);

	return true;
}

bool Model::SaveToFileBinary(const std::filesystem::path& filepath) const
{
	// Ouverture d'un fichier en �criture (et en mode binaire car nous ne stockons pas du texte)
	std::ofstream outputFile(filepath, std::ios::binary);
	if (!outputFile.is_open())
	{
		fmt::print(stderr, fg(fmt::color::red), "failed to open model file {}\n", filepath);
		return false;
	}

	// il est important d'utiliser un type � taille fixe pour que ce soit lisible sur plusieurs machines
	// il faudrait �galement prendre l'endianness en compte mais cela d�passe le cadre de cet exercice
	Uint8 version = FileVersion;
	outputFile.write(reinterpret_cast<const char*>(&version), sizeof(Uint8));

	// Texture (taille + suite de caract�res)
	if (m_texture)
	{
		const std::string& texturePath = m_texture->GetFilePath();

		Uint32 pathLength = static_cast<Uint32>(texturePath.size());
		outputFile.write(reinterpret_cast<const char*>(&pathLength), sizeof(Uint32));
		outputFile.write(reinterpret_cast<const char*>(&texturePath[0]), pathLength);
	}
	else
	{
		Uint32 pathLength = 0;
		outputFile.write(reinterpret_cast<const char*>(&pathLength), sizeof(Uint32));
	}

	// Indices (nombre indices + indices)
	Uint32 indexCount = static_cast<Uint32>(m_indices.size());
	outputFile.write(reinterpret_cast<const char*>(&indexCount), sizeof(Uint32));

	for (int index : m_indices)
	{
		Sint32 value = static_cast<Sint32>(index);
		outputFile.write(reinterpret_cast<const char*>(&value), sizeof(Sint32));
	}

	// Vertices (nombre vertices + vertices)
	Uint32 vertexCount = static_cast<Uint32>(m_vertices.size());
	outputFile.write(reinterpret_cast<const char*>(&vertexCount), sizeof(Uint32));

	for (const auto& vertex : m_vertices)
	{
		// float est, en pratique, un taille � type fixe
		outputFile.write(reinterpret_cast<const char*>(&vertex.pos.x), sizeof(float));
		outputFile.write(reinterpret_cast<const char*>(&vertex.pos.y), sizeof(float));
		outputFile.write(reinterpret_cast<const char*>(&vertex.uv.x), sizeof(float));
		outputFile.write(reinterpret_cast<const char*>(&vertex.uv.y), sizeof(float));
		outputFile.write(reinterpret_cast<const char*>(&vertex.color.r), sizeof(float));
		outputFile.write(reinterpret_cast<const char*>(&vertex.color.g), sizeof(float));
		outputFile.write(reinterpret_cast<const char*>(&vertex.color.b), sizeof(float));
		outputFile.write(reinterpret_cast<const char*>(&vertex.color.a), sizeof(float));
	}

	return true;
}

Model Model::LoadFromFileRegular(const std::filesystem::path& filepath)
{
	// Ouverture d'un fichier en lecture
	std::ifstream inputFile(filepath);
	if (!inputFile.is_open())
	{
		fmt::print(stderr, fg(fmt::color::red), "failed to open model file {}\n", filepath);
		return {}; //< on retourne un Model construit par d�faut (on pourrait �galement lancer une exception)
	}

	return LoadFromJSon(nlohmann::json::parse(inputFile));
}

Model Model::LoadFromFileCompressed(const std::filesystem::path& filepath)
{
	// Ouverture d'un fichier en lecture (en binaire)
	std::ifstream inputFile(filepath, std::ios::binary);
	if (!inputFile.is_open())
	{
		fmt::print(stderr, fg(fmt::color::red), "failed to open model file {}\n", filepath);
		return {}; //< on retourne un Model construit par d�faut (on pourrait �galement lancer une exception)
	}

	// On lit tout le contenu dans un vector
	std::vector<char> content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

	// Nous devons allouer un tableau d'une taille suffisante pour stocker la version d�compress�e : probl�me, nous n'avons pas cette information
	// Nous l'avons donc stock�e dans un Uint32 au d�but du fichier
	Uint32 decompressedSize;
	std::memcpy(&decompressedSize, &content[0], sizeof(Uint32));

	// Petite s�curit� pour �viter les donn�es malveillantes : assurons-nous que la taille n'a pas une valeur d�lirante
	if (decompressedSize > 10'000'000) //< La taille d�passe 10MB? �vitons
	{
		fmt::print(stderr, fg(fmt::color::red), "failed to load model file {}: decompressed size is too big ({}), is the file corrupt?\n", filepath, decompressedSize);
		return {};
	}

	// Nous pouvons ensuite allouer un tableau d'octets (char), std::vector<char> ferait l'affaire ici mais un unique_ptr suffit amplement
	std::unique_ptr<char[]> decompressedStr = std::make_unique<char[]>(decompressedSize);
	if (LZ4_decompress_safe(&content[sizeof(Uint32)], decompressedStr.get(), static_cast<int>(content.size() - sizeof(Uint32)), decompressedSize) <= 0)
	{
		fmt::print(stderr, fg(fmt::color::red), "failed to load model file {}: corrupt file\n", filepath);
		return {};
	}

	return LoadFromJSon(nlohmann::json::parse(decompressedStr.get()));
}

Model Model::LoadFromFileBinary(const std::filesystem::path& filepath)
{
	// Ouverture d'un fichier en lecture (en binaire)
	std::ifstream inputFile(filepath, std::ios::binary);
	if (!inputFile.is_open())
	{
		fmt::print(stderr, fg(fmt::color::red), "failed to open model file {}\n", filepath);
		return {}; //< on retourne un Model construit par d�faut (on pourrait �galement lancer une exception)
	}

	// il est important d'utiliser un type � taille fixe pour que ce soit lisible sur plusieurs machines
	// il faudrait �galement prendre l'endianness en compte mais cela d�passe le cadre de cet exercice
	Uint8 version = FileVersion;
	inputFile.read(reinterpret_cast<char*>(&version), sizeof(Uint8));
	if (version > FileVersion)
	{
		fmt::print(stderr, fg(fmt::color::red), "model file has unsupported version {} (current version is {})", version, FileVersion);
		return {}; //< on retourne un Model construit par d�faut (on pourrait �galement lancer une exception)
	}

	Model model;

	// Texture (taille + suite de caract�res)
	Uint32 pathLength;
	inputFile.read(reinterpret_cast<char*>(&pathLength), sizeof(Uint32));

	std::string texturePath;
	if (pathLength > 0)
	{
		texturePath.resize(pathLength);
		inputFile.read(reinterpret_cast<char*>(&texturePath[0]), pathLength);
	}

	std::shared_ptr<const SDLTexture> texture;
	if (!texturePath.empty())
		texture = ResourceManager::Instance().GetTexture(texturePath);

	// Indices (nombre indices + indices)
	Uint32 indexCount;
	inputFile.read(reinterpret_cast<char*>(&indexCount), sizeof(Uint32));

	std::vector<int> indices;
	for (Uint32 i = 0; i < indexCount; ++i)
	{
		Sint32 value;
		inputFile.read(reinterpret_cast<char*>(&value), sizeof(Sint32));

		indices.push_back(static_cast<int>(value));
	}

	// Vertices (nombre vertices + vertices)
	Uint32 vertexCount;
	inputFile.read(reinterpret_cast<char*>(&vertexCount), sizeof(Uint32));

	std::vector<ModelVertex> vertices(vertexCount);
	for (auto& vertex : vertices)
	{
		// float est, en pratique, un taille � type fixe
		inputFile.read(reinterpret_cast<char*>(&vertex.pos.x), sizeof(float));
		inputFile.read(reinterpret_cast<char*>(&vertex.pos.y), sizeof(float));
		inputFile.read(reinterpret_cast<char*>(&vertex.uv.x), sizeof(float));
		inputFile.read(reinterpret_cast<char*>(&vertex.uv.y), sizeof(float));
		inputFile.read(reinterpret_cast<char*>(&vertex.color.r), sizeof(float));
		inputFile.read(reinterpret_cast<char*>(&vertex.color.g), sizeof(float));
		inputFile.read(reinterpret_cast<char*>(&vertex.color.b), sizeof(float));
		inputFile.read(reinterpret_cast<char*>(&vertex.color.a), sizeof(float));
	}

	return Model(std::move(texture), std::move(vertices), std::move(indices));
}


//#include <fstream>
//#include <iostream>
//#include "Model.h"
//#include "SDLRenderer.h"
//#include "ResourceManager.h"
//#include "SDLTexture.h"
//
//Model::Model(const std::string& filePath) :
//	m_modelFilePath(filePath)
//{
//	std::ifstream f(filePath);
//	if (!f.is_open())
//	{
//		std::cout << "This doesnt exist" << std::endl;
//		CreateModel();
//	}
//	else
//	{
//		std::cout << filePath << " exists" << std::endl;
//		LoadModel(f);
//	}
//}
//
//
////READ
//void Model::LoadModel(std::ifstream& f)
//{
//	nlohmann::json model;
//	f >> model;
//
//	if (model.contains("texture")) 
//	{
//		m_textureFilePath = model["texture"];
//		m_texture = ResourceManager::Instance().GetTexture(m_textureFilePath);
//	}
//	
//	if (model.contains("indices")) 
//	{
//		m_indices = model["indices"].get<std::vector<int>>();
//	}
//
//	if (model.contains("vertices")) 
//	{
//		nlohmann::json vertices = model["vertices"];
//		m_vertices.resize(vertices.size());
//
//		for (int i = 0; i < vertices.size(); ++i)
//		{
//			nlohmann::json position = vertices[i]["position"];
//			nlohmann::json color = vertices[i]["color"];
//			nlohmann::json uv = vertices[i]["uv"];
//
//			m_vertices[i].position =
//			{
//				position[0].get<float>(),
//				position[1].get<float>()
//			};
//
//			m_vertices[i].color =
//			{
//				color[0].get<Uint8>(),
//				color[1].get<Uint8>(),
//				color[2].get<Uint8>(),
//				color[3].get<Uint8>()
//			};
//
//			m_vertices[i].tex_coord =
//			{
//				uv[0].get<float>(),
//				uv[1].get<float>()
//			};
//		}
//	}
//}
//
////WRITE
//void Model::SaveModel()
//{
//	std::ofstream fw(m_modelFilePath);
//	nlohmann::json model;
//
//	model["texture"] = m_textureFilePath;
//	std::cout << m_textureFilePath << std::endl;
//
//	model["indices"] = m_indices;
//
//	for (int i = 0; i < m_indices.size(); ++i)
//	{
//		std::cout << model["indices"][i] << std::endl;
//	}
//
//	std::vector<std::unordered_map<std::string, std::vector<float>>> vertices;
//	vertices.resize(m_vertices.size());
//
//	model["vertices"] = vertices;
//
//	for (int i = 0; i < model["vertices"].size(); ++i)
//	{
//		model["vertices"][i]["position"] =
//		{
//			m_vertices[i].position.x,
//			m_vertices[i].position.y
//		};
//
//		model["vertices"][i]["uv"] =
//		{
//			m_vertices[i].tex_coord.x,
//			m_vertices[i].tex_coord.y
//		};
//
//		model["vertices"][i]["color"] =
//		{
//			m_vertices[i].color.r,
//			m_vertices[i].color.g,
//			m_vertices[i].color.b,
//			m_vertices[i].color.a
//		};
//	};
//
//	fw << model.dump(4);
//	fw.close();
//}
//
//void Model::CreateModel() 
//{
//	std::cout << "THIS WAS CALLED" << std::endl;
//}
//
//void Model::Draw(SDLRenderer& renderer)
//{
//	SDL_RenderGeometry(renderer.get(), m_texture->get(), m_vertices.data(), m_vertices.size(), m_indices.data(), m_indices.size());
//}
//
//
//// Set things to check whether the file has changed when saved....
//
//
//void Model::SetModel(const std::string& filePath)
//{
//	m_modelFilePath = filePath;
//}
//
//void Model::SetTexture(const std::string& filePath) 
//{
//	m_textureFilePath = filePath;
//}
//
//void Model::SetIndices(std::vector<int> indices) 
//{
//	m_indices = indices;
//}
//
//void Model::SetColor(int index, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
//{
//	m_vertices[index].color = { r, g, b, a };
//}
//
//void Model::SetPostion(int index, float x, float y)
//{
//	m_vertices[index].position = { x, y};
//}
//
//void Model::SetUV(int index, float x, float y)
//{
//	m_vertices[index].tex_coord = { x, y };
//}