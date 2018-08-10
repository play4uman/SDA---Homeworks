#pragma once
#include <memory>
#include <string>
#include "..\Constants.h"
#include "Living.h"
#include "Projectile.h"

class Player : public Living
{
    RTTI_ENABLE(Player, Living)
public:
	virtual void update(float deltaTime);
};

