#include "nt_sdl.h"
#include "nt_event.h"
#include "nt_timer.h"
#include "nt_render.h"
#include "nt_ui.h"
#include "nt_openweb.h"
#include "_Resource.h"

int pleaseGiveUp = 0;

int main(int argc, char *argv[])
{
	pleaseGiveUp = ntSDL::initSDL();
	nt_webtools::positionwindow();

	nt_ui::load_settings();
	nt_ui::build_ui();
	
	if(!pleaseGiveUp)
	pleaseGiveUp = ntSDL::initFonts();

	SDL_Event e;

	while(pleaseGiveUp==0)
	{
		SDL_Delay(1000/30);
		{
			while(SDL_PollEvent( &e ) && pleaseGiveUp==false)
			pleaseGiveUp=ntEvent::handle_event(e);

			nt_render::render();
		}
	}

	nt_ui::save_settings();
	ntSDL::ntSDLShutdown();

	if(!~pleaseGiveUp)
	pleaseGiveUp=0;

	return pleaseGiveUp;
}