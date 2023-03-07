#include "Texture2D.h"
#include <SDL_image.h>

//Constructor
Texture2D::Texture2D(SDL_Renderer* renderer) 
{
	m_renderer = renderer;

}
//Destructor
Texture2D::~Texture2D() 
{
	Free();
	m_renderer = nullptr;
}

bool Texture2D::LoadFromFile(std::string path) 
{
	//Remove Memory of Previous Texture
	Free();

	//Load Image
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0xFF, 0xFF));
		m_texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);
		if (m_texture == nullptr)
		{
			cout << "Unable to Create Texture From Surface. Error:" << SDL_GetError() << endl;
		}
		else 
		{
			m_width = p_surface->w;
			m_height = p_surface->h;
		}
		SDL_FreeSurface(p_surface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error:" << IMG_GetError() << endl;
	}
	return m_texture != nullptr;
}

void Texture2D::Render(Vector2D new_Position, SDL_RendererFlip flip, double angle) 
{
	SDL_Rect renderLocation = { new_Position.x,new_Position.y,m_width,m_height};
	//Render To Screen
	SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &renderLocation, 0, nullptr, flip);
}

void Texture2D::Free() 
{
	if (m_texture != nullptr) {
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_width = 0.0f;
		m_height = 0.0f;
	}
}