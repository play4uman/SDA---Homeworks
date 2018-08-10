#pragma once
#include "../Base/GameState.h"
#include "LevelData.h"
#include <vector>

class Player;
class PlayState: public GameState
{
	RTTI_ABSTRACT(PlayState, GameState)
public:
	PlayState(SDL_Renderer* renderer);
	~PlayState();

	virtual void update(float deltaTime);
	virtual void onEnter();
	virtual void onExit();

    const Player* getPlayer() {return m_player;}
    LevelData& getLevelData() {return m_levelData;}
	
	int getEnemyCount() const;
	void signalDeadEnemy(vec2& position);
	void spawnEnemy();

	template<typename T>
	void spawnClassEnemy();

	void spawnClassPowerUp(vec2& position);
	int dropType();

	bool isPointViable(vec2& target)const;
protected:
    LevelData m_levelData;
    Player* m_player;

	int countEnemies;
	int numUpdate;
};

