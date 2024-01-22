#include "Player.h"
#include "Presenter.h"
#include "InputManager.h"



Player::Player()
{
}

Player::~Player()
{
}

void Player::init()
{
	angle = 0;
	flip = SDL_FLIP_NONE;
	frontT = loadTexture(PLAYER_FOLDER + "FRONT.bmp");
	rightT = loadTexture(PLAYER_FOLDER + "RIGHT.bmp");
	backT = loadTexture(PLAYER_FOLDER + "BACK.bmp");
	runAnim = animator.init(PLAYER_FOLDER + "runF\\", 20, ".bmp");
	runSAnim = animator.init(PLAYER_FOLDER + "runS\\", 20, ".bmp");
	runBAnim = animator.init(PLAYER_FOLDER + "runB\\", 20, ".bmp");

	m_up = SDL_GetScancodeFromName("W");
	m_down = SDL_GetScancodeFromName("S");
	m_left = SDL_GetScancodeFromName("A");
	m_right = SDL_GetScancodeFromName("D");
	m_player.texture = frontT;
	m_player.rect = { 0, 0, 200, 200 };
	m_speed = 10;
}

void Player::update()
{
	move();
}

void Player::draw()
{
	if (!playerHidden) {
		Presenter::drawObject(m_player, angle, flip);
	}
	
}

void Player::move()
{
    // Separate animation update from movement logic

    if (isKeyPressed(m_up)) {
        m_player.rect.y -= m_speed;
        m_player.texture = animator.returnFrame(runBAnim, true);
        flip = SDL_FLIP_NONE;
        angle = 0;
    }
    else if (isKeyPressed(m_left)) {
        m_player.rect.x -= m_speed;
        m_player.texture = animator.returnFrame(runSAnim, true);
        flip = SDL_FLIP_HORIZONTAL;
        angle = 0;
    }
    else if (isKeyPressed(m_down)) {
        m_player.rect.y += m_speed;
        m_player.texture = animator.returnFrame(runAnim, true);
        flip = SDL_FLIP_NONE;
        angle = 0;
    }
    else if (isKeyPressed(m_right)) {
        m_player.rect.x += m_speed;
        m_player.texture = animator.returnFrame(runSAnim, true);
        flip = SDL_FLIP_NONE;
        angle = 0;
    }
}


void Player::destroy()
{
	SDL_DestroyTexture(m_player.texture);
}
