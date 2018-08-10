#pragma once
#include <string>
#define HAVE_M_PI
#include "SDL.h"
#include "../rapidjson/document.h"
#include <map>
#include <memory>

struct RGBA
{
    uint8_t r, g, b, a;
    RGBA(): r(255), g(255), b(255), a(255) {}
    RGBA(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a): r(_r), g(_g), b(_b), a(_a) {}
    RGBA(const RGBA& other) { *this = other; }

    static RGBA readColor(rapidjson::Value& value);
};

class Texture
{
    Texture& operator=(const Texture&);
    Texture(const Texture&);

    Texture();
public:
    Texture(SDL_Texture* texture);
    ~Texture();

    SDL_Texture* getSDLTexture(){return m_sdlTexture;}
    void setBlendMode(SDL_BlendMode blendMode);

    void clear(RGBA color);
    void update(int x, int y, int w, int h, const void* pixels, int pitch);
private:
    SDL_Texture* m_sdlTexture;
};

class TextureManager
{
public:
    static TextureManager* Instance();
    static void Destroy();

    void setRenderer(SDL_Renderer* renderer);
    SDL_Renderer* getRenderer() {return m_renderer;}
	std::shared_ptr<Texture> load(const std::string& fileName);
    std::shared_ptr<Texture> create(int width, int height, Uint32 sdlPixelFormat, int sdlAccess, const std::string& name = std::string());

private:
	std::map<std::string, std::weak_ptr<Texture> > m_mapTexture;
	TextureManager();
    ~TextureManager();
    SDL_Renderer* m_renderer;
};

