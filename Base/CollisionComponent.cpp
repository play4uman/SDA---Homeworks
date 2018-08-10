#include "CollisionComponent.h"
#include "BaseObject.h"
#include "GameState.h"

RTTI_REGISTER(CollisionComponent)

CollisionComponent::CollisionComponent(BaseShape *shape):
    m_originalShape(shape), m_shape(nullptr), m_collisionUpdateId(0)
{
}

CollisionComponent::~CollisionComponent()
{
    delete m_shape;
    delete m_originalShape;
}

void CollisionComponent::serialize(rapidjson::Value& value)
{
    const char* shapeType = value["ShapeType"].GetString();
    if (!strcmp(shapeType, "AABB"))
    {
        m_originalShape = new Shape<AABB>();
        static_cast<Shape<AABB>*>(m_originalShape)->m_Shape = AABB(vec2((float)value["MinX"].GetDouble(), (float)value["MinY"].GetDouble()), 
                                                                   vec2((float)value["MaxX"].GetDouble(), (float)value["MaxY"].GetDouble()));
    } 
    else if (!strcmp(shapeType, "OBB"))
    {
        m_originalShape = new Shape<OBB>();
        static_cast<Shape<OBB>*>(m_originalShape)->m_Shape = OBB(vec2((float)value["MinX"].GetDouble(), (float)value["MinY"].GetDouble()), 
                                                                 vec2((float)value["MaxX"].GetDouble(), (float)value["MaxY"].GetDouble()),
                                                                 (float)value["Angle"].GetDouble());
    }
    else if (!strcmp(shapeType, "Circle"))
    {
        m_originalShape = new Shape<Circle>();
        static_cast<Shape<Circle>*>(m_originalShape)->m_Shape = Circle(vec2((float)value["CenterX"].GetDouble(), (float)value["CenterY"].GetDouble()), 
                                                                      (float)value["Radius"].GetDouble());
    }
    else if (!strcmp(shapeType, "Line"))
    {
        m_originalShape = new Shape<Line>();
        static_cast<Shape<Line>*>(m_originalShape)->m_Shape = Line(vec2((float)value["StartX"].GetDouble(), (float)value["StartY"].GetDouble()), 
                                                                   vec2((float)value["EndX"].GetDouble(), (float)value["EndY"].GetDouble()));
    }
}

void CollisionComponent::init()
{
    if (m_originalShape)
        m_shape = m_originalShape->transform(m_parent->getTransform());
}

void CollisionComponent::draw(Shape<OBB> *o0)
{
    SDL_Point pts[5];
    vec2 p = o0->m_Shape.m_transform * -vec2One;
    pts[0].x = (int)p.x;
    pts[0].y = (int)p.y;
    p = o0->m_Shape.m_transform * vec2(-1.0f, 1.0f);
    pts[1].x = (int)p.x;
    pts[1].y = (int)p.y;
    p = o0->m_Shape.m_transform * vec2One;
    pts[2].x = (int)p.x;
    pts[2].y = (int)p.y;
    p = o0->m_Shape.m_transform * vec2(1.0f, -1.0f);
    pts[3].x = (int)p.x;
    pts[3].y = (int)p.y;
    pts[4] = pts[0];
    m_parent->getGameState<GameState>()->drawLines(pts, 5, 255, 0, 0);
}

void CollisionComponent::draw(Shape<AABB> *b0)
{
    SDL_Point pts[5];
    pts[0].x = (int)b0->m_Shape.m_min.x;
    pts[0].y = (int)b0->m_Shape.m_min.y;
    pts[1].x = (int)b0->m_Shape.m_min.x;
    pts[1].y = (int)b0->m_Shape.m_max.y;
    pts[2].x = (int)b0->m_Shape.m_max.x;
    pts[2].y = (int)b0->m_Shape.m_max.y;
    pts[3].x = (int)b0->m_Shape.m_max.x;
    pts[3].y = (int)b0->m_Shape.m_min.y;
    pts[4] = pts[0];
    m_parent->getGameState<GameState>()->drawLines(pts, 5, 255, 0, 0);
}

void CollisionComponent::draw(Shape<Circle> *c0)
{
    SDL_Point pts[21];
    for (unsigned i = 0; i < arrSize(pts); ++i)
    {
        float angle = 2 * M_PI * i / (arrSize(pts) - 1);
        pts[i].x = (int)(c0->m_Shape.m_center.x + cosf(angle) * c0->m_Shape.m_radius);
        pts[i].y = (int)(c0->m_Shape.m_center.y + sinf(angle) * c0->m_Shape.m_radius);
    }
    m_parent->getGameState<GameState>()->drawLines(pts, arrSize(pts), 255, 0, 0);
}

void CollisionComponent::draw(Shape<Line> *l0)
{
    SDL_Point pts[2];
    pts[0].x = (int)l0->m_Shape.m_p0.x;
    pts[0].y = (int)l0->m_Shape.m_p0.y;
    pts[1].x = (int)l0->m_Shape.m_p1.x;
    pts[1].y = (int)l0->m_Shape.m_p1.y;
    m_parent->getGameState<GameState>()->drawLines(pts, 2, 255, 0, 0);
}

bool CollisionComponent::s_render = false;

void CollisionComponent::render()
{
    if (Shape<OBB>* obbShape = dynamic_cast<Shape<OBB>*>(m_shape))
        draw(obbShape);
    else if (Shape<AABB>* aabbShape = dynamic_cast<Shape<AABB>*>(m_shape))
        draw(aabbShape);
    else if (Shape<Circle>* circleShape = dynamic_cast<Shape<Circle>*>(m_shape))
        draw(circleShape);
    else if (Shape<Line>* lineShape = dynamic_cast<Shape<Line>*>(m_shape))
        draw(lineShape);
}

void CollisionComponent::update(float deltaTime)
{
    m_collisions.clear();
    if (m_shape)
        m_originalShape->transform(m_shape, m_parent->getTransform());
}

void CollisionComponent::uninit()
{
}

std::vector<BaseObject*>& CollisionComponent::getCollisions()
{
    size_t currentUpdateId = m_parent->getGameState<GameState>()->getUpdateId();
    if (currentUpdateId != m_collisionUpdateId)
    {
        std::vector<BaseObject*> ignore;
        ignore.push_back(m_parent);
        m_parent->getGameState<GameState>()->testCollision(*m_shape, &m_collisions, &ignore);
        m_collisionUpdateId = currentUpdateId;
    }
    return m_collisions;
}