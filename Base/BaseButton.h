#pragma once

#include "BaseObject.h"

class VisualComponent;
class BaseButton : public BaseObject
{
public:
    BaseButton(GameState* gameState, const vec2& buttonPosition):
        BaseObject(),
        m_currButtonState(IDLE),
        m_prevButtonState(IDLE),
        m_visualComponent(nullptr)
    {
        setGameState(gameState);
        setPosition(buttonPosition);
    }

    virtual void init();
    virtual void update(float deltaTime);
    bool isPressed() const { return m_currButtonState == PRESSED && m_prevButtonState == PRESSED ;}
    bool isJustPressed() const { return m_currButtonState == PRESSED && m_prevButtonState != PRESSED;}
    bool isJustReleased() const { return m_currButtonState != PRESSED && m_prevButtonState == PRESSED;}
    bool isFocused() const { return m_currButtonState == FOCUSED;}

protected:
    bool hitTest(const vec2& position);
private:
    enum ButtonState
    {
	    PRESSED = 0,
        FOCUSED,
	    IDLE,
    };

    ButtonState m_currButtonState;
    ButtonState m_prevButtonState;
    VisualComponent* m_visualComponent;
};