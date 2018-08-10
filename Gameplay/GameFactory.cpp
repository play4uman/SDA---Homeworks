#pragma once
#include "GameFactory.h"

#include "../rapidjson/filereadstream.h"
#include "Player.h"
#include "NormalArcher.h"
#include "SpreeArcher.h"
#include "MagicArcher.h"
#include "Door.h"
#include "Wall.h"
#include "Column.h"
#include "Ground.h"
#include "Projectile.h"
#include "Anim.h"

#include "../Base/VisualComponent.h"
#include "../Base/CollisionComponent.h"
#include "../Base/vec2.h"

#include <cstdio>


 void GameFactory::initialize()
 {
 }

 BaseObject* GameFactory::createBaseObjectFromJson(rapidjson::Value& value, PlayState* parentState, const vec2& position)
 {
    std::string className = value["Class"].GetString();
    RTTIInfo rtti = RTTIInfo::get(className);
    assert(rtti.isValid() && "NO RTTI REGISTERED FOR THIS OBJECT TYPE");
    BaseObject *obj = rtti.createInstance<BaseObject>();
    obj->setGameState(parentState);
    obj->setPosition(position);
    obj->serialize(value);
    return obj;
 }

 BaseComponent* GameFactory::createBaseComponentFromJson(rapidjson::Value& value, BaseObject* parentObj)
 {
     std::string className = value["Class"].GetString();
     RTTIInfo rtti = RTTIInfo::get(className);
     assert(rtti.isValid() && "NO RTTI REGISTERED FOR THIS COMPONENT TYPE");
     BaseComponent *comp = rtti.createInstance<BaseComponent>();
     comp->setParentObject(parentObj);
     comp->serialize(value);
     return comp;
 }

