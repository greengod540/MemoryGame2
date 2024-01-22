#pragma once
#include <iostream>
#include <string>
#include <Engine.h>
#include <map>
#include <regex>
#include <vector>
#include "TextCreator.h"
#include "InputManager.h"
class DialogueTree {

	int j;

public:
	int optionX = 800;
	int optionY = 410;
	bool conversation = false;
	bool biggerThan(std::string line, std::map<std::string, int> skillValue);
	std::string convoSpeech;
	std::string line;
	std::string filename;
	std::vector<std::string> filenames;
	std::string filenameStart = "playerone.txt";
	std::vector<SDL_Rect> optionsRect;
	std::vector<std::string> quitOptions;
	std::map<std::string, int> optionToOptionY;
	std::vector<std::string> options;
	std::map<int, std::string> optionToFile;
	std::map<int, std::string> optionToQuit;
	std::string readFile(std::string filePath);
	std::map<int, std::string> optionToFileMap;
	std::string file1;
	std::string file2;


	string option;
	SDL_Color optionsColor;
	void drawText();
	std::string filenamered2;	
	bool mouseInsideOption = false;
	void optionInteract();
	


private:
	std::string filename1;
	std::string filenamered;
	void clearOptions();



};