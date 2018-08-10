#pragma once
#include "MagicArrow.h"
#include "../Base/InputHandler.h"
#include "../Base/VisualComponent.h"
#include "Game.h"
#include "Player.h"
#include <utility>
#include <iostream>

RTTI_REGISTER(MagicArrow)

MagicArrow::MagicArrow() : Projectile() {
	std::cout << "Created " << getClassName() << std::endl;
}

void MagicArrow::update(float deltaTime)
{
	std::cout << "Updating " << getClassName() << std::endl;
	Player* player = getPlayer();
	setSpeed(player->getPosition());
	std::cout << m_speed.x << " " << m_speed.y << std::endl;
	Projectile::update(deltaTime);
}
