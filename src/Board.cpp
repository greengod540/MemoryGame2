#include "Board.h"
#include<Engine.h>
#include "Presenter.h"
Presenter presenter1;
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



static bool allowed = true;
static const double showCardsDuration = 4.0;
int moves = 0;
int2 firstPos = { 0, 0 };
int2 secondPos = { 0, 0 };
int card1Check;
int card2Check;

int background = NULL;


bool change_tex = false;



SoundManager soundManager;

bool draw1 = false;
bool reset = false;

int mistakes = 0;

int mousePressed = 0;
std::vector<int> index = { 0, 0 };
SDL_Rect mouse_coors;
static bool tryAgainDrawn = false;

Player player1;
Player player2;
SDL_Color text = { 255, 255, 255 };




int j = 0;

InputManager inpMan;

int xMouse = 0;
int yMouse = 0;



Board::Board()
{

}

Board::~Board()
{

}
void Board::mainMenu()
{
}




void Board::setRandomPositions() {
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<int> posXDist(300, 800);
	std::uniform_int_distribution<int> posYDist(0, 700);

	for (int i = 0; i < cards.size(); i++) {
		bool overlap;

		do {
			overlap = false;
			int randomPosX = posXDist(eng);
			int randomPosY = posYDist(eng);

			SDL_Rect currentCardRect = { randomPosX, randomPosY, 100, 200 };

			for (int j = 0; j < i; j++) {
				if (SDL_HasIntersection(&currentCardRect, &cards[j].card.rect)) {
					overlap = true;
					break;
				}
			}

			if (!overlap) {
				cards[i].card.rect = { randomPosX, randomPosY, 100, 200 };
			}
		} while (overlap);
	}
}







void Board::tryAgain()
{
	
	soundManager.playSound(SUCCESS);
	presenter1.drawObject(tryAgainScreen);
	presenter1.drawObject(Yes);
	presenter1.drawObject(No);

}

void Board::init()
{

	
	
	
	
	tryAgainScreen.texture = loadTexture("tryagain3.bmp");
	tryAgainScreen.rect = { 0, 0, Presenter::m_SCREEN_WIDTH, Presenter::m_SCREEN_HEIGHT };
	Yes.texture = loadTexture("YES.bmp");
	Yes.rect = { 700, 500, 200, 200 };
	No.texture = loadTexture("No.bmp");
	No.rect = { 700, 700, 200, 200 };


	
	std::string configFile = "config\\boardInit.txt";

	std::fstream stream;

	std::string backgorundImg, playerConfigFile, tmp;


	stream.open(configFile);


	stream >> tmp >> backgorundImg;


	stream.close();



	lightManager.init();




	soundManager.init();
	

	


	ids[0] = 1;
	ids[2] = 3;
	ids[4] = 5;
	ids[6] = 7;
	ids[8] = 9;



	Knife.texture = loadTexture("oneKnife.bmp");
	Knife.shadowTexture = loadTexture("oneKnife.bmp");


	Beer1.texture = loadTexture("Beer1.bmp");
	Beer1.shadowTexture = loadTexture("Beer1.bmp");
	Knife.rect = { 1300, 100, 50, 400 };
	Beer1.rect = { 989, 574, 300, 300 };
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<int> posXDist(300, 800);
	std::uniform_int_distribution<int> posYDist(0, 700);



	std::random_device rd1;
	std::default_random_engine eng1(rd1());
	std::uniform_int_distribution<int> backgrounds(1, 3);
	background = backgrounds(eng1);

	
	switch (background) {
	case 1:
		createObject(backgroundTable, loadTexture("woodTable.bmp"), { 0, 0, Presenter::m_SCREEN_WIDTH, Presenter::m_SCREEN_HEIGHT }, false);
		createObject(food1, loadTexture("food2.bmp"), {128, 705, 300, 300}, true);
		createObject(Beer2, loadTexture("Beer2.bmp"), { 989, 0, 200, 200 }, true);
		createObject(dragonHead, loadTexture("dragonHead.bmp"), { 50, 0, 200, 200 }, true);
		
		
		
	
		

		break;

	case 2:
		createObject(background2, loadTexture("medievalBackground.bmp"), { 0, 0, Presenter::m_SCREEN_WIDTH, Presenter::m_SCREEN_HEIGHT }, false);
		break;

	case 3:
		createObject(background3, loadTexture("medievalBarBackground.bmp"), { 0, 0, Presenter::m_SCREEN_WIDTH, Presenter::m_SCREEN_HEIGHT }, false);
		break;
	}

	

	card1.init("config\\card\\cardInit.txt");
	std::cout << SDL_GetError();
	card2.init("config\\card\\cardInit2.txt");
	card3.init("config\\card\\cardInit3.txt");
	card4.init("config\\card\\cardInit4.txt");
	card5.init("config\\card\\cardInit5.txt");
	card6.init("config\\card\\cardInit6.txt");
	card7.init("config\\card\\cardInit7.txt");
	card8.init("config\\card\\cardInit8.txt");
	card9.init("config\\card\\cardInit9.txt");
	card10.init("config\\card\\cardInit10.txt");
	cards = { card1, card2, card3, card4, card5, card6, card7, card8, card9, card10 };
	for (int i = 0; i < cards.size(); i++) {
		bool overlap;

		do {
			overlap = false;
			int randomPosX = posXDist(eng);
			int randomPosY = posYDist(eng);

			SDL_Rect currentCardRect = { randomPosX, randomPosY, 100, 200 };

			for (int j = 0; j < i; j++) {
				if (SDL_HasIntersection(&currentCardRect, &cards[j].card.rect)) {
					overlap = true;
					break;
				}
			}

			if (!overlap) {
				cards[i].card.rect = { randomPosX, randomPosY, 100, 200 };
			}
		} while (overlap);
	}
	for (int i = 0; i < cards.size(); i++) {
		createObject(cards[i].card, cards[i].card.texture, cards[i].card.rect, true);
	}



}



