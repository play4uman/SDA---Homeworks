#include "TextComponent.h"
#include "BaseObject.h"
#include "VisualComponent.h"
#include "GameState.h"

RTTI_REGISTER(TextComponent)

void TextComponent::addText(int x, int y, const std::string& text)
{
    auto vis = m_parent->getComponent<VisualComponent>();
    Sprite* sprite = vis->getRenderSpriteByName(m_targetSprite);
    m_font->getBackground() = m_background;
    m_font->getForeground() = m_foreground;
    m_font->render(sprite->getTexture(), x, y, text);
}

void TextComponent::serialize(rapidjson::Value& value)
{
    BaseComponent::serialize(value);
    m_font = FontManager::instance()->load(value["FontPath"].GetString(), value["FontSize"].GetInt());
    if (value.HasMember("Foreground"))
        m_foreground = RGBA::readColor(value["Foreground"]);
    if (value.HasMember("Background"))
        m_background = RGBA::readColor(value["Background"]);
    if (value.HasMember("TargetSprite"))
        m_targetSprite = value["TargetSprite"].GetString();
    if (value.HasMember("Text"))
    {
        int x = value["TextX"].GetInt();
        int y = value["TextY"].GetInt();
        std::string text = value["Text"].GetString();
        m_parent->getGameState<GameState>()->addCallback([=] { addText(x, y, text); });
    }
}

