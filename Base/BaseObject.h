#pragma once
#define HAVE_M_PI
#include <string>
#include "Sprite.h"
#define HAVE_M_PI
#include <SDL.h>
#include "vec2.h"
#include <memory>
#include "BaseComponent.h"
#include <vector>
#include "../rapidjson/document.h"
#include "RTTI.h"

class GameState;
class BaseObject
{
    RTTI_ENABLE_BASE(BaseObject)
    BaseObject& operator=(const BaseObject&);
    BaseObject(const BaseObject&);
public:
    BaseObject() : m_gameState(nullptr)
    { m_transform.setIdentity(); }

    virtual ~BaseObject();

    virtual void init();
    virtual void update(float deltaTime);
    virtual void render(std::vector<BaseComponent*>& renderables);
    virtual void serialize(rapidjson::Value& value);

    void addComponent(BaseComponent* component);
    template<class TYPE> TYPE* getComponent();

    Transform2& getTransform() { return m_transform; }
    void setTransform(const Transform2& val) { m_transform = val; }

    vec2 getPosition() const { return m_transform.getTranslation(); }
    void setPosition(const vec2& pos) { m_transform.setTranslationOnly(pos); }

    float getAngle() const { return m_transform.getRotation(); }
    void setAngle(float angle) { m_transform.setRotationOnly(angle); }

    vec2 getScale() const { return m_transform.getScale(); }
    void setScale(const vec2& scale) { m_transform.setScaleOnly(scale); }

    virtual void uninit(){}

    template <class T>
    T* getGameState() const { return rtti_cast<T>(m_gameState); }

    void setGameState(GameState *gameState) { m_gameState = gameState; }
protected:
    std::vector<BaseComponent*> m_components;
    Transform2 m_transform;
    GameState* m_gameState;
};

template<class TYPE> TYPE* BaseObject::getComponent()
{
    for(BaseComponent* component : m_components)
    {
        TYPE* founded = rtti_cast<TYPE>(component);
        if(founded)
            return founded;
    }

    return nullptr;
}