void Board::update() {







}













void Board::draw()
{
	
	


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












}



















void Board::destroy()
{
	//player1.destroyPlayer();
	SDL_DestroyTexture(m_background);

}

void Board::resetGame()
{
	objects.clear();

	ids[0] = 1;
	ids[2] = 3;
	ids[4] = 5;
	ids[6] = 7;
	ids[8] = 9;

	std::cout << "dont work";
	std::fstream stream;
	stream.open("log.txt");

	stream << SDL_GetError();


	stream.close();

	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<int> posXDist(300, 800);
	std::uniform_int_distribution<int> posYDist(0, 700);
	for (int i = 0; i < cards.size(); i++) {
		bool overlap;

		do {
			overlap = false;
			int randomPosX = posXDist(eng);
			int randomPosY = posYDist(eng);

			SDL_Rect currentCardRect = { randomPosX, randomPosY, 100, 200 };

			for (int j = 0; j < i; j++) {
				if (SDL_HasIntersection(&currentCardRect, &cards[j].card.rect)) {
					overlap = true;
					break;
				}
			}

			if (!overlap) {
				cards[i].card.rect = { randomPosX, randomPosY, 100, 200 };
			}
		} while (overlap);
	}

	std::random_device rd1;
	std::default_random_engine eng1(rd1());
	std::uniform_int_distribution<int> backgrounds(1, 3);
	background = backgrounds(eng1);
	switch (background) {
	case 1:
		createObject(backgroundTable, loadTexture("woodTable.bmp"), { 0, 0, Presenter::m_SCREEN_WIDTH, Presenter::m_SCREEN_HEIGHT }, false);
		createObject(food1, loadTexture("food2.bmp"), { 128, 705, 300, 300 }, true);
		createObject(Beer2, loadTexture("Beer2.bmp"), { 989, 0, 200, 200 }, true);
		createObject(dragonHead, loadTexture("dragonHead.bmp"), { 50, 0, 200, 200 }, true);






		break;

	case 2:
		createObject(background2, loadTexture("medievalBackground.bmp"), { 0, 0, Presenter::m_SCREEN_WIDTH, Presenter::m_SCREEN_HEIGHT }, false);
		break;

	case 3:
		createObject(background3, loadTexture("medievalBarBackground.bmp"), { 0, 0, Presenter::m_SCREEN_WIDTH, Presenter::m_SCREEN_HEIGHT }, false);
		break;
	}


	for (int i = 0; i < cards.size(); i++) {
		cards[i].show();
		updateObject(cards[i].card, true);
	}

	moves = 0;
	mistakes = 0;
	reset = false;


}

