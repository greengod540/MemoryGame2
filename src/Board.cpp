#include "Board.h"
#include<Engine.h>
#include "Presenter.h"
Presenter presenter1;
Player player;
#include <Presenter.h>
#include <InputManager.h>
#include <Player.h>
#include <SoundManager.h>
#include <iostream>
#include <fstream>
#include <Card.h>
#include <SDL.h>
#include <vector>
#include <defines.h>
#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include "TextCreator.h"
#include <objects.h>
#include <DialogueTree.h>
#include "LevelLoader.h"
#include "defines.h"


Drawable background;
DialogueTree dg;
LevelLoader levelLoader;



Board::Board()
{

}

Board::~Board()
{

}


void Board::init()
{
	levelLoader.levelInit();
	

	
	
}





















void Board::draw()
{
	/*
	
	
	std::cout << InputManager::m_mouseCoor.x << " " << InputManager::m_mouseCoor.y << endl;
	
	


	if (reset == false) {
		for (int y = 0; y < objects.size(); y++) {
			drawObject(objects[y]);
			
		}
		
		
		lightManager.createLight({ InputManager::m_mouseCoor.x, InputManager::m_mouseCoor.y, 200, 200 }, 255, 255, 255, 128);
		lightManager.rayTrace({ InputManager::m_mouseCoor.x, InputManager::m_mouseCoor.y, 200, 200 }, objects);
		
		
		
		
		

	}
	else if (ids.empty()) {
		presenter1.drawObject(tryAgainScreen);
		Text_Creator::TextCreate((FONT_FOLDER + "OldLondon.ttf").c_str(), 300, 10, 10, 300, 100, ("moves: " + std::to_string(moves)).c_str(), text);
		Text_Creator::TextCreate((FONT_FOLDER + "OldLondon.ttf").c_str(), 300, 300, 111, 300, 100, ("mistakes: " + std::to_string(mistakes)).c_str(), text);
		presenter1.drawObject(Yes);
		presenter1.drawObject(No);


	}
	
	
	
	
	
	
	*/

	
	
	

	levelLoader.Levelloader();








}



















void Board::destroy()
{
	

}











void Board::handleInput()
{
	

}

