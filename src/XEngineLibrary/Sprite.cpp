#include <Sprite.h>
#include <SDLRenderer.h>
#include <SDLTexture.h>
#include <Transform.h>

Sprite::Sprite(std::shared_ptr<const SDLTexture> texture) :
	Sprite(std::move(texture), texture->GetRect())
{
}

Sprite::Sprite(std::shared_ptr<const SDLTexture> texture, const SDL_Rect& rect) :
	m_texture(std::move(texture)),
	m_rect(rect),
	m_origin(0.f, 0.f),
	m_width(rect.w),
	m_height(rect.h)
{
}

void Sprite::Draw(SDLRenderer& renderer, const Transform& cameraTransform, const Transform& transform)
{
	SDL_Rect texRect = m_texture->GetRect();

	Vector2f originPos = m_origin * Vector2f(m_width, m_height);

	// Calcul de la position des quatre coins du sprite dans le rep�re du Transform
	// c'est � cette �tape que la translation, rotation et scale du Transform vont s'appliquer
	Vector2f topLeftCorner = transform.TransformPoint(Vector2f(0.f, 0.f) - originPos);
	Vector2f topRightCorner = transform.TransformPoint(Vector2f(static_cast<float>(m_width), 0.f) - originPos);
	Vector2f bottomLeftCorner = transform.TransformPoint(Vector2f(0.f, static_cast<float>(m_height)) - originPos);
	Vector2f bottomRightCorner = transform.TransformPoint(Vector2f(static_cast<float>(m_width), static_cast<float>(m_height)) - originPos);

	// Application de la cam�ra (transformation inverse)
	topLeftCorner = cameraTransform.TransformInversePoint(topLeftCorner);
	topRightCorner = cameraTransform.TransformInversePoint(topRightCorner);
	bottomLeftCorner = cameraTransform.TransformInversePoint(bottomLeftCorner);
	bottomRightCorner = cameraTransform.TransformInversePoint(bottomRightCorner);

	// La division �tant g�n�ralement plus co�teuse que la multiplication, quand on sait qu'on va faire plusieurs divisons par
	// les m�mes valeurs on peut calculer l'inverse de la valeur pour la multiplier par la suite (X * (1 / Y) == X / Y)
	float invWidth = 1.f / texRect.w;
	float invHeight = 1.f / texRect.h;

	// On sp�cifie maintenant nos vertices (sommets), compos�s � chaque fois d'une couleur, position et de coordonn�es de texture
	// Ceux-ci vont servir � sp�cifier nos triangles. Chaque triangle est compos� de trois sommets qui d�finissent les valeurs aux extr�mit�s,
	// la carte graphique allant ensuite g�n�rer les valeurs interm�diaires (par interpolation) pour les pixels composant le triangle.
	SDL_Vertex vertices[4];
	vertices[0].color = SDL_Color{ 255, 255, 255, 255 };
	vertices[0].position = SDL_FPoint{ topLeftCorner.x, topLeftCorner.y };
	vertices[0].tex_coord = SDL_FPoint{ m_rect.x * invWidth, m_rect.y * invHeight };

	vertices[1].color = SDL_Color{ 255, 255, 255, 255 };
	vertices[1].position = SDL_FPoint{ topRightCorner.x, topRightCorner.y };
	vertices[1].tex_coord = SDL_FPoint{ (m_rect.x + m_rect.w) * invWidth, m_rect.y * invHeight };

	vertices[2].color = SDL_Color{ 255, 255, 255, 255 };
	vertices[2].position = SDL_FPoint{ bottomLeftCorner.x, bottomLeftCorner.y };
	vertices[2].tex_coord = SDL_FPoint{ m_rect.x * invWidth, (m_rect.y + m_rect.h) * invHeight };

	vertices[3].color = SDL_Color{ 255, 255, 255, 255 };
	vertices[3].position = SDL_FPoint{ bottomRightCorner.x, bottomRightCorner.y };
	vertices[3].tex_coord = SDL_FPoint{ (m_rect.x + m_rect.w) * invWidth, (m_rect.y + m_rect.h) * invHeight };

	// On pourrait donner la liste des sommets � la SDL et lui dire de rendre des triangles (� condition d'avoir N * 3 sommets pour N triangles)
	// n�anmoins, �tant donn� que nous affichons deux triangles coll�s et partageant les m�mes donn�es, on peut se permettre ici de r�utiliser
	// les vertices, avec les indices.

	// Lorsqu'on a des indices lors du rendu, alors ceux-ci d�finissent les num�ros des vertices qui vont composer nos triangles.
	// ceci permet de r�utiliser les vertices, permettant de consommer moins de m�moire et d'avoir un rendu plus rapide

	// Six indices pour deux triangles, avec r�utilisation des sommets [1] et [2]
	int indices[6] = { 0, 1, 2, 2, 1, 3 };

	SDL_RenderGeometry(renderer.get(),
		(m_texture) ? m_texture->get() : nullptr,
		vertices, 4,
		indices, 6);
}

int Sprite::GetHeight() const
{
	return m_height;
}

const Vector2f& Sprite::GetOrigin() const
{
	return m_origin;
}

int Sprite::GetWidth() const
{
	return m_width;
}

void Sprite::Resize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Sprite::SetOrigin(const Vector2f& origin)
{
	m_origin = origin;
}

void Sprite::SetRect(SDL_Rect rect)
{
	m_rect = rect;
}