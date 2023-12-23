#pragma once

#include "Engine.h"
#include<string>
#include "Player.h"
#include <Card.h>
#include <SDL.h>
#include <vector>
#include <map>



class Board
{
public:

	Board();
	~Board();


	void mainMenu();
	void setRandomPositions();
	void showFor();
	void tryAgain();
	void init();
	void update();
	void draw();
	void destroy();
	void resetGame();
	void handleInput();


	std::map<int, int> ids;
	Drawable backgroundTable;

	Card card1;
	Card card2;
	Card card3;
	Card card4;
	Card card5;
	Card card6;
	Card card7;
	Card card8;
	Card card9;
	Card card10;
	Drawable tryAgainScreen;
	Drawable Yes;
	Drawable No;
	Drawable Knife;
	Drawable Beer1;
	Drawable dragonHead;
	Drawable Beer2;
	Drawable food1;
	Drawable background2;
	Drawable background3;
	std::vector<Card> cards = { card1, card2, card3, card4, card5, card6, card7, card8, card9, card10 };
	std::vector<int> cardsID = { 1, 2, 3, 3, 5, 5, 2, 1, 9, 9 };
	std::vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	bool foundMap(int keyOrValue1, int keyOrValue2, std::map<int, int>& myMap);
	void eraseElementsByValue(std::map<int, int>& myMap, const int& valueToErase);
	void handleCardSelection(int cardIndex);


	SDL_Texture* m_background;
};