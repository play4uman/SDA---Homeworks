#pragma once
#include "Player.h"
#include "../Base/InputHandler.h"
#include "../Base/VisualComponent.h"
#include "PlayState.h"
#include "../Base/vec2.h"
#include "Game.h"
#include "Projectile.h"
#include <utility>

#include <iostream>


RTTI_REGISTER(Player)

void Player::update(float deltaTime)
{
	//std::cout << "Updating Player" << std::endl;
    VisualComponent* visualComponent = getComponent<VisualComponent>();
    if(!visualComponent)
        return;

    m_speed.x = ((float)InputHandler::Instance()->isKeyPressed(SDL_SCANCODE_RIGHT) - (float)InputHandler::Instance()->isKeyPressed(SDL_SCANCODE_LEFT));

	//std::cout << m_speed.x << std::endl;

    m_speed.y = ((float)InputHandler::Instance()->isKeyPressed(SDL_SCANCODE_DOWN) - (float)InputHandler::Instance()->isKeyPressed(SDL_SCANCODE_UP));

    if (!m_speed.equalWithEpsilon(vec2Zero))
        m_speed = m_speed * getMaxVelocity() / m_speed.getLength();

    if (!canMove(m_speed * deltaTime))
        m_speed = vec2Zero;

    if(InputHandler::Instance()->isMouseButtonJustPressed(MouseButton_LEFT))
    {
        vec2 targetPos = InputHandler::Instance()->getMousePosition();
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

    if (!visualComponent->getRenderSpriteByName("Shoot")->isPlaying())
    {
        if (!m_speed.equalWithEpsilon(vec2Zero))
        {
            visualComponent->setCurrentRenderSpriteByName("Run");
            visualComponent->getCurrentSpritePlaying()->play();
        }
        else
            visualComponent->setCurrentRenderSpriteByName("Idle");
    }

    Living::update(deltaTime);
}