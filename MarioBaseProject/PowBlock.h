#pragma once
#ifndef _POWBLOCK_H
#define _POWBLOCK_H
#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include "Constants.h"
#include "String"

class Texture2D;
class LevelMap;
class SDL_Renderer;

class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map);
	~PowBlock();
	void Render();
	void TakeHit();
	inline Rect2D GetCollisionBox() 
	{
		return Rect2D(m_position.x,m_position.y,m_single_sprite_h, m_single_sprite_w);
	}
	inline bool IsAvailable() { return m_num_hits_left > 0; }

private:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	LevelMap* m_level_map;

	float m_single_sprite_w;
	float m_single_sprite_h;
	int m_num_hits_left;

};

#endif // !_POWBLOCK_H