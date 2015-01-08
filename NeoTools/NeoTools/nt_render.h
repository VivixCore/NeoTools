#pragma once
#ifndef nt_RENDER_H_INCLUDED
#define nt_RENDER_H_INCLUDED

#include "nt_uiblock.h"

namespace nt_render
{
	extern int y_offset_global;
	extern int y_offset_global_last;
	extern int y_offset_mousewheel;
	void render();
	void drawblock(ntUIBlock*);
}

#endif