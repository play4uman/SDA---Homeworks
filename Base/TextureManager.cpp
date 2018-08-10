#include "TextureManager.h"
#include "..\Constants.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

RGBA RGBA::readColor(rapidjson::Value& value)
{
    RGBA rgba;
    rgba.r = (uint8_t) value[0].GetUint();
    rgba.g = (uint8_t) value[1].GetUint();
    rgba.b = (uint8_t) value[2].GetUint();
    rgba.a = (uint8_t) value[3].GetUint();
    return rgba;
}

Texture::Texture(SDL_Texture* texture):m_sdlTexture(texture)
{
}

Texture::~Texture()
{
    SDL_DestroyTexture(m_sdlTexture);
}

void Texture::setBlendMode(SDL_BlendMode blendMode)
{
    SDL_SetTextureBlendMode(m_sdlTexture, blendMode);
}

void Texture::clear(RGBA color)
{
    Uint32 texFormat;
    int texAccess, texW, texH;
    SDL_QueryTexture(m_sdlTexture, &texFormat, &texAccess, &texW, &texH);

    SDL_PixelFormat *format = SDL_AllocFormat(texFormat);
    SDL_Surface *clearSurf = SDL_CreateRGBSurface(0, texW, texH, format->BitsPerPixel, format->Rmask, format->Gmask, format->Bmask, format->Amask);
    Uint32 ucolor = SDL_MapRGBA(format, color.r, color.g, color.b, color.a);
    SDL_FreeFormat(format);

    SDL_FillRect(clearSurf, nullptr, ucolor);
    SDL_LockSurface(clearSurf);
    update(0, 0, texW, texH, clearSurf->pixels, clearSurf->pitch);
    SDL_UnlockSurface(clearSurf);
    SDL_FreeSurface(clearSurf);
}

void Texture::update(int x, int y, int w, int h, const void* pixels, int pitch)
{
    SDL_Rect rect = { x, y, w, h };
    SDL_UpdateTexture(m_sdlTexture, &rect, pixels, pitch);
}

static TextureManager* s_pInstance= nullptr;
TextureManager::TextureManager():
    m_renderer(nullptr)
{
	s_pInstance = nullptr;
}

void TextureManager::setRenderer(SDL_Renderer* renderer)
{
    m_renderer = renderer;
}


TextureManager::~TextureManager()
{
    m_mapTexture.clear();
}

std::shared_ptr<Texture> TextureManager::load(const std::string& fileName)
{
    if (m_mapTexture[fileName].expired())
    {
        SDL_Surface* pTempSyrface = IMG_Load(fileName.c_str());
        if (pTempSyrface == nullptr)
        {
            return nullptr;
        }

        SDL_Texture* pTexture = SDL_CreateTextureFromSurface(m_renderer, pTempSyrface);

        SDL_FreeSurface(pTempSyrface);

        if (pTexture != nullptr)
        {
            std::cout << fileName << ": Texture loaded " << std::endl;
            std::shared_ptr<Texture> texture(new Texture(pTexture));
            m_mapTexture[fileName] = std::weak_ptr<Texture>(texture);
            return texture;
        }
        return nullptr;
    }
    
    return m_mapTexture[fileName].lock();	
}

std::shared_ptr<Texture> TextureManager::create(int width, int height, Uint32 sdlPixelFormat, int sdlAccess, const std::string& name)
{
    if (!m_mapTexture[name].expired())
        return m_mapTexture[name].lock();
    SDL_Texture *sdlTex = SDL_CreateTexture(m_renderer, sdlPixelFormat, sdlAccess, width, height);
    if (!sdlTex)
        return nullptr;
    std::shared_ptr<Texture> texture(new Texture(sdlTex));
    if (!name.empty())
        m_mapTexture[name] = texture;
    return texture;
}

TextureManager* TextureManager::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = new TextureManager();
	}

	return s_pInstance;
}

void TextureManager::Destroy()
{
    delete s_pInstance;
    s_pInstance = nullptr;
}