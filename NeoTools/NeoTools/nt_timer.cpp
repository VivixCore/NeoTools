#include "nt_timer.h"
#include "nt_sdl.h"

ntTimer::ntTimer()
{
	startTicks=0;
	pausedTicks=0;
	paused=false;
	started=false;
}

//copy constructor
ntTimer::ntTimer(const ntTimer& a)
{
	startTicks=a.startTicks;
	pausedTicks=a.pausedTicks;
	paused=a.paused;
	started=a.started;
}

//equal2
ntTimer& ntTimer::operator = (const ntTimer& a)
{
	startTicks=a.startTicks;
	pausedTicks=a.pausedTicks;
	paused=a.paused;
	started=a.started;
	return *this;
}

void ntTimer::start()
{
	started=true;
	paused=false;
	startTicks=SDL_GetTicks();
}

void ntTimer::stop()
{
	started=false;
	paused=false;
}

int ntTimer::get_ticks()
{
	if(started==true)
	{
		if(paused==true)
		{
			return pausedTicks;
		}
		else
		{
			return SDL_GetTicks()-startTicks;
		}
	}
	return 0;
}

void ntTimer::pause()
{
	if( (started==true) && (paused==false) )
	{
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void ntTimer::unpause()
{
	if(paused==true)
	{
		paused=false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

bool ntTimer::is_started()
{
	return started;
}

bool ntTimer::is_paused()
{
	return paused;
}