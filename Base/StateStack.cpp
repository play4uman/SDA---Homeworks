#include "StateStack.h"
#include "GameState.h"
#include <iostream>


StateStack::StateStack():m_nextState(nullptr),m_requestPopState(0)
{
    m_gameStates.reserve(2);
}


StateStack::~StateStack()
{
    if(m_nextState)
        delete m_nextState;
}

void StateStack::pushState(GameState* newState)
{
	m_nextState = newState;
}

void StateStack::popState()
{
    if(m_requestPopState < (int)m_gameStates.size())
        ++m_requestPopState;
}

void StateStack::forcePopState()
{
	if (!m_gameStates.empty())
	{
        GameState* backState = m_gameStates.back();
		backState->onExit();
    	m_gameStates.pop_back();
        delete backState;
	}
}

void StateStack::changeState(GameState* newState)
{
    popState();
    m_nextState = newState;
}

void StateStack::update(float deltaTIme)
{
    if(m_requestPopState > 0)
    {
        for(int i = 0; i < m_requestPopState; ++i)
        {
            forcePopState();
        }
        m_requestPopState = 0;
    }
    
    if(m_nextState)
    {
        m_gameStates.push_back(m_nextState);
        m_gameStates.back()->onEnter();
        m_nextState = nullptr;
    }

	if (!m_gameStates.empty())
	{
		m_gameStates.back()->update(deltaTIme);
	}
}

void StateStack::render()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->render();
	}
}