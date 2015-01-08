#pragma once
#ifndef ntSDL_H_INCLUDED
#define ntSDL_H_INCLUDED

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <vector>
#include <list>

namespace ntSDL
{
	//SDL PARAMETERS
	extern int SCREEN_WIDTH;
	extern int SCREEN_HEIGHT;
	extern int SCREEN_BPP;
	extern int fontsize;
	extern int fontoffset;
	extern SDL_Color fontcolor;

	extern int camspeed;
	extern TTF_Font *font;

	//SDL IMAGE LOADING
	extern SDL_Surface *screen;
	extern SDL_Rect nullrect;
	SDL_Surface *load_image(std::string);
	//DRAW ENTITY
	void apply_surface(int,int,SDL_Surface*,SDL_Surface*,SDL_Rect*);
	void ntSDLShutdown();

	SDL_Surface* makeNewSurface(int,int);

	int initFonts();

	//hurp durp
	extern std::string windowtitle;
	extern std::string fontname;
	void SetWindowTitle(std::string);

	//BOOTS UP SDL
	int initSDL();
	//resize magic
	void resizeScreen(int,int);
}
#endif