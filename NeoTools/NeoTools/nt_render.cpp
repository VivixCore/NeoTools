#include "nt_render.h"
#include "nt_sdl.h"
#include "nt_ui.h"
#include "nt_uiblock_types.h"
#include "nt_util.h"

int nt_render::y_offset_global = 0;
int nt_render::y_offset_global_last = 0;
int nt_render::y_offset_mousewheel = 0;

//will probably need this later
//#include <ctime>
//std::time_t t = std::time(0);

void nt_render::render()
{
	//SDL_FillRect(ntSDL::screen,&ntSDL::nullrect,255);
	//ntSDL::apply_surface(0,0,nt_ui::iconsystem[0]->imagep,ntSDL::screen,&ntSDL::nullrect);
	/*
	int x;
	Rest in peace easyrender
	for(x=0;x<nt_ui::iconblocks.size();x++)
	{
		drawblock(nt_ui::iconblocks[x]);
	}
	*/

	y_offset_global = 0;
	std::list<std::vector<ntUIBlock*>>::iterator i=nt_ui::blockcategories.begin();
	//skip bg
	i++;
	y_offset_global -= i->at(0)->height;
	i--;
	
	for(i;i!=nt_ui::blockcategories.end();++i)
	{
		int x;
		int dif = 0, d = 0;
		ntUIBlock* a;
		for(x=0;x<i->size();x++)
		{
			a = i->at(x);
			if(x==0)
			{
				drawblock(a);
				a->timer_s = y_offset_global;
			}
			else if(a->shouldrender)
			{
				drawblock(a);
				d = a->coord_y + a->height - i->at(0)->height;
				if(d > dif)
				dif = d;
			}
			else break;
		}
		y_offset_global += dif;
	}
	if(y_offset_global != y_offset_global_last)
	{
		int smaller = nt_ui::maxwindowheight;
		int z = (y_offset_global + nt_ui::blockcategories.begin()->at(0)->height);
		int newheight = smaller;
		if(smaller > z)
		newheight = z;

		ntSDL::resizeScreen(ntSDL::SCREEN_WIDTH,ntSDL::SCREEN_HEIGHT=newheight);

		//pain in my fucking ass
		if(y_offset_global_last > y_offset_global)
		{
			int dif = y_offset_global_last - y_offset_global;
			y_offset_mousewheel += dif;
			if(nt_render::y_offset_mousewheel > 0)
			nt_render::y_offset_mousewheel = 0;
		}
		y_offset_global_last = y_offset_global;
	}
	SDL_Flip(ntSDL::screen);
}

void nt_render::drawblock(ntUIBlock* b)
{
	using namespace ntUIBlockTypes;

	switch(b->type)
	{
		case TYPE_BANNER:
		{
			y_offset_global += b->height;//nt_ui::bannerheight;
			//apply surface
			ntSDL::apply_surface(b->coord_x,b->coord_y+y_offset_global+y_offset_mousewheel,b->imagep,ntSDL::screen,&ntSDL::nullrect);
			break;
		}
		case TYPE_X_DAILY:
		case TYPE_TIMER:
		case TYPE_METEOR:
		case TYPE_ICON:
		case TYPE_ABOUT:
		case TYPE_RESET:
		case TYPE_GAME:
		{
			//apply it
			ntSDL::apply_surface(b->coord_x,b->coord_y+y_offset_global+y_offset_mousewheel,b->imagep,ntSDL::screen,&ntSDL::nullrect);
			break;
		}
		case TYPE_SYSTEM_BG:
		{
			//fillrect that bad-boy with some 0,0,0
			SDL_FillRect(ntSDL::screen,NULL,0xFF000000);
			break;
		}
		case TYPE_SYSTEM_CHECKBOX:
		case TYPE_SYSTEM_CHECKBOX_BONUS:
		{
			//apply it
			ntSDL::apply_surface(b->coord_x,b->coord_y+y_offset_global+y_offset_mousewheel,b->imagep,ntSDL::screen,&b->rect);
			break;
		}
		case TYPE_SYSTEM_TIMER:
		{
			//apply it
			ntSDL::apply_surface(b->coord_x,b->coord_y+y_offset_global+y_offset_mousewheel,b->imagep,ntSDL::screen,&ntSDL::nullrect);

			//this belongs in the system timer
			SDL_Surface* textMsg = TTF_RenderText_Solid(ntSDL::font,b->getCountDown().c_str(),ntSDL::fontcolor);
			ntSDL::apply_surface(b->coord_x + b->width + 3,b->coord_y+y_offset_global+y_offset_mousewheel,textMsg,ntSDL::screen,&ntSDL::nullrect);
			if(textMsg)
			SDL_FreeSurface(textMsg);
			break;
		}
		default:
		{
			break;
		}
	}
}