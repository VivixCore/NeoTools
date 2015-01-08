#include "nt_ui.h"
#include "nt_util.h"
#include "nt_errors.h"
#include "nt_uiblock_types.h"
#include "nt_openweb.h"
#include <SDL_syswm.h>
#include <fstream>

std::vector<ntUIBlock*> nt_ui::iconblocks;
std::vector<ntUIBlock*> nt_ui::iconsystem;
std::list<std::vector<ntUIBlock*>> nt_ui::blockcategories;
//int nt_ui::bannerheight = 32;
int nt_ui::maxwindowheight = 32;
int nt_ui::mousescrollrate = 32;
bool nt_ui::invertmousescroll = false;
int nt_ui::SYSTEM_CHECKBOX = -1;
int nt_ui::SYSTEM_TIMER = -1;
int nt_ui::SYSTEM_CHECKBOX_BONUS = -1;
/*
std::vector<SDL_Surface*> nt_ui::images;
std::vector<int> nt_ui::ms;
std::vector<int> nt_ui::coords;
std::vector<int> nt_ui::states;
std::vector<int> nt_ui::types;
std::vector<ntTimer*> nt_ui::timers;
std::vector<int> nt_ui::times;
*/

int nt_ui::load_settings()
{
	std::vector<std::string> info;
	int a = nt_util::openTextFile("./Assets/System/config_settings.txt",info,ntErrors::ERROR_SETTINGS_CONFIG_BROKEN);
	if(a!=0)
	return a;

	std::vector<std::string> line;
	std::string cmd;
	int x;
	int ww = ntSDL::SCREEN_WIDTH;
	int wh = ntSDL::SCREEN_HEIGHT;
	int posx = 0;
	int posy = 0;

	for(x=0;x<info.size();x++)
	{
		line = nt_util::pipe2StringVector(info[x]);
		cmd = line[0];
		if(cmd=="WINDOW_WIDTH")
		ww = atoi(line[1].c_str());
		else if(cmd=="WINDOW_HEIGHT")
		wh = atoi(line[1].c_str());
		else if(cmd=="WINDOW_POS_X")
		posx = atoi(line[1].c_str());
		else if(cmd=="WINDOW_POS_Y")
		posy = atoi(line[1].c_str());
		else if(cmd=="FONT")
		ntSDL::fontname = line[1];
		else if(cmd=="FONT_SIZE")
		ntSDL::fontsize = atoi(line[1].c_str());
		else if(cmd=="FONT_COLOR")
		{
			ntSDL::fontcolor.r=atoi(line[1].c_str());
			ntSDL::fontcolor.g=atoi(line[2].c_str());
			ntSDL::fontcolor.b=atoi(line[3].c_str());
		}
		else if(cmd=="FONT_VERTICAL_OFFSET")
		ntSDL::fontoffset = atoi(line[1].c_str());
		else if(cmd=="MAX_WINDOW_HEIGHT")
		maxwindowheight = atoi(line[1].c_str());
		else if(cmd=="MOUSE_SCROLL_SPEED")
		mousescrollrate = atoi(line[1].c_str());
	}
	ntSDL::resizeScreen(ww,wh);
	nt_webtools::positionwindow(posx,posy);
	return 0;
}

