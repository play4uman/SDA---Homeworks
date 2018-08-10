#include "Anim.h"
#include "../Base/VisualComponent.h"

RTTI_REGISTER(Anim)

void Anim::init()
{
    Sprite *sprite = getComponent<VisualComponent>()->getCurrentSpritePlaying();
    if (sprite)
        sprite->play();
}

void Anim::update(float deltaTime)
{
    BaseObject::update(deltaTime);
    Sprite *sprite = getComponent<VisualComponent>()->getCurrentSpritePlaying();
    if (!sprite || !sprite->isPlaying())
        getGameState<GameState>()->removeObject(this);
}
