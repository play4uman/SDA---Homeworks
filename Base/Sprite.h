#pragma once
#define HAVE_M_PI
#include <string>
#include "SDL_render.h"
#include "TextureManager.h"
#include "../rapidjson/document.h"

class Sprite
{
    Sprite& operator=(const Sprite&);
    Sprite(const Sprite&);

    Sprite(const std::string& ID, const std::string& textureId);
	Sprite(const std::string& ID, int U, int V, int width, int height, int numberOfFrames, bool isLooped, const std::string& texturePath, int framePerSecond);

    Sprite(const std::string& ID, int width, int height, Uint32 sdlPixelFormat, RGBA color);

public:
    static Sprite* createStaticSprite(const std::string& ID, const std::string& texturePath);
    static Sprite* createStaticSprite(const std::string& ID, int U, int V, int width, int height, const std::string& texturePath);
    static Sprite* createStaticSprite(const std::string& ID, int width, int height, Uint32 sdlPixelFormat, RGBA color);
    static Sprite* createAnimatedSprite(const std::string& ID, int width, int height, int numberOfFrames, bool isLooped, const std::string& texturePath, int framePerSecond);
	~Sprite();

    void serialize(rapidjson::Value& value){}

    const std::string getID() const{ return m_spriteID;}
    void play();
    void stop();
    void gotoAndStop(int frameNumber);
    bool isPlaying() const { return m_isPlaying;}
    bool isLooped() const { return m_isLooped;}
    void update(float deltaTime);
    void render(int x, int y, int width, int height, float angle, int centerOfRotationX, int centerOfRotationY, Uint8 alpha, SDL_RendererFlip flipMode);

    bool operator==(const Sprite& sprite) { return this == &sprite;}
    bool operator!=(const Sprite& sprite) { return this != &sprite;}
    bool operator==(Sprite& sprite) { return this == &sprite;}
    bool operator!=(Sprite& sprite) { return this != &sprite;}

    RGBA& getColor() { return m_color; }
    Texture *getTexture() const { return m_texture.get(); }
private:
    int m_framePerSecond;
    float m_timePerFrame;
    bool m_isPlaying;
    bool m_isLooped;
	int m_x;
	int m_y;
	int m_width;
	int m_height;
    int m_numberOfFrames;
    int m_currentFrame;
    float m_elapsedTime;
    float m_currentFrameTime;
    float m_totalTime;
    RGBA m_color;
	std::string m_texturePath;
    std::string m_spriteID;
    SDL_Renderer* m_render;
    std::shared_ptr<Texture> m_texture;
};

