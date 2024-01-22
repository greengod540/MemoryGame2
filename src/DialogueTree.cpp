#include <DialogueTree.h>
#include "Engine.h"
#include <algorithm>
#include <sstream>
Text_Creator txtCreator;

bool DialogueTree::biggerThan(std::string line, std::map<string, int> skillValue) {
    stringstream iss(line);
    string word;
    string skill;
    string inieger;
    string file1;
    string file2;
    while (iss >> word) {
        if (word == "<biggerThan") {
            iss >> skill >> inieger >> file1 >> file2;
            if (skillValue[skill] >= stoi(inieger)) {
                filenamered = file1;
                return true;


            }
            else if (skillValue[skill] < stoi(inieger)) {
                filenamered = file2;
                return true;
            }
        }
        std::cout << "FILENAME: " + filenamered;
    }


    std::cout << "Keyword not found in the string." << std::endl;

}


std::string DialogueTree::readFile(std::string filePath)
{
    TTF_Init();
    if (conversation) {

        quitOptions.clear();
        convoSpeech = "";
        quitOptions.clear();
        options.clear();
        optionsRect.clear();
        optionToFile.clear();
        optionToOptionY.clear();
        int optionX = 800;
        int optionY = 410;
        std::vector<std::string> filenames;
        std::string unEditedLine = line;
        bool isFileOption = false;
        bool isEmptyFile = false;
        string flag1 = "< end";
        string flag2 = "<file";
        string quitFlag = "<quit";
        string biggerThanFlag = "<biggerThan";
        string smallerThanFlag = "<smallerthan";
        string optionFlag = "Option: ";
        string emptyFileFlag = "<emptyFile";
        std::vector<string> varialues;


        std::fstream stream(filePath);
        if (!stream.is_open()) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            return "";
        }


        SDL_Color color;
        color.a = 255;
        color.b = 255;
        color.g = 255;
        color.r = 255;
        SDL_Color optionsColor;
        optionsColor.a = 0;
        optionsColor.b = 0;
        optionsColor.g = 255;
        optionsColor.a = 255;
        std::string filename1 = "";
        std::string filenameCheck;
        std::string filenameCheck2;
        std::string numberToCheck;
        std::map<std::string, int> skilChecks;
        skilChecks["Tech"] = tech;
        skilChecks["Speech"] = Speech;
        skilChecks["Strength"] = Strength;
        skilChecks["Sneak"] = Sneak;

        options.clear();
        convoSpeech = "";

        // Inside your while loop
        while (getline(stream, line)) {
            // Search for ".txt" in the line
            unEditedLine = line;
            size_t filePos = line.find("<file");
            size_t txtPos = line.find(".txt");

            if (line.find("Option:") == 0) {
                auto posIterator = std::search(
                    line.begin(), line.end(),
                    flag2.begin(), flag2.end()
                );

                


                if (posIterator != line.end()) {
                    if (filePos != std::string::npos && txtPos != std::string::npos && filePos < txtPos) {
                        std::string filename = line.substr(filePos + 6, txtPos - (filePos + 6));
                        filenames.push_back(filename);
                    }
                    isFileOption = true;
                }
                else {
                    // ... (existing code)
                }

                auto posIterator2 = std::search(
                    line.begin(), line.end(),
                    quitFlag.begin(), quitFlag.end()
                );
                auto posIterator3 = std::search(
                    line.begin(), line.end(),
                    optionFlag.begin(), optionFlag.end()
                );



                if (posIterator2 != line.end()) {
                    line.erase(posIterator2, line.end());
                    quitOptions.push_back(line);
                }
                else {
                    // ... (existing code)
                }


                options.push_back(line);
            }
            else {
                auto posIteratorEF = std::search(
                    line.begin(), line.end(),
                    emptyFileFlag.begin(), emptyFileFlag.end()
                );

                if (posIteratorEF != line.end()) {
                    conversation = false;
                }

                convoSpeech += line;
            }

        }

        stream.close();

        for (auto& option : options) {
            bool isQuitOption = false;

            for (const auto& quitOpt : quitOptions) {
                if (option == quitOpt) {
                    isQuitOption = true;
                    break;
                }
            }

            if (isQuitOption) {
                optionToFile[optionY] = "quit";
            }
            else if (isFileOption) {
                for (const auto& file : filenames) {
                    size_t filePos = option.find("<file");
                    if (option.find(file) != std::string::npos) {
                        option.erase(filePos, file.length() + 12); // +6 to include "<file"
                        optionToFile[optionY] = file + ".txt";
                    }
                }
            }
            
            if (biggerThan(option, skilChecks) && !filenamered.empty() && option.find(biggerThanFlag)) {
                std::cout << "why doesnt this work? " + filenamered;
                optionToFile[optionY] = filenamered;
            }

            





            SDL_Rect rect = { 800, optionY, 200, 100 };
            optionsRect.push_back(rect);

            Text_Creator::TextCreate((FONT_FOLDER + "BulzingItalic.ttf").c_str(), 27, 800, optionY, 200, 100, option.c_str(), optionsColor);

            optionY += 200;
        }

        Text_Creator::TextCreate((FONT_FOLDER + "BulzingItalic.ttf").c_str(), 27, 500, 140, 800, 200, convoSpeech.c_str(), { 255, 255, 255, 255 });


        return convoSpeech;
    }

}


void DialogueTree::optionInteract()
{




    for (int i = 0; i < optionsRect.size(); i++) {
        if (isMouseInRect(InputManager::m_mouseCoor, optionsRect[i]) && InputManager::isMousePressed()) {
            mouseInsideOption = true;
            j = i;  // Set j to the current index

            if (optionToFile[optionsRect[i].y] != "quit" && optionToFile[optionsRect[i].y] != "empty") {

                filenameStart = optionToFile[optionsRect[i].y];
                
                
            }
            else if(optionToFile[optionsRect[i].y] == "quit") {
                conversation = false;

            }
            
            
            
            

            // Exit the loop once we find the first option with mouse inside
            mouseInsideOption = true;
        }
    }




    // You can add additional logic here if needed
}

void DialogueTree::drawText()
{


}

void DialogueTree::clearOptions()
{
    // Clear the optionsRect vector
    quitOptions.clear();
    convoSpeech = "";
    quitOptions.clear();
    options.clear();
    optionsRect.clear();
    optionToFile.clear();
    optionToOptionY.clear();

    // Optionally, you can clear other data structures like optionToFile, etc.

    // Clear the text by drawing an empty string
    SDL_Color color = { 0, 0, 0, 255 };  // Set color to black, you can change it based on your requirements
    Text_Creator::TextCreate((FONT_FOLDER + "BulzingItalic.ttf").c_str(), 27, 500, 140, 800, 200, "", color);

}