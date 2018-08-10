#pragma once
#include <vector>

class GameState;
class StateStack
{
    StateStack& operator=(const StateStack&);
    StateStack(const StateStack&);
public:
	StateStack();
	~StateStack();

	void pushState(GameState* newState);
	void changeState(GameState* newState);
    void popAll() { m_requestPopState = m_gameStates.size();}
	void popState();
	void update(float deltTIme);
	void render();

private:
    void forcePopState();

	std::vector<GameState*> m_gameStates;
    GameState* m_nextState;
    int m_requestPopState;
};

