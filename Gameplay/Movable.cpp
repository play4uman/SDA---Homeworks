#include "Movable.h"
#include "../Base/Util.h"
#include "../Base/CollisionComponent.h"
#include "PlayState.h"
#include "Player.h"
RTTI_REGISTER(Movable)

float Movable::angleFromSpeed(const vec2& speed)
{
    return atan2f(speed.y, speed.x) + M_PI / 2;
}

bool Movable::isBlocker(BaseObject* obj)
{
    return rtti_cast<Movable>(obj) || !rtti_cast<GameplayObject>(obj);
}

bool Movable::canMove(const vec2& displacement) 
{
    if (displacement.equalWithEpsilon(vec2Zero))
        return true;
    CollisionComponent* collisionComp = getComponent<CollisionComponent>();
    if (!collisionComp)
        return true;
    float angle = angleFromSpeed(displacement);
    Transform2 trans;
    trans.set(getPosition() + displacement, angle, getScale());
    BaseShape* tempShape = collisionComp->getOriginalShape()->transform(trans);
    std::vector<BaseObject*> ignore;
    ignore.push_back(this);
    std::vector<BaseObject*> collisions;
    getGameState<GameState>()->testCollision(*tempShape, &collisions, &ignore);
    delete tempShape;
    for (BaseObject *obj: collisions)
        if (isBlocker(obj))
            return false;
    return true;
}

void Movable::init()
{
    GameplayObject::init();
    updateAngle();
}

void Movable::updateAngle()
{
    if (!m_speed.equalWithEpsilon(vec2Zero))
        setAngle(angleFromSpeed(m_speed));
}

void Movable::update(float deltaTime)
{
    setPosition(getPosition() + m_speed * deltaTime);
    updateAngle();
    GameplayObject::update(deltaTime);
}

void Movable::serialize(rapidjson::Value& value)
{
    m_maxVelocity = (float)value["MaxVelocity"].GetDouble();
    GameplayObject::serialize(value);
}

Player* Movable::getPlayer()const
{
	std::vector<BaseObject*>& objs = getGameState<PlayState>()->getGameObjects();
	for (BaseObject* search : objs)
	{
		Player* founded = rtti_cast<Player>(search);
		if (founded)
		{
			return founded;
		}
	}
	return nullptr;
}