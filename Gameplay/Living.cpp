#include "Living.h"
#include "PlayState.h"
#include "Player.h"

RTTI_REGISTER(Living)

void Living::serialize(rapidjson::Value& value)
{
    m_health = (float)value["Health"].GetDouble();
    Movable::serialize(value);
}

void Living::SpawnSplat(const vec2& position)
{
    PlayState *playState = getGameState<PlayState>();
    BaseObject *splat = playState->getLevelData().createBaseObjectFromTemplateID("BloodSplat", position.x, position.y);
    splat->setAngle(2 * M_PI * rand() / RAND_MAX);
    playState->addObject(splat);
}

void Living::Die()
{
    getGameState<GameState>()->removeObject(this);
	getGameState<PlayState>()->signalDeadEnemy(getPosition());
}

void Living::setHealth(float val) 
{
    if (val < m_health)
        SpawnSplat(getPosition());
    m_health = val; 
    if (m_health < 0.0f)
        Die();
}