bool Board::foundMap(int keyOrValue1, int keyOrValue2, std::map<int, int>& myMap)
{
	for (const auto& entry : myMap) {
		if ((entry.first == keyOrValue1 && entry.second == keyOrValue2) ||
			(entry.first == keyOrValue2 && entry.second == keyOrValue1)) {
			return true;
		}
	}
	return false;
}


void Board::eraseElementsByValue(std::map<int, int>& myMap, const int& valueToErase)
{

	auto it = myMap.begin();
	while (it != myMap.end()) {
		if (it->second == valueToErase) {
			it = myMap.erase(it);
			std::cout << "Element with value " << valueToErase << " erased." << std::endl;
		}
		else {
			++it;
		}
	}



}




void Board::handleCardSelection(int cardIndex)
{

	static int firstClickIndex = 0;
	static int secondClickIndex = 0;






	// Card selection logic
	if (mousePressed == 1) {
		firstClickIndex = cardIndex;
		cards[firstClickIndex].changeTextureBack();
		updateObject(cards[firstClickIndex].card, true);
	}
	else if (mousePressed == 2) {
		secondClickIndex = cardIndex;
		updateObject(cards[secondClickIndex].card, true);
		if (firstClickIndex != secondClickIndex) {
			cards[secondClickIndex].changeTextureBack();



			if (foundMap(firstClickIndex, secondClickIndex, ids)) {
				soundManager.playSound(CARDS_SAME);
				cards[firstClickIndex].hide();
				cards[secondClickIndex].hide();
				ids.erase(firstClickIndex);
				ids.erase(secondClickIndex);
				updateObject(cards[firstClickIndex].card, false);
				updateObject(cards[secondClickIndex].card, false);
				mousePressed = 0;
			}

			else if (foundMap(firstClickIndex, secondClickIndex, ids) == false) {
				mistakes++;
				soundManager.playSound(CARDS_NOT_SAME);
				cards[firstClickIndex].changeTextureFront();
				cards[secondClickIndex].changeTextureFront();
				updateObject(cards[firstClickIndex].card, true);
				updateObject(cards[secondClickIndex].card, true);
				mousePressed = 0;
			}
		}
		else {
			mousePressed = 1;
		}
		
		
	}
	
}


void Board::handleInput()
{
	int mouseX, mouseY;

	static auto startTime = std::chrono::steady_clock::now(); // Record the start time

	SDL_GetGlobalMouseState(&mouseX, &mouseY);
	




	if (isMouseInRect(InputManager::m_mouseCoor, Yes.rect) && InputManager::isMousePressed() && reset == true) {

		resetGame();
	}
	else if (isMouseInRect(InputManager::m_mouseCoor, No.rect) && InputManager::isMousePressed() && reset == true) {
		soundManager.playSound(QUIT);
		SDL_Quit();
		exit(1);


	}
	if (reset) {
		soundManager.playSound(SUCCESS);
	}



	




	for (int h = 0; h < cards.size(); h++) {
		
		int mouseX1, mouseY1;

		static auto startTime = std::chrono::steady_clock::now(); // Record the start time

		SDL_GetGlobalMouseState(&mouseX1, &mouseY1);


		SDL_Rect mouseRect = { mouseX1, mouseY1, 0, 0 };





		// Show the cards for a specified duration


		if (isMouseInRect(InputManager::m_mouseCoor, cards[h].card.rect) && InputManager::isMousePressed() && !ids.empty()) {


			std::cout << "gugu";
			moves++;

			soundManager.playSound(PLAYER_COLLISION);
			mousePressed++;
			handleCardSelection(h);
			if (mousePressed > 2) {
				mousePressed = 0; // Reset to 0 after the second click
			}
		}
		
		if (ids.empty()) {
			std::cout << "ids empty";

			reset = true;
		}

	}
}

