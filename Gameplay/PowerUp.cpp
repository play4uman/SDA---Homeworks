#include "PowerUp.h"
#include "../Base/CollisionComponent.h"
#include "Living.h"
#include "Player.h"

RTTI_REGISTER(PowerUp)

void PowerUp::update(float deltaTime)
{
	std::vector<BaseObject*>& collisions = getComponent<CollisionComponent>()->getCollisions();
	for (BaseObject *obj : collisions)
	{
		if (Player* player = rtti_cast<Player>(obj))
		{
			if (typeName == "Health")
			{
				player->setHealth(player->getHealth() + 10);
			}
			else if (typeName == "DamageBonus")
			{
				player->setMaxVelocity(player->getMaxVelocity() + 100);
			}
			else
			{
				exit(1);
			}
			
			getGameState<GameState>()->removeObject(this);
			return;
		}

	}

	GameplayObject::update(deltaTime);
}