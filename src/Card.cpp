#include "Card.h"
#include <Presenter.h>
#include <defines.h>
#include <iostream>
#include "Engine.h"

Presenter presenter_Card;
std::string backimg, frontimg;

Card::Card()
{
}

Card::~Card()
{
}

void Card::init(std::string configFile)
{
    std::fstream stream;
    std::string tmp;

    stream.open(configFile);
    stream >> tmp >> backimg >> frontimg;
    stream >> tmp >> tmp >> tmp >> card.rect.w >> card.rect.h;

    back = loadTexture(backimg);
    front = loadTexture(frontimg);
   



    // Initialize drawRect based on the random value



}

void Card::reset()
{
   

}



void Card::destroy()
{
    SDL_DestroyTexture(back);
    SDL_DestroyTexture(front);
}

void Card::draw()
{


    if (isVisible == true) {
        presenter_Card.drawObject(card);
    }


}


void Card::changeTextureBack()
{
   
        card.texture = front;
    
}

void Card::changeTextureFront()
{
    
        card.texture = back;
    
}

void Card::setRandomPos()
{
    int randomPosX = 300 + std::rand() % (800 - 300 + 1);
    int randomPosY = std::rand() % 700;

    card.rect.x = randomPosX;
    card.rect.y = randomPosY;

        
}

int Card::getCardID()
{
    return Card::ID;
}

void Card::setCardID(int setID)
{
    Card::ID = setID;
}

void Card::hide()
{
    isVisible = false;
}

void Card::show()
{
    isVisible = true;
}
