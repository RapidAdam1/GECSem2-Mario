#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include "GameScreenManager.h"

#include <iostream>
using namespace std;

//GlobalVariables
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;

//FunctionPrototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();


int main(int argc, char* args[])
{
	//check if sdl was setup correctly
	if (InitSDL())
	{
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
		g_old_time = SDL_GetTicks();

		bool quit = false;
		while (!quit)
		{
			Render();
			quit = Update();
		}
	}

	CloseSDL();
	return 0;

}

bool InitSDL()
{
	//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//setup passed so create window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		//did the window get created?
		if (g_window == nullptr)
		{
			//window failed
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		//Attach Renderer To Window
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_renderer != nullptr) 
		{
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags)) 
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError() << endl;
				return false;
			}
		}
		else 
		{
			cout << "SDL_Renderer Could not initialise. Error: " << SDL_GetError() << endl;
			return false;
		}
	}

	return true;
}

void CloseSDL()
{
	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//FreeTexture();
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;


	delete game_screen_manager;
	game_screen_manager = nullptr;
	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

}

bool Update() 
{
	Uint32 new_time = SDL_GetTicks();
	//Event Handler
	SDL_Event e;

	//Get Events
	SDL_PollEvent(&e);

	//Event Handle
	switch (e.type) 
	{
	case SDL_QUIT:
		return true;
		break;
		
	}
	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;
	return false;
}

void Render()
{
	//Clear Screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	game_screen_manager->Render();
	//Update Screen
	SDL_RenderPresent(g_renderer);
}
