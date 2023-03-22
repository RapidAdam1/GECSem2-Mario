#include "PowBlock.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include "Constants.h"
#include "String"

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map)
{
	std::string imagePath = "Images/PowBlock.png";
	m_texture = new Texture2D(renderer);
	if (!m_texture->LoadFromFile(imagePath.c_str()))
	{
		std::cout << "Failed to load texture." << std::endl;
		return;
	}
	m_level_map = map;
	m_single_sprite_w = m_texture->GetWidth() / 3; 
	//there are three images in this sheet in a row
		m_single_sprite_h = m_texture->GetHeight();
	m_num_hits_left = 3;
	m_position = Vector2D((SCREEN_WIDTH * 0.5f) - m_single_sprite_w * 0.5f, 260);
}

PowBlock::~PowBlock()
{
}

void PowBlock::Render()
{
}

void PowBlock::TakeHit()
{
}

inline Rect2D PowBlock::GetCollisionBox()
{
}
