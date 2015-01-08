#include "nt_openweb.h"
#include <windows.h>
#include "nt_sdl.h"

//source: http://stackoverflow.com/questions/27220/how-to-convert-stdstring-to-lpcwstr-in-c-unicode
std::wstring nt_webtools::s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

void nt_webtools::positionwindow()
{
	HWND a = FindWindow(NULL,s2ws(ntSDL::windowtitle).c_str());
	MoveWindow
	(
		a, 
		0,
		0, 
		0, 
		0, 
		1
	);
}

void nt_webtools::positionwindow(int x, int y)
{
	HWND a = FindWindow(NULL,s2ws(ntSDL::windowtitle).c_str());
	MoveWindow
	(
		a, 
		x,
		y, 
		0, 
		0, 
		1
	);
}

int nt_webtools::open_webpage(std::string& dest)
{
	return (int)ShellExecute(NULL, L"open", s2ws(dest).c_str(), NULL, NULL, SW_SHOWNORMAL);
}