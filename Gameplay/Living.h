#pragma once
#include "Movable.h"
#include "../Constants.h"

class Living :
    public Movable
{
    RTTI_ENABLE(Living, Movable)
public:
    Living(): Movable(), m_health(0.0f) {}

    void serialize(rapidjson::Value& value);

    virtual void SpawnSplat(const vec2& position);
    virtual void Die();

    virtual float getHealth() const { return m_health; }
    virtual void setHealth(float val);
	//Player* getPlayer()const;
protected:
    float m_health;
};

