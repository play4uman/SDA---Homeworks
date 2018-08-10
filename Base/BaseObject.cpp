#include "BaseObject.h"
#include "InputHandler.h"
#include "..\Gameplay\GameFactory.h"

RTTI_REGISTER(BaseObject)

BaseObject::~BaseObject()
{
    for(BaseComponent* component : m_components)
    {
        delete component;
    }
    m_components.clear();
}

void   BaseObject::addComponent(BaseComponent* component)
{
    if(component)
    {
        component->setParentObject(this);
        std::vector<BaseComponent*>::iterator itt = m_components.begin();
        for(;itt!=m_components.end();itt++)
        {
            if((*itt)->getUpdatePriority() >= component->getUpdatePriority())
            {
                break;
            }
        }
        m_components.insert(itt, component);
    }
}


void   BaseObject::init()
{
    for(BaseComponent* component : m_components)
	{
		component->init();
	}
}

void   BaseObject::update(float deltaTime)
{
    for(BaseComponent* component : m_components)
	{
		component->update(deltaTime);
	}
}

void   BaseObject::render(std::vector<BaseComponent*>& renderables)
{
    for(BaseComponent* component : m_components)
	{
        if (component->getRenderLayer() != 0)
		    renderables.push_back(component);
	}
}

void BaseObject::serialize(rapidjson::Value& value)
{
    setAngle((float)value["Angle"].GetDouble());

    rapidjson::Value& components = value["Components"];

    unsigned numberOfComponents = components.Size();
    for(unsigned i = 0; i < numberOfComponents; ++i)
    {
        addComponent(GameFactory::createBaseComponentFromJson(components[i], this));
    }
}