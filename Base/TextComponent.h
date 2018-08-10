#pragma once
#include "BaseComponent.h"
#include "Font.h"

class TextComponent: public BaseComponent
{
    RTTI_ENABLE(TextComponent, BaseComponent)
public:
    void addText(int x, int y, const std::string& text);

    virtual void serialize(rapidjson::Value& value);
    virtual uint8_t getUpdatePriority() const { return 0; }

    std::shared_ptr<Font> getFont() const { return m_font; }
    void setFont(std::shared_ptr<Font> val) { m_font = val; }
protected:
    std::shared_ptr<Font> m_font;
    std::string m_targetSprite;
    RGBA m_foreground, m_background;
};
