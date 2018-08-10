#pragma once
#define HAVE_M_PI
#include "SDL_ttf.h"
#include <map>
#include <memory>
#include <string>
#include "TextureManager.h"

class Font
{
public:
    Font(TTF_Font* font);
    ~Font();

    void render(Texture *target, int x, int y, const std::string& text);

    RGBA& getForeground() { return m_foreground; } 
    RGBA& getBackground() { return m_background; }
protected:
    TTF_Font* m_font;
    RGBA m_foreground, m_background;
};

class FontManager
{
public:
    static FontManager* instance();
    static void destroy();

    std::shared_ptr<Font> load(const std::string& fileName, int ptSize);
protected:
    std::map<std::pair<std::string, int>, std::weak_ptr<Font>> m_mapFonts;
    static FontManager *s_instance;
};