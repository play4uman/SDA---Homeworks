#pragma once
#include <string>
#include <vector>
#include <map>
#include "../rapidjson/document.h"
#include "../Base/BaseComponent.h"
#include "../Base/BaseObject.h"

class PlayState;

class GameFactory
{
    GameFactory();
public:
    static void initialize();

    static BaseObject* createBaseObjectFromJson(rapidjson::Value& value, PlayState* parentState, const vec2& position);
    static BaseComponent* createBaseComponentFromJson(rapidjson::Value& value, BaseObject* parentObj);
};

