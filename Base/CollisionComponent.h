#pragma once
#include "Collision.h"
#include "BaseComponent.h"
#include "../rapidjson/document.h"
#include <vector>

class CollisionComponent: public BaseComponent
{
    RTTI_ENABLE(CollisionComponent, BaseComponent)
public:
    CollisionComponent(BaseShape *originalShape = nullptr);
    virtual ~CollisionComponent();

    virtual void serialize(rapidjson::Value& value);

    virtual void init();
    virtual void render();
    virtual void update(float deltaTime);

    virtual uint8_t getUpdatePriority() const { return 10; }
    virtual uint8_t getRenderLayer() const { return s_render ? 200 : 0; }

    virtual void uninit();

    BaseShape* getOriginalShape() const { return m_originalShape; }
    void setOriginalShape(BaseShape* val) { m_originalShape = val; }

    BaseShape* getShape() const { return m_shape; }
    void setShape(BaseShape* val) { m_shape = val; }

    void draw(Shape<OBB> *o0);
    void draw(Shape<AABB> *b0);
    void draw(Shape<Circle> *c0);
    void draw(Shape<Line> *l0);

    std::vector<BaseObject*>& getCollisions();

    static bool s_render;
protected:
    BaseShape *m_originalShape;
    BaseShape *m_shape;
    std::vector<BaseObject*> m_collisions;
    size_t m_collisionUpdateId;
};