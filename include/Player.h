#pragma once

#include "Engine.h"
#include "Presenter.h"
#include "Animator.h"

class Player
{
public:
	Player();
	~Player();

	void init();
	void update();
	void draw();
	void move();
	void destroy();
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	int angle = 0;
	
	SDL_Texture* frontT;
	SDL_Texture* rightT;
	SDL_Texture* backT;
	Animator animator;
	std::vector<SDL_Texture*> runAnim;
	std::vector<SDL_Texture*> runSAnim;
	std::vector<SDL_Texture*> runBAnim;

	SDL_RendererFlip flip1 = SDL_FLIP_NONE;
	bool playerHidden = false;


	Drawable m_player;
private:

	SDL_Scancode m_up, m_left, m_down, m_right;

	int m_speed;
};