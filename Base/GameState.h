#pragma once

#include <vector>
#define HAVE_M_PI
#include <SDL.h>
#include "BaseObject.h"
#include <algorithm>
#include <functional>
#include "Collision.h"

struct SDL_Renderer;
class GameState
{
    RTTI_ABSTRACT_BASE(GameState)
    GameState& operator=(const GameState&);
    GameState(const GameState&);
public:
	
	virtual void update(float deltaTime);

	virtual void render();

	virtual void onEnter() = 0;
	virtual void onExit() = 0;
	
    GameState(): m_updateId(0)
    {
    }

	virtual ~GameState() 
    {
        for(uint32_t i = 0; i< m_gameObjects.size(); ++i)
        {
            delete m_gameObjects[i];
        }
        m_gameObjects.clear();
    };

    typedef std::function<void()> Callback;

    void addCallback(Callback cb) { m_callbacks.push_back(cb); }
    void callCallbacks()
    {
        for (auto cb: m_callbacks)
            cb();
        m_callbacks.clear();
    }

    void addObject(BaseObject* object) 
    {
        addCallback([=] {
            m_gameObjects.push_back(object);
            object->init();
        });
    }

    void removeObject(BaseObject* object, bool doDelete = true) 
    {
        addCallback([=] {
            m_gameObjects.erase(std::remove(m_gameObjects.begin(), m_gameObjects.end(), object), m_gameObjects.end());
            object->uninit();
            if (doDelete)
                delete object;
        });
    }

    std::vector<BaseObject*>& getGameObjects() { return m_gameObjects; }
    size_t getUpdateId() const { return m_updateId; }

    bool testCollision(BaseShape& shape, std::vector<BaseObject*>* collisions = nullptr, const std::vector<BaseObject*>* objToIgnore = nullptr);

    void drawLines(const SDL_Point* points, int count, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

protected:
	GameState(SDL_Renderer* renderer): m_renderer(renderer) {};

    SDL_Renderer* m_renderer;
    std::vector<BaseObject*> m_gameObjects;

    std::vector<Callback> m_callbacks;
    size_t m_updateId;
};

