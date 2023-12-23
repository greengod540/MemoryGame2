#include "TextCreator.h"
#include "Presenter.h"

Drawable Text_Creator::text1;

void Text_Creator::TextCreate(const char* font, int size, int x, int y, int w, int h, const char* text, SDL_Color color)
{
	TTF_Init();
	TTF_Font* Sans = TTF_OpenFont(font, size);
	if (!Sans) {
		std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
		// Handle the error
	}


	

	// this is the color in rgb format,
	// maxing out all would give you the color white,
	// and it will be your text's color


	// as TTF_RenderText_Solid could only be used on
	// SDL_Surface then you have to create the surface first
	SDL_Surface* surfaceMessage =
		TTF_RenderText_Solid(Sans, text, color);

	if (!surfaceMessage) {
		std::cerr << "Failed to create text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
		// Handle the error
	}

	// now you can convert it into a texture
	text1.texture = SDL_CreateTextureFromSurface(Presenter::m_mainRenderer, surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = x;  //controls the rect's x coordinate 
	Message_rect.y = y; // controls the rect's y coordinte
	Message_rect.w = w; // controls the width of the rect
	Message_rect.h = h; 
	text1.rect = Message_rect;// controls the height of the rect

	// (0,0) is on the top left of the window/screen,
	// think a rect as the text's box,
	// that way it would be very simple to understand

	// Now since it's a texture, you have to put RenderCopy
	// in your game loop area, the area where the whole code executes

	// you put the renderer's name first, the Message,
	// the crop size (you can ignore this if you don't want
	// to dabble with cropping), and the rect which is the size
	// and coordinate of your texture
	Presenter::drawObject(text1);
}
