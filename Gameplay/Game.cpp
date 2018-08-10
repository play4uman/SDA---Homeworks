#include "Game.h"

#include "..\Constants.h"

#include "../Base/BaseObject.h"
#include "../Base/StateStack.h"
#include "../Base/InputHandler.h"
#include "../Base/TextureManager.h"
#include "../Base/Font.h"
#include "..\UI\MainMenu.h"
#include "GameFactory.h"

#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Player.h"
#include "PlayState.h"

static Game* s_pInstance = nullptr;

Game::Game():
    m_window(nullptr),
    m_renderer(nullptr),
    m_running(false)
{
}

Game::~Game()
{
    InputHandler::Destroy();
    TextureManager::Destroy();
    FontManager::destroy();

    SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
	TTF_Quit();
}

bool Game::init(const char* title, int x_pos, int y_pos, int width, int height, int windowFlags, int renderFlags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() == 0)
	{
		m_window = SDL_CreateWindow(title, x_pos, y_pos, width, height, windowFlags);

		if (m_window != nullptr)
		{
			m_renderer = SDL_CreateRenderer(m_window, -1, renderFlags);
			
			SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
			
			if (m_renderer != nullptr)
			{
				SDL_RenderClear(m_renderer);
								
				m_running = true;
	
                GameFactory::initialize();
                TextureManager::Instance()->setRenderer(m_renderer);

				m_gameStateStack.changeState(new MainMenu(m_renderer));

				m_gameHeight = height;
				m_gameWidth = width;
				
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return false;
}

void Game::render()
{
	SDL_RenderClear(m_renderer);
	m_gameStateStack.render();
	SDL_RenderPresent(m_renderer);
}

void Game::uninit()
{
	InputHandler::Instance()->uninit();
}

void Game::Destroy()
{
    delete s_pInstance;
}

void Game::update(float deltaTime)
{
    InputHandler::Instance()->update(deltaTime);

    if(InputHandler::Instance()->quitRequested())
    {
        quit();
    }

	m_gameStateStack.update(deltaTime);
}


Game* Game::Instance()
{
	if (s_pInstance == 0)
	{
		s_pInstance = new Game();
	}

	return s_pInstance;
}

void Game::quit()
{
	m_running = false;
}