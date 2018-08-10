#pragma once
#include "SpreeArcher.h"
#include "../Base/InputHandler.h"
#include "../Base/VisualComponent.h"
#include "Game.h"
#include "Movable.h"
#include <utility>
#include <iostream>
#include "Player.h"

RTTI_REGISTER(SpreeArcher)

void SpreeArcher::update(float deltaTime)
{
	//std::cout << "Updating " << getClassName() << std::endl;
	VisualComponent* visualComponent = getComponent<VisualComponent>();
	if (getPlayer() && shotCounter == 0)
	{
		vec2 targetPos = getPlayer()->getPosition();
		vec2 pos = getPosition();
		vec2 directions[3];
		directions[0] = targetPos - pos; directions[0] = directions[0].normalize();
		directions[1] = targetPos - pos; directions[1] = directions[1].normalize().rotate(0.5235);
		directions[2] = targetPos - pos; directions[2] = directions[2].normalize().rotate(-0.5235);

		for (int i = 0; i < 3; i++)
		{
			vec2 initialPos = pos + directions[i] * 50.0f;
			Projectile* arrow = (Projectile *)getGameState<PlayState>()->getLevelData().createBaseObjectFromTemplateID("PlayerArrow", initialPos.x, initialPos.y);
			arrow->setSpeed(directions[i] * arrow->getMaxVelocity());
			getGameState<GameState>()->addObject(arrow);

			visualComponent->setCurrentRenderSpriteByName("Shoot");
			visualComponent->getCurrentSpritePlaying()->play();
		}
	}
	shotCounter++;
	if (shotCounter == 90)
		shotCounter = 0;
    Living::update(deltaTime);
}