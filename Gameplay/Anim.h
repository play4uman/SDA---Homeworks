#pragma once
#include "../Base/BaseObject.h"
#include "PlayState.h"

class Anim: public BaseObject
{
    RTTI_ENABLE(Anim, BaseObject)
public:
    virtual void init();

    virtual void update(float deltaTime);
};