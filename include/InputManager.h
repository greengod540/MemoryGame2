#pragma once

#include "Engine.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	static int2 m_mouseCoor;

	static const Uint8* m_keyboardState;

	void handleInput();
	void setMouseMultiply(float2 multyplier);

	static bool isMousePressed();

private:
	SDL_Event m_event;

	float2 m_mouseMultiply;

	static bool m_mouseIsPressed;
};

bool isAnyKeyPressed();

bool isKeyPressed(SDL_Scancode code);