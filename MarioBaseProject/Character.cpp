#include "Character.h"
#include "Texture2D.h"


Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position)
{
	m_facing_direction = FACING_RIGHT;
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		cout << "Failed to Load Texture" << endl;
	}
}

Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Render()
{
	if(m_facing_direction == FACING_RIGHT){ m_texture->Render(m_position, SDL_FLIP_NONE); }
	else { m_texture->Render(m_position, SDL_FLIP_HORIZONTAL); }
}

void Character::Update(float deltaTime, SDL_Event e)
{

	if (m_moving_left) {MoveLeft(deltaTime);}
	else if (m_moving_right) { MoveRight(deltaTime); }

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_RIGHT:
			m_moving_right = true;
			break;
		case SDLK_LEFT:
			m_moving_left = true;
			break;
		}
	break;
	}
	SetPosition(GetPosition());
}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Character::GetPosition()
{
	return m_position;
}

void Character::MoveLeft(float deltaTime)
{
	m_facing_direction = FACING_LEFT;
	m_position.x -= 1;
}

void Character::MoveRight(float deltaTime)
{
	m_facing_direction = FACING_RIGHT;
	m_position.x += 1;
}