int nt_ui::save_settings()
{
	std::ofstream clear("./Assets/System/config_settings.txt",std::fstream::trunc);
	clear.close();

	std::string linesep = "////////////////////////////////////////////////////////////////////\n";
	std::ofstream out("./Assets/System/config_settings.txt",std::fstream::app);
		out << linesep;
		out << "//Window Settings\n";
		out << linesep;

		SDL_SysWMinfo i;
		SDL_VERSION(&i.version);//this is important don't remove it
		if(SDL_GetWMInfo(&i))
		{
			HWND b = i.window;
			RECT getrect;
			GetWindowRect(b,&getrect);

			int posx = getrect.left;
			int posy = getrect.top;

			out << "WINDOW_POS_X|" << nt_util::num2string(posx) << "\n";
			out << "WINDOW_POS_Y|" << nt_util::num2string(posy) << "\n";
		}

		out << "WINDOW_WIDTH|" << nt_util::num2string(ntSDL::SCREEN_WIDTH) << "\n";
		out << "WINDOW_HEIGHT|" << nt_util::num2string(ntSDL::SCREEN_HEIGHT) << "\n";
		out << "MAX_WINDOW_HEIGHT|" << nt_util::num2string(nt_ui::maxwindowheight) << "\n\n";
		
		out << linesep;
		out << "//Font Settings\n";
		out << linesep;
		out << "FONT|" << ntSDL::fontname << "\n";
		out << "FONT_SIZE|" << nt_util::num2string(ntSDL::fontsize) << "\n";
		out << "FONT_VERTICAL_OFFSET|" << nt_util::num2string(ntSDL::fontoffset) << "\n";
		out << "FONT_COLOR|" << nt_util::num2string(ntSDL::fontcolor.r) << "|" << nt_util::num2string(ntSDL::fontcolor.g) << "|" << nt_util::num2string(ntSDL::fontcolor.b) << "\n\n";

		out << linesep;
		out << "//Input Settings\n";
		out << linesep;
		out << "//Speed at which mouse wheel scrolls per tick (in pixels)\n";
		out << "MOUSE_SCROLL_SPEED|" << nt_util::num2string(nt_ui::mousescrollrate) << "\n";
		out << "//Inverts mousewheel input\n";
		out << "INVERT_MOUSE_SCROLL|" << nt_util::num2string(nt_ui::invertmousescroll) << "\n";

		out.close();
	return 0;
}

int nt_ui::gettypefromstring(std::string in)
{
	using namespace ntUIBlockTypes;

	if(in=="BANNER")
	return TYPE_BANNER;
	else if(in=="ICON")
	return TYPE_ICON;
	else if(in=="ICONABOUT")
	return TYPE_ABOUT;
	else if(in=="DAILY")
	return TYPE_X_DAILY;
	else if(in=="TIMED")
	return TYPE_TIMER;
	else if(in=="TIMEOFDAY")
	return TYPE_TIME_OF_DAY;
	else if(in=="CHECKTIMER")
	return TYPE_METEOR;
	else if(in=="GAME")
	return TYPE_GAME;
	else if(in=="RESET")
	return TYPE_RESET;

	//anything else I guess just display it
	return TYPE_ICON;
}

