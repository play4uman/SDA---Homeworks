#include "GameState.h"
#include "CollisionComponent.h"
#include <algorithm>
#include "InputHandler.h"
#include <iostream>

RTTI_REGISTER(GameState)

void GameState::update(float deltaTime)
{
    ++m_updateId;
    callCallbacks();

    for (BaseObject* object : m_gameObjects)
    {
        object->update(deltaTime);
    }
    if (InputHandler::Instance()->isKeyJustPressed(SDL_SCANCODE_C))
        CollisionComponent::s_render = !CollisionComponent::s_render;
}

void GameState::render()
{
    std::vector<BaseComponent*> renderables;
    for (BaseObject* object : m_gameObjects)
        object->render(renderables);
    std::sort(renderables.begin(), renderables.end(), [](BaseComponent *c0, BaseComponent *c1) { return c0->getRenderLayer() < c1->getRenderLayer(); });
    for (BaseComponent* comp: renderables)
        comp->render();
}

bool GameState::testCollision(BaseShape& shape, std::vector<BaseObject*>* collisions, const std::vector<BaseObject*>* objToIgnore)
{
    if (collisions)
        collisions->clear();
    for (BaseObject* obj: m_gameObjects)
    {
        CollisionComponent* collisionComp = obj->getComponent<CollisionComponent>();
        if (!collisionComp)
            continue;
        if (objToIgnore && std::find(objToIgnore->begin(), objToIgnore->end(), obj) != objToIgnore->end())
            continue;
        if (!collisionComp->getShape()->intersect(shape))
            continue;
        if (!collisions)
            return true;
        collisions->push_back(obj);
    }
    return collisions && collisions->size() > 0;
}

void GameState::drawLines(const SDL_Point* points, int count, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    SDL_RenderDrawLines(m_renderer, points, count);
}