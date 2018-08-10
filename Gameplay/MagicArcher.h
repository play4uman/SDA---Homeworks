#pragma once
#include <memory>
#include <string>
#include "../rapidjson/document.h"
#include "..\Constants.h"
#include "Living.h"

class VisualComponent;
class MagicArcher : public Living
{
    RTTI_ENABLE(MagicArcher, Living)
public:
	virtual void update(float deltaTime);
protected:
	int shotCounter = 0;
};

