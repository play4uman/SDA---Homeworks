#pragma once
#include "Movable.h"

class Projectile :
    public Movable
{
    RTTI_ENABLE(Projectile, Movable)
public:
    virtual bool isBlocker(BaseObject* obj);

    virtual void update(float deltaTime);

    virtual void serialize(rapidjson::Value& value);

    float getDamage() const { return m_damage; }
    void setDamage(float val) { m_damage = val; }
protected:
    float m_damage;
};

