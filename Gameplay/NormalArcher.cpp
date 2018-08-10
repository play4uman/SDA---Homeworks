#pragma once
#include "NormalArcher.h"
#include "Player.h"
#include "../Base/VisualComponent.h"
#include <iostream>


RTTI_REGISTER(NormalArcher)

void NormalArcher::move(float deltaTime)
{
	setSpeed(getPlayer()->getPosition() - getPosition());
	setSpeed(m_speed * getMaxVelocity() / m_speed.getLength());

	if (!canMove(m_speed * deltaTime))
		m_speed = vec2Zero;
	if ((getPlayer()->getPosition() - getPosition()).getLength() <= maxRangeEnemyNormalArcher)
		m_speed = vec2Zero;
}

void NormalArcher::update(float deltaTime)
{
	move(deltaTime);

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
			Projectile* arrow = (Projectile *)getGameState<PlayState>()->getLevelData().createBaseObjectFromTemplateID("PlayerArrow", initialPos.x, initialPos.y);
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
