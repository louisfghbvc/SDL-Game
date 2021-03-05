
/*
 * SDLtool.cpp
 *
 *  Created on: 2017¦~5¤ë25¤é
 *      Author: jason
 */
#include <iostream>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include "..\header\SDLtool.h"
SDL_Surface *screen = NULL;
SDL_Event event;

Timer::Timer()
{
	startTicks = 0;
}
void Timer::start(void)
{
	startTicks = SDL_GetTicks();
}
int Timer::getTicks(void)
{
	return (SDL_GetTicks() - startTicks);
}
SDL_Surface *load_image_alpha(string filename)
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str() );

    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        SDL_FreeSurface( loadedImage );
    }

    return optimizedImage;
}
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}
bool init(void)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return false;
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
	if(screen == NULL)
		return false;
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	    return false;
	SDL_WM_SetCaption( "Feld Des Gottlichen Wortes", NULL );
	return true;

}

