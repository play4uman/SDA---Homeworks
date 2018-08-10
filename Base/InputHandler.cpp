#include "InputHandler.h"

static InputHandler* s_pInstance = nullptr;

InputHandler::InputHandler():m_mousePosition(0.0f,0.0f), m_prevMousePosition(0.0f, 0.0f)
{
    reset();
}


InputHandler::~InputHandler()
{
}


void InputHandler::uninit()
{
}

void InputHandler::update(float deltaTime)
{
	SDL_Event event;

    m_prevMousePosition = m_mousePosition;

    memcpy(m_prevMouseButtonStates, m_mouseButtonStates, sizeof(m_prevMouseButtonStates));


	int mouseX, mouseY;

	SDL_GetMouseState(&mouseX, &mouseY);
	
	m_mousePosition.x = ((float)mouseX);
	m_mousePosition.y = ((float)mouseY);
		
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				m_mouseButtonStates[MouseButton_LEFT] = true;
			}

			if (event.button.button == SDL_BUTTON_MIDDLE)
			{
				m_mouseButtonStates[MouseButton_MIDDLE] = true;
			}

			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				m_mouseButtonStates[MouseButton_RIGHT] = true;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				m_mouseButtonStates[MouseButton_LEFT] = false;
			}

			if (event.button.button == SDL_BUTTON_MIDDLE)
			{
				m_mouseButtonStates[MouseButton_MIDDLE] = false;
			}

			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				m_mouseButtonStates[MouseButton_RIGHT] = false;
			}
		}
        else if(event.type == SDL_QUIT)
        {
            m_quitRequested = true;
        }
	}

    memcpy(m_ptrLastKeyState, m_ptrKeyState, SDL_Scancode::SDL_NUM_SCANCODES);
	memcpy(m_ptrKeyState, SDL_GetKeyboardState(0), SDL_Scancode::SDL_NUM_SCANCODES);
}

InputHandler* InputHandler::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = new InputHandler();
	}

	return s_pInstance;
}

void InputHandler::Destroy()
{
    delete s_pInstance;
}

const vec2& InputHandler::getMousePosition()
{
	return m_mousePosition;
}

bool InputHandler::isKeyPressed(SDL_Scancode key)
{
	if (m_ptrKeyState != 0)
	{
		if (m_ptrKeyState[key] == 1)
		{
			return true;
		}

		return false;
	}
	
	return false;
}

bool InputHandler::isKeyJustPressed(SDL_Scancode key)
{
    if (m_ptrKeyState)
    {
        if (m_ptrKeyState[key] == 1)
        {
            if (m_ptrLastKeyState)
            {
                return m_ptrLastKeyState[key] == 0;
            }

            return true;
        }

        return false;
    }

    return false;
}

bool InputHandler::isKeyJustReleased(SDL_Scancode key)
{
    if (m_ptrKeyState)
    {
        if (m_ptrKeyState[key] == 0)
        {
            if (m_ptrLastKeyState)
            {
                return m_ptrLastKeyState[key] == 1;
            }

            return true;
        }

        return false;
    }

    return false;
}

void InputHandler::reset()
{
    m_quitRequested = false;
    memset (m_prevMouseButtonStates, 0 , sizeof(m_prevMouseButtonStates));
    memset (m_mouseButtonStates, 0 , sizeof(m_mouseButtonStates));
    memset (m_ptrLastKeyState, 0 , sizeof(m_ptrLastKeyState));
    memset (m_ptrKeyState, 0 , sizeof(m_ptrKeyState));
}
