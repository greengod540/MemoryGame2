#include "InputManager.h"

bool InputManager::m_mouseIsPressed = bool();
bool InputManager::m_mouseRIsPressed = bool();

int2 InputManager::m_mouseCoor = int2();

const Uint8* InputManager::m_keyboardState = nullptr;

InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

void InputManager::setMouseMultiply(float2 multyplier)
{
	m_mouseMultiply.x = multyplier.x;
	m_mouseMultiply.y = multyplier.y;
}

void InputManager::handleInput()
{
	m_mouseIsPressed = false;
	m_mouseRIsPressed = false;
	//Events for the mouse
	while (SDL_PollEvent(&m_event))
	{
		switch (m_event.type)
		{
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&(m_mouseCoor.x), &(m_mouseCoor.y));

			m_mouseCoor.x *= m_mouseMultiply.x;
			m_mouseCoor.y *= m_mouseMultiply.y;

			break;
		case SDL_MOUSEBUTTONDOWN:
			if (m_event.button.button == SDL_BUTTON_LEFT)
			{
				m_mouseIsPressed = true;
			}
			else if (m_event.button.button == SDL_BUTTON_RIGHT) {
				m_mouseRIsPressed = true;		
			}
			break;
		}
	}

	m_keyboardState = SDL_GetKeyboardState(NULL);
}

bool InputManager::isMousePressed()
{
	return m_mouseIsPressed;
}

bool InputManager::isRMousePressed()
{
	return m_mouseRIsPressed;
}

bool isAnyKeyPressed()
{
	int numOfKeys = 322;

	for (int i = 0; i < numOfKeys; i++)
	{
		if (InputManager::m_keyboardState[i])
		{
			return true;
		}
	}

	return false;
}

bool isKeyPressed(SDL_Scancode code)
{
	return InputManager::m_keyboardState[code];
}