int nt_ui::build_ui()
{
	using namespace ntUIBlockTypes;

	//load config file for icon placement stuff
	std::vector<std::string> info;
	std::vector<std::string> line;

	iconsystem.clear();
	int a = 7;
	int x = 0;
	while(~--a)
	iconsystem.push_back(0);
	int index = 0;
	std::string cmd;
	int type = 100;

	//SYSTEM ICONS FIRST BECAUSE WE WILL BE COPYING THEM INTO THE MAIN THING
	a = nt_util::openTextFile("./Assets/System/config_system_icons.txt",info,ntErrors::ERROR_SYSTEM_UI_CONFIG_BROKEN);
	if(a!=0)
	return a;
	for(x=0;x<info.size();x++)
	{
		line = nt_util::pipe2StringVector(info[x]);
		cmd = line[0];

		if(cmd=="BG")
		{
			index=0;
			type = TYPE_SYSTEM_BG;
		}
		else if(cmd=="TIMER")
		{
			index=SYSTEM_TIMER=1;
			type = TYPE_SYSTEM_TIMER;
		}
		else if(cmd=="CHECK")
		{
			index=SYSTEM_CHECKBOX=2;
			type = TYPE_SYSTEM_CHECKBOX;
		}
		else if(cmd=="CHECK_BONUS")
		{
			index=SYSTEM_CHECKBOX_BONUS=5;
			type = TYPE_SYSTEM_CHECKBOX_BONUS;
		}
		else if(cmd=="RESET")
		{
			index=3;
			type = TYPE_SYSTEM_RESET;
		}

		ntUIBlock* block = new ntUIBlock();
		iconsystem[index]=block;

		//load image
		block->setimage(ntSDL::load_image("./Assets/IMG/"+line[1]));

		//set coords
		int xcoord = 0, ycoord = 0, xsize = 0, ysize = 0;

		if(line[2]!="xdelta")
		xcoord = atoi(line[2].c_str());
		else xcoord = 0;
		if(line[3]!="ydelta")
		ycoord = atoi(line[3].c_str());
		else ycoord = 0;
		if(line[4]!="xsize")
		xsize = atoi(line[4].c_str());
		else xsize = 32;
		if(line[5]!="ysize")
		ysize = atoi(line[5].c_str());
		else ysize = 32;

		block->setcoords(xcoord,ycoord);

		//set type
		block->settype(type);
		block->settime(0);
		block->setsize(xsize,ysize);
		block->seturl("");
		block->setstate(0);

		if(type==TYPE_SYSTEM_BG)
		iconblocks.push_back(block);
	}

	info.clear();
	a = nt_util::openTextFile("./Assets/System/config_link_icons.txt",info,ntErrors::ERROR_UI_CONFIG_BROKEN);
	if(a!=0)
	return a;

	//Now load the actual asset icon things
	for(x=0;x<info.size();x++)
	{
		ntUIBlock* block = new ntUIBlock();
		line = nt_util::pipe2StringVector(info[x]);

		block->setname(line[0]);
		//load image
		block->setimage(ntSDL::load_image("./Assets/IMG/"+line[1]));

		//set coords
		int xcoord = 0, ycoord = 0;

		if(line[2]!="x")
		xcoord = atoi(line[2].c_str());
		else xcoord = -32;
		if(line[3]!="y")
		ycoord = atoi(line[3].c_str());
		else ycoord = -32;

		block->setcoords(xcoord,ycoord);

		//set type
		block->settype(type=gettypefromstring(line[4]));

		//and push back the times, too
		block->settime(atoi(line[5].c_str()));

		//set size of block
		block->setsize(atoi(line[6].c_str()),atoi(line[7].c_str()));

		//add url
		if(line.size()>8)
		block->seturl(line[8]);
		else
		block->seturl("");

		//set state
		block->setstate(0);

		if(type==TYPE_BANNER)
		{
			if(iconblocks.size()>0)
			blockcategories.push_back(iconblocks);
			iconblocks.clear();
		}
		block->setrender(false);
		iconblocks.push_back(block);

		if(type==TYPE_X_DAILY || type==TYPE_GAME)
		{
			//add # checkboxes where appropriate
			int v = block->timer_s;
			if(v!=0)
			{
				if(type==TYPE_GAME)
				{
					if(v==-1)
					v=1;
					else
					v+=2;
				}

				while(~--v)
				{
					ntUIBlock* a = new ntUIBlock();
					if((v>=3)&&(type==TYPE_GAME))
					*a = *iconsystem[SYSTEM_CHECKBOX_BONUS];
					else
					*a = *iconsystem[SYSTEM_CHECKBOX];
					//ntSDL::vcSetWindowTitle(nt_util::num2string(a->type));
					a->setcoords(block->coord_x+block->width+a->width*v+a->coord_x,block->coord_y+a->coord_y);
					a->rect.x = a->width*a->state;
					a->rect.w = a->width;
					a->rect.h = a->height;
					a->rect.y = 0;
					iconblocks.push_back(a);
				}
			}
		}
		else if(type==TYPE_TIMER)
		{
			//add timer button
			ntUIBlock* a = new ntUIBlock();
			*a = *iconsystem[SYSTEM_TIMER];
			a->settime(block->timer_s);
			a->setcoords(block->coord_x+block->width+a->coord_x,block->coord_y+a->coord_y);
			iconblocks.push_back(a);
		}
		else if(type==TYPE_METEOR)
		{
			//add checkbox
			ntUIBlock* a = new ntUIBlock();
			*a = *iconsystem[SYSTEM_CHECKBOX];
			int dx = a->width + a->coord_x;
			int dy = a->coord_y;
			a->setcoords(block->coord_x+block->width+a->coord_x,block->coord_y+a->coord_y);
			a->rect.x = a->width*a->state;
			a->rect.w = a->width;
			a->rect.h = a->height;
			a->rect.y = 0;
			iconblocks.push_back(a);
			//and a timer
			a = new ntUIBlock();
			*a = *iconsystem[SYSTEM_TIMER];
			a->settime(block->timer_s);
			a->setcoords(block->coord_x+block->width+a->coord_x+dx,block->coord_y+a->coord_y+dy);
			iconblocks.push_back(a);
		}
		else if(type==TYPE_ICON)
		{
			//add nothing
		}
	}
	//final push
	if(iconblocks.size()>0)
	blockcategories.push_back(iconblocks);
	iconblocks.clear();

	return 0;
}