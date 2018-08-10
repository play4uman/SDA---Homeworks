#pragma once
#include "RTTI.h"
#include "../rapidjson/document.h"

class BaseObject;

class BaseComponent
{
    RTTI_ABSTRACT_BASE(BaseComponent)
    BaseComponent& operator=(const BaseComponent&);
    BaseComponent(const BaseComponent&);
public:
    BaseComponent():m_parent(nullptr)
    {}

    void setParentObject(BaseObject* parent){m_parent = parent;}
    virtual ~BaseComponent(){};

    virtual void init(){};
    virtual void render(){};
    virtual void update(float deltaTime){};
    virtual void serialize(rapidjson::Value& value) {};

    virtual uint8_t getUpdatePriority() const = 0;
    virtual uint8_t getRenderLayer() const { return 0; } // Not rendered by default

    virtual void uninit(){}
protected:
    BaseObject* m_parent;
};

