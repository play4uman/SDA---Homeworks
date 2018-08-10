#include "Projectile.h"
#include "../Base/CollisionComponent.h"
#include "Living.h"
#include <iostream>

RTTI_REGISTER(Projectile)

bool Projectile::isBlocker(BaseObject* obj)
{
    return !rtti_cast<GameplayObject>(obj);
}

void Projectile::update(float deltaTime)
{
    std::vector<BaseObject*>& collisions = getComponent<CollisionComponent>()->getCollisions();
    for (BaseObject *obj: collisions)
    {
        if (Living *living = rtti_cast<Living>(obj))
        {
            living->setHealth(living->getHealth() - m_damage);
            getGameState<GameState>()->removeObject(this);
            return;
        }
        if (isBlocker(obj))
        {
            getGameState<GameState>()->removeObject(this);
            return;
        }
    }
    Movable::update(deltaTime);
}

void Projectile::serialize(rapidjson::Value& value)
{
    m_damage = (float)value["Damage"].GetDouble();
    Movable::serialize(value);
}
