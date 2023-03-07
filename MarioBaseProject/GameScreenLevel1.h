#pragma once
#include "GameScreen.h"
#include "Commons.h"
class Texture2D;
class Character;

class GameScreenLevel1 : GameScreen
{
public:
	   GameScreenLevel1(SDL_Renderer* renderer);
	   ~GameScreenLevel1();

	   void Render() override;
	   void Update(float deltaTime, SDL_Event e) override;
private: 
	Texture2D* m_background_texture;
	Character* my_character;
	bool SetupLevel();
};

