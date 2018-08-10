#define HAVE_M_PI
#include "Sprite.h"
#include <string>
#include "TextureManager.h"
#include <SDL_image.h>
#define _USE_MATH_DEFINES
#include <math.h>

Sprite::~Sprite()
{
}

Sprite::Sprite(const std::string& ID, const std::string& texturePath):
    m_framePerSecond(0),
    m_timePerFrame(0.0f),
    m_isPlaying(false),
    m_isLooped(false),
    m_x(0), 
    m_y(0), 
    m_width(0), 
    m_height(0), 
    m_numberOfFrames(1),
    m_currentFrame(0),
    m_elapsedTime(0.0f),
    m_currentFrameTime(0.0f),
    m_totalTime(0.0f),
    m_spriteID(ID),
    m_texturePath(texturePath),
    m_texture(nullptr),
    m_color(255, 255, 255, 255)
{
    m_render = TextureManager::Instance()->getRenderer();
    m_texture = TextureManager::Instance()->load(m_texturePath);
    SDL_QueryTexture(m_texture->getSDLTexture(), nullptr, nullptr, &m_width, &m_height);
}

Sprite::Sprite(const std::string& ID, int x, int y, int width, int height, int numberOfFrames, bool isLooped, const std::string& textureId, int framePerSecond):
    m_framePerSecond(framePerSecond),
    m_timePerFrame(1.0f/framePerSecond),
    m_isPlaying(false),
    m_isLooped(isLooped),
    m_x(x), 
    m_y(y), 
    m_width(width), 
    m_height(height), 
    m_numberOfFrames(numberOfFrames),
    m_currentFrame(0),
    m_elapsedTime(0.0f),
    m_currentFrameTime(0.0f),
    m_totalTime(numberOfFrames * (1.0f/framePerSecond)),
    m_spriteID(ID),
    m_texturePath(textureId),
    m_texture(nullptr),
    m_color(255, 255, 255, 255)
{
    m_render = TextureManager::Instance()->getRenderer();

    if(numberOfFrames > 1)
    {
        m_width = m_width / numberOfFrames;
    }

    m_timePerFrame = framePerSecond > 0 ? 1.0f/framePerSecond : 0.0f;
    m_totalTime = framePerSecond > 0 ? (numberOfFrames * (1.0f/framePerSecond)) : 0.0f;
    m_texture = TextureManager::Instance()->load(textureId);
}

Sprite::Sprite(const std::string& ID, int width, int height, Uint32 sdlPixelFormat, RGBA color):
    m_framePerSecond(0),
    m_timePerFrame(0.0f),
    m_isPlaying(false),
    m_isLooped(false),
    m_x(0), 
    m_y(0), 
    m_width(width), 
    m_height(height), 
    m_numberOfFrames(1),
    m_currentFrame(0),
    m_elapsedTime(0.0f),
    m_currentFrameTime(0.0f),
    m_totalTime(0.0f),
    m_spriteID(ID),
    m_texturePath(),
    m_texture(nullptr),
    m_color(color)
{
    m_render = TextureManager::Instance()->getRenderer();
    m_texture = TextureManager::Instance()->create(width, height, sdlPixelFormat, SDL_TEXTUREACCESS_STREAMING, ID);
    m_texture->clear(color);
}

Sprite* Sprite::createStaticSprite(const std::string& ID, const std::string& textureId)
{
    return new Sprite(ID, textureId);
}

Sprite* Sprite::createStaticSprite(const std::string& ID, int U, int V, int width, int height, const std::string& textureId)
{
    return new Sprite(ID, U, V, width, height, 1, false, textureId, 0);
}

Sprite* Sprite::createAnimatedSprite(const std::string& ID, int width, int height, int numberOfFrames, bool isLooped, const std::string& textureId, int framePerSecond)
{
    return new Sprite(ID, 0, 0, width, height, numberOfFrames, isLooped, textureId, framePerSecond);
}

Sprite* Sprite::createStaticSprite(const std::string& ID, int width, int height, Uint32 sdlPixelFormat, RGBA color)
{
    return new Sprite(ID, width, height, sdlPixelFormat, color);
}

void Sprite::play()
{
    if(m_numberOfFrames > 1 && !m_isPlaying)
    {
        m_isPlaying = true;
        m_elapsedTime = 0;
        m_currentFrameTime = 0;
        m_currentFrame = 0;
    }
}

void Sprite::stop()
{
    m_isPlaying = false;
    m_elapsedTime = m_currentFrameTime * m_timePerFrame;
    m_currentFrameTime = 0.0f;
}

void Sprite::gotoAndStop(int frameNumber)
{
    m_currentFrame = frameNumber;
    m_isPlaying = false;
    m_elapsedTime = frameNumber * m_timePerFrame;
    m_currentFrameTime = 0.0f;
}

void Sprite::update(float deltaTime)
{
    if(m_isPlaying)
    {
        m_elapsedTime += deltaTime;
        m_currentFrameTime += deltaTime;
        if(m_currentFrameTime >= m_timePerFrame)
        {
            m_currentFrameTime = m_currentFrameTime - m_timePerFrame;
            if(m_currentFrame < m_numberOfFrames-1)
            {
                ++m_currentFrame;
            }
            else if(m_currentFrame == m_numberOfFrames-1)
            {
                if(m_isLooped)
                {
                    m_currentFrame = 0;
                }
                else
                {
                    m_isPlaying = false;
                    m_elapsedTime = m_totalTime;
                }
            }
        }
    }
}

void Sprite::render(int x, int y, int width, int height, float angle, int centerOfRotationX, int centerOfRotationY, Uint8 alpha, SDL_RendererFlip flipMode)
{
    SDL_Rect srcRect = {m_x + m_currentFrame*m_width, m_y, m_width, m_height};
	SDL_Rect destRect = {x, y, width, height};
    SDL_Point centerOfRotation =  {centerOfRotationX, centerOfRotationY};

    SDL_SetTextureColorMod(m_texture->getSDLTexture(), m_color.r, m_color.g, m_color.b);
    SDL_SetTextureAlphaMod(m_texture->getSDLTexture(), (Uint8)((uint32_t)alpha * m_color.a / 255));
	SDL_RenderCopyEx(m_render, m_texture->getSDLTexture(), &srcRect, &destRect, (angle / M_PI) * 180, &centerOfRotation, flipMode);
}
