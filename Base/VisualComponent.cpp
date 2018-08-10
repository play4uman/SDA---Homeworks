#include "VisualComponent.h"
#include "BaseObject.h"

RTTI_REGISTER(VisualComponent)

 VisualComponent::~VisualComponent()
 {
     for(Sprite* sprite : m_sprites)
     {
         delete sprite;
     }
     
     m_sprites.clear();
 }

void VisualComponent::serialize(rapidjson::Value& value)
{
    rapidjson::Value& sprites = value["Sprites"];

    m_width = value["Width"].GetUint();
    m_height = value["Height"].GetUint();
    m_anchor.x = (float)value["AnchorX"].GetDouble();
    m_anchor.y = (float)value["AnchorY"].GetDouble();
    m_alpha = (char)value["Alpha"].GetUint();
    if (value.HasMember("Layer"))
        m_renderLayer = (uint8_t)value["Layer"].GetUint();

    unsigned int numberOfSprites = sprites.Size();
    for (unsigned int i = 0; i < numberOfSprites; ++i)
    {
        rapidjson::Value& spriteData = sprites[i];

        unsigned framesPerSecond = spriteData["FramesPerSecond"].GetUint();
        bool isLooped = spriteData["Looped"].GetBool();
        unsigned int x = spriteData["X"].GetUint();
        unsigned int y = spriteData["Y"].GetUint();
        unsigned int width = spriteData["Width"].GetUint();
        unsigned int height = spriteData["Height"].GetUint();
        unsigned int numberOfFrames = spriteData["NumberOfFrames"].GetUint();
        std::string texturePath;
        if (spriteData.HasMember("TexturePath"))
            texturePath = spriteData["TexturePath"].GetString();
        std::string textureID = spriteData["Name"].GetString();
        RGBA clearColor;
        if (spriteData.HasMember("ClearColor"))
            clearColor = RGBA::readColor(spriteData["ClearColor"]);

        Sprite* sprite = nullptr;
        if (texturePath.empty())
        {
            sprite = Sprite::createStaticSprite(textureID, width, height, SDL_PIXELFORMAT_ARGB8888, clearColor);
        }
        else if(numberOfFrames > 0)
        {
            sprite = Sprite::createAnimatedSprite(textureID, width, height, numberOfFrames, isLooped, texturePath, framesPerSecond);
        }
        else
        {
            sprite = Sprite::createStaticSprite(textureID, x, y, width, height, texturePath);
        }
        RGBA color;
        if (spriteData.HasMember("Color"))
            color = RGBA::readColor(spriteData["Color"]);
        sprite->getColor() = color;
        if (spriteData.HasMember("BlendMode"))
        {
            SDL_BlendMode mode = SDL_BLENDMODE_NONE;
            std::string blendString = spriteData["BlendMode"].GetString();
            if (blendString == std::string("Blend"))
                mode = SDL_BLENDMODE_BLEND;
            else if (blendString == std::string("Add"))
                mode = SDL_BLENDMODE_ADD;
            else if (blendString == std::string("Mod"))
                mode = SDL_BLENDMODE_MOD;
            sprite->getTexture()->setBlendMode(mode);
        }

        m_sprites.push_back(sprite);
    }

    m_currentRenderSprite = m_sprites.size() > 0 ? m_sprites[0] : nullptr;
}

void VisualComponent::update(float deltaTime)
{
    if(m_currentRenderSprite)
    {
        m_currentRenderSprite->update(deltaTime);
    }
}

void VisualComponent::render()
{
    if(m_currentRenderSprite)
    {
        vec2 position = m_parent->getPosition();
        int anchorOffsetX = (int)(m_width * m_anchor.x);
        int anchorOffsetY = (int)(m_height * m_anchor.y);
        m_currentRenderSprite->render((int)position.x - anchorOffsetX, (int)position.y - anchorOffsetY, m_width, m_height, m_parent->getAngle(), anchorOffsetX, anchorOffsetY, m_alpha, m_flipMode);
    }
}