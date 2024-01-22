#include "TextBox.h"

void TextBox::createTextBox(SDL_Rect textRect, std::string text)
{

    Drawable textBox;
    textBox.rect = textRect;
    
    textBox.texture = texture;

    // Check if texture creation was successful
    if (textBox.texture == nullptr) {
        // Handle texture creation failure
        SDL_Log("Unable to create texture for TextBox: %s", SDL_GetError());
        return;
    }

    SDL_Color textColor = { 255, 255, 255, 255 };
    Text_Creator::TextCreate("font\\BulzingItalic.ttf", 35, textRect.x, textRect.y - textRect.h / 2, textRect.w, textRect.h, text.c_str(), textColor);


}
