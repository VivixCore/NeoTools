#include "nt_sdl.h"
#include "nt_errors.h"
#include "nt_ui.h"

TTF_Font *ntSDL::font;
int ntSDL::fontsize = 12;
int ntSDL::fontoffset = 0;
SDL_Color ntSDL::fontcolor;
SDL_Surface *ntSDL::screen;
SDL_Rect ntSDL::nullrect;

std::string ntSDL::windowtitle = "NeoTools";
std::string ntSDL::fontname = "ORANGEKI.TTF";
int ntSDL::SCREEN_WIDTH = 192;
int ntSDL::SCREEN_HEIGHT = 640;
int ntSDL::SCREEN_BPP = 32;

//image loadering
SDL_Surface *ntSDL::load_image( std::string filename ) 
{ 
	//Temporary storage for the image that's loaded 
	SDL_Surface* loadedImage = NULL; 
	//The optimized image that will be used 
	SDL_Surface* optimizedImage = NULL;
	//Load the image
	loadedImage = IMG_Load(filename.c_str() );
	//If nothing went wrong in loading the image 
	if( loadedImage != NULL ) 
	{ 
		//Create an optimized image 
		optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
		/* TODO - map BMPs with explicit colors or something
		if(optimizedImage != NULL)
		{
			//Map the color key
			Uint32 colorkey = SDL_MapRGB(optimizedImage->format,0,0,0);
			//set all pixels of 0,0,0 to be transparent
			SDL_SetColorKey(optimizedImage,SDL_SRCCOLORKEY,colorkey);
		}*/
		//Free the old image 
		SDL_FreeSurface( loadedImage ); 
	}
	//return the converted image
	return optimizedImage;
}

//DRAW ENTITY
void ntSDL::apply_surface( int xoffset, int yoffset, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
{
	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;

	//give the sacrifices to the rectongle
	offset.x = xoffset;
	offset.y = yoffset;

	if(clip->x==-1)
		clip=NULL;

	//Blit the surface
	SDL_BlitSurface( source, clip, destination, &offset);
}

int ntSDL::initFonts()
{
	font = TTF_OpenFont(std::string("./Assets/Fonts/"+fontname).c_str(),fontsize);
	if(font!=NULL)
		return 0;
	return ntErrors::ERROR_NO_FONT;
}

void ntSDL::ntSDLShutdown()
{
	if(screen)
	SDL_FreeSurface(screen);
	//deconstruct the universe
	nt_ui::iconblocks.clear();
	nt_ui::iconsystem.clear();
	nt_ui::blockcategories.clear();
	SDL_Quit();
}
//hurp durp
void ntSDL::SetWindowTitle(std::string title)
{SDL_WM_SetCaption(title.c_str(),NULL);}

SDL_Surface* ntSDL::makeNewSurface(int w,int h)
{
	Uint32 rmask,gmask,bmask,amask;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif

	return SDL_CreateRGBSurface( SDL_HWSURFACE, w, h, ntSDL::SCREEN_BPP,rmask,gmask,bmask,amask );
}

//resizes SDL Surface
void ntSDL::resizeScreen(int w, int h)
{
	SDL_FreeSurface(screen);
	screen = SDL_SetVideoMode( SCREEN_WIDTH = w, SCREEN_HEIGHT = h, SCREEN_BPP, SDL_HWSURFACE /*| SDL_RESIZABLE */);
}

//BOOTS UP SDL
int ntSDL::initSDL()
{
	//turn on magic image render powers
	if(!~SDL_Init( SDL_INIT_EVERYTHING ))
	return ntErrors::ERROR_SDL_INIT;

	//set up our windowspace, sdl swsurface creates magic system memory
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE /*| SDL_RESIZABLE */);

	if(screen==NULL)
	return ntErrors::ERROR_SDL_SETVIDEOMODE;

	//set our window's title
	SDL_WM_SetCaption(windowtitle.c_str(),NULL);

	//set our null rect for future generations
	nullrect.x=-1;
	//load our font

	//font = TTF_OpenFont("./Assets/Fonts/ORANGEKI.TTF",12);
	if(!~TTF_Init())
	return ntErrors::ERROR_FONT_INIT;

	//TTF can be used at this point, we'll load the font up later when we've built the UI and gotten the font size settings

	return 0;
}