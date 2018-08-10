#pragma once
#include "GameplayObject.h"

class PowerUp: public GameplayObject
{
    RTTI_ENABLE(PowerUp, GameplayObject)
public:
	void update(float deltaTime);
	void setTypeName(const char* type) { typeName = type; }
	std::string getTypeName()const { return typeName; }
protected:
	std::string typeName;
};