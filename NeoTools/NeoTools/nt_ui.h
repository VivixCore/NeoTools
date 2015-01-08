#pragma once
#ifndef nt_UI_H_INCLUDED
#define nt_UI_H_INCLUDED

#include <vector>
#include <list>
#include "nt_uiblock.h"

namespace nt_ui
{
	extern int SYSTEM_TIMER, SYSTEM_CHECKBOX, SYSTEM_CHECKBOX_BONUS;
	int load_settings();
	int save_settings();
	int build_ui();
	int gettypefromstring(std::string);
	//extern int bannerheight;
	extern bool invertmousescroll;
	extern int maxwindowheight;
	extern int mousescrollrate;
	extern std::vector<ntUIBlock*> iconblocks;
	extern std::vector<ntUIBlock*> iconsystem;
	extern std::list<std::vector<ntUIBlock*>> blockcategories;
	/*
	extern std::vector<SDL_Surface*> images;
	extern std::vector<int> ms;
	extern std::vector<int> coords;
	extern std::vector<int> states;
	extern std::vector<int> types;
	extern std::vector<ntTimer*> timers;
	*/
}

#endif