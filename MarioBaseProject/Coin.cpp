#include "Coin.h"

Coin::Coin(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
	m_audio = new AudioComponent();
	
}

Coin::~Coin()
{
	delete m_renderer;
	m_renderer = nullptr;
	delete m_texture;
	m_texture = nullptr;
	delete m_audio;
	m_audio = nullptr;
}

void Coin::FlipRightwayUp()
{
	if (m_facing_direction == FACING_LEFT)
	{
		m_facing_direction = FACING_RIGHT;
	}
	else { m_facing_direction = FACING_LEFT; }
	Jump();
}


void Coin::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE_SMALL;
		m_jumping = true;
		m_can_jump = false;
	}
}


void Coin::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f) 
	{
		m_frame_delay = ANIMATION_DELAY;
		m_current_frame++;
		if (m_current_frame > 2) 
		{
			m_current_frame = 0;
		}
	}



	//enemy is not injured so move
	if (m_facing_direction == FACING_LEFT)
	{
		m_moving_left = true;
		m_moving_right = false;
	}
	else if (m_facing_direction == FACING_RIGHT)
	{
		m_moving_right = true;
		m_moving_left = false;
	}
}

void Coin::Render()
{
	//variable to hold the left position of the sprite we want to draw
	int left = 0.0f;

	//get the portion of the sprite sheet you want to draw
	//							   {xPos, yPos, width of sprite, height of sprite}
	SDL_Rect portion_of_sprite = {m_single_sprite_w*m_current_frame,0,m_single_sprite_w, m_single_sprite_h };

	//determine where you want it drawn
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	//then draw it facing the correct direction
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}

}

void Coin::SetAlive(bool isAlive)
{
	m_alive = isAlive;
}

void Coin::CollectCoin()
{
	m_alive = false;
	m_audio->LoadAudioFromFile("Music/Coin.mp3", 0, 1);
	//if (m_audio != nullptr) { m_audio->PlayAudio(); }
}

void Coin::FlipDirection(FACING direction)
{
	m_facing_direction = direction;
}