#include "GameScreenManager.h"
#include "GameScreen.h"
#include "ScreenMainMenu.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;
	m_CurrentScreen = nullptr;
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager() 
{
	m_renderer = nullptr;
	delete m_CurrentScreen;
	m_CurrentScreen = nullptr;
}

void GameScreenManager::Render()
{
	m_CurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	m_CurrentScreen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	if (m_CurrentScreen != nullptr) 
	{
		delete m_CurrentScreen;
	}

	switch (new_screen)
	{
	case SCREEN_INTRO:
		break;
	case SCREEN_MENU:
		m_CurrentScreen = (GameScreen*)new ScreenMainMenu(m_renderer,this);
		break;
	case SCREEN_LEVEL1:
		m_CurrentScreen = (GameScreen*)new GameScreenLevel1(m_renderer);
		break;
	case SCREEN_LEVEL2:
		m_CurrentScreen = (GameScreen*)new GameScreenLevel2(m_renderer);
		break;
	case SCREEN_GAMEOVER:
		break;
	case SCREEN_HIGHSCORES:
		break;
	default:
		break;
	}
}
