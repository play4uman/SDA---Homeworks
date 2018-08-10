#pragma once
#define HAVE_M_PI
#include <SDL.h>
#include <vector>
#include "../Base/StateStack.h"
class Game
{
    Game& operator=(const Game&);
    Game(const Game&);

    Game();
	~Game();
public:

	bool init(const char* title, int x_pos, int y_pos, int width, int height, int windowFlags, int renderFlags);
	void quit();
	void render();
	void update(float deltaTime);
	void uninit();
	bool runing(){ return m_running; };
	StateStack& getStateMachine(){ return m_gameStateStack; };
	
	int getGameWidth() const { return m_gameWidth; };
	int getGameHeight() const{ return m_gameHeight; };

	static Game* Instance();
    static void Destroy();
	
private:
	int m_gameWidth;
	int m_gameHeight;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	StateStack m_gameStateStack;

	void SetBackgroundImage();

    bool m_running;
};
