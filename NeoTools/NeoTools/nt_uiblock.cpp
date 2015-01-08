#include "nt_uiblock.h"
#include "nt_util.h"

ntUIBlock::ntUIBlock()
{
	shouldrender = false;
	imagep = NULL;
	timer_s = 0;
	coord_x = 0;
	coord_y = 0;
	width = 32;
	height = 32;
	type = 0;
	state = 0;
	timer = new ntTimer();
	name = "No Name";
	url = "http://google.com/";
}

//copy constructor
ntUIBlock::ntUIBlock(const ntUIBlock& a)
{
	shouldrender = a.shouldrender;
	imagep = a.imagep;
	timer_s = a.timer_s;
	coord_x = a.coord_x;
	coord_y = a.coord_y;
	width = a.width;
	height = a.height;
	type = a.type;
	state = a.state;
	if(!timer)
	timer = new ntTimer();
	*timer = *a.timer;
	name = a.name;
	url = a.url;
}

//equal2
ntUIBlock& ntUIBlock::operator = (const ntUIBlock& a)
{
	shouldrender = a.shouldrender;
	imagep = a.imagep;
	timer_s = a.timer_s;
	coord_x = a.coord_x;
	coord_y = a.coord_y;
	width = a.width;
	height = a.height;
	type = a.type;
	state = a.state;
	if(!timer)
	timer = new ntTimer();
	*timer = *a.timer;
	name = a.name;
	url = a.url;
	return *this;
}

ntUIBlock::~ntUIBlock()
{
	SDL_FreeSurface(imagep);
	timer->stop();
	delete timer;
}

void ntUIBlock::setimage(SDL_Surface* p)
{imagep = p;}

void ntUIBlock::settime(int t)
{timer_s = t;}

void ntUIBlock::setcoords(int x, int y)
{coord_x = x; coord_y = y;}

void ntUIBlock::settype(int t)
{type = t;}

void ntUIBlock::setstate(int t)
{state = t;}

void ntUIBlock::setname(std::string n)
{name = n;}

void ntUIBlock::seturl(std::string u)
{url = u;}

void ntUIBlock::setsize(int w, int h)
{width = w; height = h;}

void ntUIBlock::setrect(SDL_Rect&r)
{rect=r;}

void ntUIBlock::setrender(bool a)
{shouldrender = a;}

std::string ntUIBlock::getCountDown()
{
	int hours = 0, minutes = 0, dif = 0;
	
	if(timer_s == -1)
	dif = floor(timer->get_ticks()/1000.0);
	else
	{
		dif = timer_s - floor(timer->get_ticks()/1000.0);

		if(dif <= 0)
		{
			setstate(0);
			timer->stop();
		}
	}
	while(dif >= 3600)
	{
		hours++;
		dif-= 3600;
	}
	while(dif >= 60)
	{
		minutes++;
		dif -= 60;
	}
	return nt_util::num2string2(hours) + ":" + nt_util::num2string2(minutes) + ":" + nt_util::num2string2(dif);
}