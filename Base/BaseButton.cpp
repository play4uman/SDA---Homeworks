#include "BaseButton.h"
#include "InputHandler.h"
#include "BaseObject.h"
#include "VisualComponent.h"

void BaseButton::init()
{
    m_visualComponent = getComponent<VisualComponent>();
    m_visualComponent->getSprite("Idle")->play();
}

void BaseButton::update(float deltaTime)
{
    if(!m_visualComponent)
        return;

    m_prevButtonState = m_currButtonState;

    vec2 mousePos = InputHandler::Instance()->getMousePosition();

    bool mouseIsOverTheButton = hitTest(mousePos);

    m_currButtonState = IDLE;

    if (InputHandler::Instance()->isMouseButtonPressed(MouseButton_LEFT) && mouseIsOverTheButton)
    {
        m_currButtonState = PRESSED;
    }
    else if(m_prevButtonState == FOCUSED && InputHandler::Instance()->isKeyJustPressed(SDL_Scancode::SDL_SCANCODE_RETURN))
    {
        m_currButtonState = PRESSED;
    }
    else if(mouseIsOverTheButton)
    {
        m_currButtonState = FOCUSED;
    }

    m_visualComponent->setCurrentRenderSpriteIndex(m_currButtonState);
}

bool BaseButton::hitTest(const vec2& position)
{
    if(m_visualComponent)
    {
        float angleInRad = -getAngle();

        vec2 anchorOffset(m_visualComponent->getWidth()*m_visualComponent->getAnchor().x, m_visualComponent->getHeight()*m_visualComponent->getAnchor().y);

        vec2 parentPosition = getPosition();
        vec2 correctedPos = position.rotateByAngle(parentPosition, angleInRad) + anchorOffset;

        return (correctedPos.x <= parentPosition.x + m_visualComponent->getWidth() &&
		        correctedPos.x >= parentPosition.x &&
                correctedPos.y <= parentPosition.y + m_visualComponent->getHeight() &&
		        correctedPos.y >= parentPosition.y);
    }

    return false;
}