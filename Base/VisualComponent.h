#pragma once

#include "BaseComponent.h"
#include "Sprite.h"
#include "vec2.h"
#include <vector>
#include <string>
#include "../rapidjson/document.h"

class VisualComponent : public BaseComponent
{
    RTTI_ENABLE(VisualComponent, BaseComponent)
protected:
    VisualComponent():
        m_currentRenderSprite(nullptr),
        m_width(0), 
        m_height(0), 
        m_flipMode(SDL_FLIP_NONE),
        m_alpha(255),
        m_anchor(0.5f, 0.5f),
        m_renderLayer(64)
    {
    }

public:
    VisualComponent(int width, int height, float angle, const std::vector<Sprite*>& sprites):
    m_currentRenderSprite(nullptr),
    m_width(width), 
    m_height(height), 
    m_flipMode(SDL_FLIP_NONE),
    m_alpha(255),
    m_anchor(0.5f, 0.5f),
    m_renderLayer(64)
    {
        m_sprites.insert(m_sprites.end(), sprites.begin(), sprites.end());
        m_currentRenderSprite = m_sprites.size() > 0 ? m_sprites[0] : nullptr;
    }

    virtual ~VisualComponent();

    virtual void update(float deltaTime);
    virtual void render();
    virtual void serialize(rapidjson::Value& value);

    virtual uint8_t getUpdatePriority() const { return 1;}
    virtual uint8_t getRenderLayer() const { return m_renderLayer; }
    virtual void setRenderLayer(uint8_t val) { m_renderLayer = val; }

    void setCurrentRenderSpriteIndex(Uint32 currentRenderSprite) 
    { 
        if(currentRenderSprite < m_sprites.size())
        {
            if(m_currentRenderSprite != m_sprites[currentRenderSprite])
            {
                getCurrentSpritePlaying()->gotoAndStop(0);
            }

            m_currentRenderSprite = m_sprites[currentRenderSprite];
        }
    }

    void setCurrentRenderSpriteByName(const std::string& spriteName) 
    { 
        for(Sprite* sprite : m_sprites)
        {
            if(sprite->getID() == spriteName)
            {
                m_currentRenderSprite = sprite;
                break;
            }
        }
    }

    Sprite*       getSprite(std::string ID)
    {
        for(Sprite* sprite : m_sprites)
        {
            if(sprite->getID() == ID)
            {
                return sprite;
            }
        }

        return nullptr;
    }

    void          setAlpha(Uint8 alpha) { m_alpha = alpha; }
    void          setFlipMode(SDL_RendererFlip flipMode) { m_flipMode = flipMode;}

    void          setWidth(int width) {m_width = width;}
    void          setHeight(int height) {m_height = height;}

    int           getWidth()    const {return m_width;}
	int           getHeight()   const {return m_height;}

    const vec2& getAnchor()    const {return m_anchor;}

    void setAnchorPoint(const vec2& anchor) { m_anchor = anchor; }

    Sprite*       getCurrentSpritePlaying() { return m_currentRenderSprite;}

    Sprite* getRenderSpriteByIndex(Uint32 renderSprite) 
    { 
        if(renderSprite < m_sprites.size())
        {
            return m_sprites[renderSprite];
        }

        return getCurrentSpritePlaying();
    }

    Sprite* getRenderSpriteByName(std::string spriteID) 
    { 
        for(Sprite* sprite : m_sprites)
        {
            if(sprite->getID() == spriteID)
            {
                return sprite;
            }
        }

        return getCurrentSpritePlaying();
    }

protected:
    vec2 m_anchor;
    int m_width;
	int m_height;
    std::vector<Sprite*> m_sprites;
    SDL_RendererFlip m_flipMode;
    Uint8 m_alpha;
    uint8_t m_renderLayer;

private:
    Sprite* m_currentRenderSprite;
};