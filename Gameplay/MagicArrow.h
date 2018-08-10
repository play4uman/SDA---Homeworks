#pragma once
#include <memory>
#include <string>
#include "../rapidjson/document.h"
#include "..\Constants.h"
#include "Movable.h"
#include "Projectile.h"

class MagicArrow : public Projectile
{
	RTTI_ENABLE(MagicArrow, Projectile)
public:
	MagicArrow();
	virtual void update(float deltaTime);
};
