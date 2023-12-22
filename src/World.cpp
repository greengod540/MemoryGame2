#include "World.h"

World::World()
{
    m_running = true;
}

World::~World()
{

}

void World::init()
{
    m_presenter.init();

    m_board.init();

    m_soundManager.init();
}

void World::run()
{
    m_presenter.draw();
    m_inputManager.handleInput();

    m_board.update();
    m_board.draw();
    m_board.handleInput();
    
}

void World::destroy()
{
    SDL_DestroyWindow(m_presenter.m_mainWindow);
    SDL_DestroyRenderer(m_presenter.m_mainRenderer);

    m_inputManager.m_keyboardState = NULL;

    m_board.destroy();

    m_soundManager.destroy();
}

bool World::isRunning()
{
    return m_running;
}
