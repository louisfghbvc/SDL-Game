/*
 * mato.cpp
 *
 *  Created on: 2017¦~6¤ë8¤é
 *      Author: ASUS
 */

#include "..\header\SDLtool.h"
#include "..\header\middlemonster.h"
#include "..\header\SDL_rotozoom.h"

SDL_Rect clipmato;
SDL_Surface *matopic=NULL;
extern SDL_Surface *screen;

mato::mato(int x, int y){
	place.x=x;
	place.y=y;
	place.w=middle_WIDTH;
	place.h=middle_WIDTH;
	status=1;
	angle=0;
	v=20;
	set_clips();
}
void mato::load_mato_flies(){
	matopic=load_image_alpha(".//middle//mato//md.png");
}
void mato::set_clips(){
	clipmato.x=0;
	clipmato.y=0;
	clipmato.w=240;
	clipmato.h=240;
}
void mato::move(){
	if(status==1)
	{
		angle-=30;
		place.x+=v;
	}
	else{
		angle+=30;
		place.x-=v;
	}
	if(angle>=360)
		angle-=360;
	else if(angle<0)
		angle+=360;
	if((place.x+place.w)>SCREEN_WIDTH-150)
	{
		place.x-=v;
		if(status)
			status=0;
		v*=1.5;
	}
	else if(place.x<150)
	{
		place.x+=v;
		if(status==0)
			status=1;
		v*=1.5;
	}
	if(v>=200)
		v=200;
}
void mato::show(){
	apply_surface(place.x,place.y,rotozoomSurface(matopic,angle,1.0,0),screen,NULL);
}
void mato::cleanup(){
	SDL_FreeSurface(matopic);
}
