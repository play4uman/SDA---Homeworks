#pragma once
#include <memory>
#include <string>
#include "../rapidjson/document.h"
#include "..\Constants.h"
#include "Living.h"
#include "Projectile.h"
#include "../Base/InputHandler.h"
#include "../Base/VisualComponent.h"
#include "LevelData.h"

class NormalArcher : public Living
{
    RTTI_ENABLE(NormalArcher, Living)
public:
	virtual void update(float deltaTime);
	void move(float deltaTime);
protected:
	int shotCounter = 0;
};

