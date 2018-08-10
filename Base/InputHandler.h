#pragma once
#define HAVE_M_PI
#include "SDL.h"
#include "vec2.h"
#include <map>
#include <vector>


enum MouseButton
{
	MouseButton_LEFT = 0,
	MouseButton_MIDDLE = 1,
	MouseButton_RIGHT = 2,
    MouseButton_COUNT
};

class InputHandler
{
    InputHandler& operator=(const InputHandler&);
    InputHandler(const InputHandler&);
public:
	static InputHandler* Instance();
    static void Destroy();

    bool isMouseButtonJustPressed(MouseButton mouseButton) const { return !m_prevMouseButtonStates[mouseButton] && m_mouseButtonStates[mouseButton];}
    bool isMouseButtonJustReleased(MouseButton mouseButton) const { return m_prevMouseButtonStates[mouseButton] && !m_mouseButtonStates[mouseButton];}
    bool isMouseButtonPressed(MouseButton mouseButton) const { return m_prevMouseButtonStates[mouseButton] && m_mouseButtonStates[mouseButton];}

	bool isKeyPressed(SDL_Scancode key);
    bool isKeyJustPressed(SDL_Scancode key);
    bool isKeyJustReleased(SDL_Scancode key);
    bool quitRequested() {return m_quitRequested;};

	const vec2& getMousePosition();
    bool getMousePositionChanged() const {return m_prevMousePosition != m_mousePosition;}
	
	void update(float deltaTime);
	void uninit();
	void reset();
	
private:
	InputHandler();
	~InputHandler();

	bool m_buttonStates[MouseButton_COUNT];

    bool m_prevMouseButtonStates[MouseButton_COUNT];
	bool m_mouseButtonStates[MouseButton_COUNT];

    bool m_quitRequested;
    vec2 m_prevMousePosition;
	vec2 m_mousePosition;
	std::map<SDL_Scancode, bool> m_mapKeyStates;
    Uint8 m_ptrKeyState[SDL_Scancode::SDL_NUM_SCANCODES];
    Uint8 m_ptrLastKeyState[SDL_Scancode::SDL_NUM_SCANCODES];
};

