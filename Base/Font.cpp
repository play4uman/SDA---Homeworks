#include "Font.h"
#include <iostream>
#include <assert.h>

Font::Font(TTF_Font *font):
    m_font(font),
    m_foreground(255, 255, 255, 255),
    m_background(0, 0, 0, 255)
{
}

Font::~Font()
{
    TTF_CloseFont(m_font);
}

void Font::render(Texture *target, int x, int y, const std::string& text)
{
    SDL_Color fore = { m_foreground.r, m_foreground.g, m_foreground.b, m_foreground.a };
    SDL_Color back = { m_background.r, m_background.g, m_background.b, m_background.a };
    SDL_Surface *surf = TTF_RenderText_Shaded(m_font, text.c_str(), fore, back);
    assert(surf);
    if (!surf)
        return;
    Uint32 texFormat;
    int texAccess, texW, texH;
    SDL_QueryTexture(target->getSDLTexture(), &texFormat, &texAccess, &texW, &texH);
    SDL_Surface *transferSurf = surf;
    surf->format->palette->colors[0].a = m_background.a; // Because SDL is smart like that and disregards the background alpha
    // Probably disregards foreground alpha too, so we might need to overwrite rest of the colors' alphas if this becomes an issue
    if (texFormat != surf->format->format)
    {
        transferSurf = SDL_ConvertSurfaceFormat(surf, texFormat, 0);
        assert(transferSurf);
    }
    SDL_LockSurface(transferSurf);
    target->update(x, y, transferSurf->w, transferSurf->h, transferSurf->pixels, transferSurf->pitch);
    SDL_UnlockSurface(transferSurf);
    if (transferSurf != surf)
        SDL_FreeSurface(transferSurf);
    SDL_FreeSurface(surf);
}

FontManager *FontManager::s_instance = nullptr;

FontManager *FontManager::instance()
{
    if (!s_instance)
        s_instance = new FontManager();
    return s_instance;
}

void FontManager::destroy()
{
    delete s_instance;
    s_instance = nullptr;
}

std::shared_ptr<Font> FontManager::load(const std::string& fileName, int ptSize)
{
    auto key = std::pair<std::string, int>(fileName, ptSize);
    std::weak_ptr<Font> storedFont = m_mapFonts[key];
    if (!storedFont.expired())
        return storedFont.lock();

    TTF_Font *ttfFont = TTF_OpenFont(fileName.c_str(), ptSize);
    if (!ttfFont)
        return nullptr;
    std::cout << fileName << ": Font loaded with size " << ptSize << std::endl;
    std::shared_ptr<Font> font(new Font(ttfFont));
    m_mapFonts[key] = std::weak_ptr<Font>(font);
    return font;
}
