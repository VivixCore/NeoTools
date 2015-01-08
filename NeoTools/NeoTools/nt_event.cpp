#include "nt_event.h"
#include "nt_ui.h"
#include "nt_openweb.h"
#include "nt_util.h"
#include "nt_uiblock_types.h"
#include "nt_render.h"

#include <fstream>
#include <Windows.h>

int ntEvent::handle_event(SDL_Event e)
{
	using namespace ntSDL;
	using namespace ntUIBlockTypes;
	int out = 0;
	//Things that always need to happen
	if(e.type == SDL_QUIT)
	{
		out=-1;
	}
	else if(e.type == SDL_VIDEORESIZE)
	{
		ntSDL::resizeScreen(ntSDL::SCREEN_WIDTH = e.resize.w,ntSDL::SCREEN_HEIGHT = e.resize.h);
	}
	else if(e.type == SDL_MOUSEMOTION)
	{
		//mouse.set(e.motion.x,e.motion.y);
	}
	else if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		//mouse.set(e.button.x,e.button.y);
		if(e.button.button==SDL_BUTTON_LEFT)
		{
			std::list<std::vector<ntUIBlock*>>::iterator i;

			//skip the bg
			i = nt_ui::blockcategories.begin();
			i++;

			for(i;i!=nt_ui::blockcategories.end();i++)
			{
				int x;int globalyoffset;
				for(x=0;x<i->size();x++)
				{
					ntUIBlock* b = i->at(x);

					//re-use the timer_s variable since banners have it but don't need it
					if(x==0)
					globalyoffset = b->timer_s;

					if
					(
						((e.button.x < (b->coord_x + b->width)) && (e.button.y < (b->coord_y + b->height + globalyoffset + nt_render::y_offset_mousewheel)))&&
						((e.button.x > b->coord_x) && (e.button.y > b->coord_y + globalyoffset + nt_render::y_offset_mousewheel))&&
						((b->shouldrender) || (b->type==TYPE_BANNER))
					
					)
					{
						//ntSDL::vcSetWindowTitle(b->name);

						if(b->url!="")
						{
							if(b->type==TYPE_ABOUT)
							{
								//windows platform specific
								TCHAR buf[2048];
								DWORD dwRet = GetModuleFileName(NULL,buf,2048);
								std::wstring herp(buf);
								std::string derp(herp.begin(),herp.end());
								int lol = derp.find_last_of("\\");
								derp = std::string(0,lol);
								nt_webtools::open_webpage((std::string)derp + b->url);
							}
							else
							nt_webtools::open_webpage(b->url);
						}

						if(b->type==TYPE_SYSTEM_TIMER)
						{
							//ntSDL::vcSetWindowTitle("WOT");
							if(b->timer->is_started())
							b->timer->stop();
							else
							b->timer->start();
						}
						else if(b->type==TYPE_SYSTEM_CHECKBOX || b->type==TYPE_SYSTEM_CHECKBOX_BONUS)
						{
							b->setstate(!b->state);
							b->rect.x = b->width*b->state;
						}
						else if(b->type==TYPE_SETTING_BOOL)
						{

						}
						else if(b->type==TYPE_BANNER)
						{
							bool io = b->shouldrender;
							while(x<i->size())
							{
								b=i->at(x);
								b->setrender(!io);
								x++;
							}
						}
						else if(b->type==TYPE_RESET)
						{
							//ntSDL::vcSetWindowTitle("ASDF");
							std::list<std::vector<ntUIBlock*>>::iterator cats;

							//skip the bg
							cats = nt_ui::blockcategories.begin();
							cats++;

							for(cats;cats!=nt_ui::blockcategories.end();cats++)
							{
								int cx;
								for(cx=0;cx<cats->size();cx++)
								{
									/*
									ntSDL::vcSetWindowTitle(nt_util::num2string(cx));
									SDL_Delay(300);
									*/

									ntUIBlock* xb = cats->at(cx);
									switch(xb->type)
									{
										case TYPE_SYSTEM_CHECKBOX:
										case TYPE_SYSTEM_CHECKBOX_BONUS:
										{
											xb->setstate(false);
											xb->rect.x = xb->width*xb->state;
										}
										//case TYPE_SYSTEM_TIMER:
										//xb->timer->stop();
										default:
										break;
									}
								}
							}
						}
						//we're done
						return out;
					}
				}
			}
		}
		else if
		(
			((e.button.button==SDL_BUTTON_WHEELUP)&&(nt_ui::invertmousescroll==false))||
			((e.button.button==SDL_BUTTON_WHEELDOWN)&&(nt_ui::invertmousescroll==true))
		)
		{
			if(nt_render::y_offset_mousewheel <= 0)
			nt_render::y_offset_mousewheel += nt_ui::mousescrollrate;

			if(nt_render::y_offset_mousewheel > 0)
			nt_render::y_offset_mousewheel = 0;
		}
		else if
		(
			((e.button.button==SDL_BUTTON_WHEELDOWN)&&(nt_ui::invertmousescroll==false))||
			((e.button.button==SDL_BUTTON_WHEELUP)&&(nt_ui::invertmousescroll==true))
		)
		{
			if((nt_render::y_offset_global_last) > (nt_ui::maxwindowheight-nt_render::y_offset_mousewheel-nt_ui::mousescrollrate))
			nt_render::y_offset_mousewheel -= nt_ui::mousescrollrate;
		}
	}
	//press button
	else if(e.type == SDL_KEYDOWN)
	{
		switch( e.key.keysym.sym)
		{
			case SDLK_f:
			{
			}
			break;
		}
	}
	//release button
	else if(e.type == SDL_KEYUP)
	{
		switch( e.key.keysym.sym)
		{
			case SDLK_f:
			{
			}
			break;
		}
	}
	return out;
}