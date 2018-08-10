#include "PlayState.h"
#include "Game.h"
#include "Player.h"
#include "NormalArcher.h"
#include "MagicArcher.h"
#include "SpreeArcher.h"
#include "../Base/TextureManager.h"
#include "../Base/InputHandler.h"
#include "../Base/StateStack.h"
#include "..\UI\PauseState.h"
#include "..\Constants.h"
#include "NormalArcher.h"
#include <random>
#include <time.h>
#include "PowerUp.h"

#include "Column.h"
#include <iostream>


RTTI_REGISTER(PlayState)

PlayState::PlayState(SDL_Renderer* renderer) :GameState(renderer), m_levelData(this), numUpdate(0)
{
    m_levelData.load(InitalLevelPath);
}


PlayState::~PlayState()
{
}


int PlayState::getEnemyCount() const 
{
	int count = 0;

	for (BaseObject* obj : m_gameObjects)
	{
		NormalArcher* foundNA = rtti_cast<NormalArcher>(obj);
		if (foundNA)
			count++;
		SpreeArcher* foundSA = rtti_cast<SpreeArcher>(obj);
		if (foundSA)
			count++;
		MagicArcher* foundMA = rtti_cast<MagicArcher>(obj);
		if (foundMA)
			count++;
	}
	return count;
}

int PlayState::dropType()
{
	srand(time(NULL));
	int result = rand() % 100 + 1;
	if (result > 50)
		return 0;
	if (result <= 50 && result > 1) 
	{
		result++;
		if (result % 2)
			return 1;
		else
			return 2;
	}
	if (result == 1)
		return 3;
}

void PlayState::spawnClassPowerUp(vec2& position)
{
	int type = dropType();
	PowerUp* powerUp;
	switch (type)
	{
	case 1:
		powerUp = (PowerUp*)getLevelData().createBaseObjectFromTemplateID("Health", position.x, position.y);
		addObject(powerUp);
		powerUp->setTypeName("Health");
		break;
	case 2: 
		powerUp = (PowerUp*)getLevelData().createBaseObjectFromTemplateID("DamageBonus", position.x, position.y);
		addObject(powerUp);
		powerUp->setTypeName("DamageBonus");
		break;
	case 3:
		powerUp = (PowerUp*)getLevelData().createBaseObjectFromTemplateID("RingOfPower", position.x, position.y);
		addObject(powerUp);
		powerUp->setTypeName("RingOfPower");
		break;
	}
}

void PlayState::signalDeadEnemy(vec2& position)
{
	countEnemies--;
	spawnClassPowerUp(position);
}

template<typename T>
void PlayState::spawnClassEnemy()
{
	srand(time(NULL));
	vec2 initPoint(rand() % 872 + 76, rand() % 628 + 76);
	while (!isPointViable(initPoint))
	{
		initPoint.x = (rand() % 872) + 76;
		initPoint.y = (rand() % 628) + 76;
	}
	T* enemy = (T*)getLevelData().createBaseObjectFromTemplateID(enemy->getClassName(), initPoint.x, initPoint.y);
	addObject(enemy);
	countEnemies++;
}

bool PlayState::isPointViable(vec2& target) const
{
	for (BaseObject* obj : m_gameObjects)
	{
		std::vector<vec2> targetSquare = vec2::getEdgesOfSquare(target, 12);
		if (rtti_cast<GameplayObject>(obj) || rtti_cast<Column>(obj))
		{
			if (rtti_cast<GameplayObject>(obj))
			{
				std::vector<vec2> testedSquare = vec2::getEdgesOfSquare(obj->getPosition(), 12);
				if (vec2::doSquaresIntersect(targetSquare, testedSquare))
					return false;
			}
			if (rtti_cast<Column>(obj))
			{
				vec2 realCentre(obj->getPosition().x + 64, obj->getPosition().y + 64);
				std::vector<vec2> testedSquare = vec2::getEdgesOfSquare(realCentre, 32);
				if (vec2::doSquaresIntersect(targetSquare, testedSquare))
					return false;
			}
		}
	}
	return true;
}

void PlayState::spawnEnemy()
{
	if (countEnemies + 1 <= 5 && numUpdate % 200 == 0)
	{
		srand(time(NULL));
		int typeEnemy = rand() % 3;
		switch (typeEnemy) 
		{
		case 0: spawnClassEnemy<NormalArcher>();
			break;
		case 1: spawnClassEnemy<SpreeArcher>();
			break;
		case 2: spawnClassEnemy<MagicArcher>();
			break;
		}
	}
}


void PlayState::update(float deltaTime)
{
	spawnEnemy();
	if (numUpdate == 1)
	{
		countEnemies = getEnemyCount();
	}
	std::cout << countEnemies << std::endl;

	numUpdate++;

	GameState::update(deltaTime);
	if (InputHandler::Instance()->isKeyJustReleased(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance()->getStateMachine().pushState(new PauseState(m_renderer));
	}

}

void PlayState::onEnter()
{

    unsigned int widthInTiles = m_levelData.getWidthInTiles();
    unsigned int heightInTiles = m_levelData.getHeightInTiles();
    unsigned int tileWidth = m_levelData.getTileWidth();
    unsigned int tileHeight = m_levelData.getTileHeight();

    for(unsigned int i = 0; i < widthInTiles; ++i)
    {
        for(unsigned int k = 0; k < heightInTiles; ++k)
        {
            TileInfo& tileInfo = m_levelData.getTileInfo(i, k);
            addObject(m_levelData.createBaseObjectFromTemplateIndex(tileInfo.TemplateIndex, i * tileWidth, k * tileHeight));
        }
    }

    for(GameObjectInfo& gameObject : m_levelData.getGameObjects())
    {
        addObject(m_levelData.createBaseObjectFromTemplateIndex(gameObject.TemplateIndex, gameObject.X, gameObject.Y));
    }
}

void PlayState::onExit()
{
	for (int i = 0; i < (int)m_gameObjects.size(); i++)
	{
		BaseObject* gameObject = m_gameObjects[i];
        m_gameObjects[i]->uninit();
        delete gameObject;
	}

	m_gameObjects.clear();
}
