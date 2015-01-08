#pragma once
#ifndef nt_UIBLOCK_H_INCLUDED
#define nt_UIBLOCK_H_INCLUDED

#include "nt_sdl.h"
#include "nt_timer.h"
#include <string>

struct ntUIBlock
{
	ntUIBlock();
	~ntUIBlock();
	ntUIBlock(const ntUIBlock&);
	ntUIBlock& operator = (const ntUIBlock&);

	std::string name;
	void setname(std::string);

	std::string url;
	void seturl(std::string);

	SDL_Surface* imagep;
	void setimage(SDL_Surface*);

	int timer_s;
	void settime(int);

	int coord_x;
	int coord_y;
	void setcoords(int,int);

	int width;
	int height;
	void setsize(int,int);

	int type;
	void settype(int);

	int state;
	void setstate(int);

	bool shouldrender;
	void setrender(bool);

	std::string getCountDown();
	
	SDL_Rect rect;
	void setrect(SDL_Rect&);

	ntTimer* timer;
};

#endif