#pragma once
#ifndef nt_WEB_H_INCLUDED
#define nt_WEB_H_INCLUDED

#include <string>

namespace nt_webtools
{
	int open_webpage(std::string&);
	std::wstring s2ws(const std::string&);
	void positionwindow();
	void positionwindow(int,int);
}

#endif