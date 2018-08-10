#pragma once
#include "gameplayobject.h"
class Movable :
    public GameplayObject
{
    RTTI_ENABLE(Movable, GameplayObject)
public:
    Movable() : GameplayObject(), m_speed(vec2Zero), m_maxVelocity(0.0f) {}

    vec2 getSpeed() const { return m_speed; }
    void setSpeed(const vec2& val) { m_speed = val; }

    float getMaxVelocity() const { return m_maxVelocity; }
    void setMaxVelocity(float val) { m_maxVelocity = val; }

    static float angleFromSpeed(const vec2& speed);

    virtual bool isBlocker(BaseObject* obj);
    virtual bool canMove(const vec2& displacement);

    virtual void init();

    void updateAngle();

    virtual void update(float deltaTime);
    virtual void serialize(rapidjson::Value& value);
	Player* Movable::getPlayer()const;
protected:
    vec2 m_speed;
    float m_maxVelocity;
};

