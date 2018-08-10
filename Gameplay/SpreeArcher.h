#pragma once
#include <memory>
#include <string>
#include "../rapidjson/document.h"
#include "..\Constants.h"
#include "Living.h"

class SpreeArcher : public Living
{
    RTTI_ENABLE(SpreeArcher, Living)
public:
	virtual void update(float deltaTime);
protected:
	int shotCounter = 0;
};

