#pragma once
#include "MagicArcher.h"
#include "../Base/InputHandler.h"
#include "../Base/VisualComponent.h"
#include "Game.h"
#include "MagicArrow.h"
#include "Projectile.h"
#include "Player.h"
#include <utility>
#include <iostream>

RTTI_REGISTER(MagicArcher)

void MagicArcher::update(float deltaTime)
{
	VisualComponent* visualComponent = getComponent<VisualComponent>();
	if (getPlayer() && shotCounter == 0)
	{
		vec2 targetPos = getPlayer()->getPosition();
		vec2 pos = getPosition();
		vec2 direction = targetPos - pos;
		if (!direction.equalWithEpsilon(vec2Zero))
		{
			direction = direction.normalize();
			vec2 initialPos = pos + direction * 50.0f;
			MagicArrow* arrow = (MagicArrow *)getGameState<PlayState>()->getLevelData().createBaseObjectFromTemplateID("PlayerArrow", initialPos.x, initialPos.y);
			arrow->setSpeed(direction * arrow->getMaxVelocity());
			getGameState<GameState>()->addObject(arrow);

			visualComponent->setCurrentRenderSpriteByName("Shoot");
			visualComponent->getCurrentSpritePlaying()->play();
		}
	}
	shotCounter++;
	if (shotCounter == 70)
		shotCounter = 0;
    Living::update(deltaTime);
}