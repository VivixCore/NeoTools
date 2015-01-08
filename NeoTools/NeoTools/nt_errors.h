#pragma once
#ifndef ntErrors_H_INCLUDED
#define ntErrors_H_INCLUDED

namespace ntErrors
{
	extern const enum Errors
	{
		//SDL is broke
		ERROR_SDL_INIT = 1,
		//SDL also broke
		ERROR_SDL_SETVIDEOMODE = 2,
		//No icon file
		ERROR_ICON_MISSING = 3,
		//Font failed to init
		ERROR_FONT_INIT = 4,
		//Font missing
		ERROR_NO_FONT = 5,
		//Config settings file broken or missing
		ERROR_SETTINGS_CONFIG_BROKEN = 6,
		//Config ui file broken or missing
		ERROR_UI_CONFIG_BROKEN = 7,
		//Config for system icons/bg broken or missing
		ERROR_SYSTEM_UI_CONFIG_BROKEN = 8
	};
}

#endif