/*
 * boxmm.cpp
 *
 *  Created on: 2017¦~6¤ë10¤é
 *      Author: ASUS
 */

#include "..\header\SDLtool.h"
#include "..\header\middlemonster.h"

SDL_Rect clipbox;
SDL_Surface* boxpic=NULL;
extern SDL_Surface* screen;

minibox::minibox(int x,int y){
	place.x=x;
	place.y=y;
	place.w=100;
	place.h=100;
	status=1;
	set_bclips();
}
void minibox::load_box_flies(){
	boxpic=load_image_alpha(".//middle//mimi//minibox.png");
}
void minibox::set_bclips(){
	clipbox.x=0;
	clipbox.y=0;
	clipbox.w=100;
	clipbox.y=100;
}
void minibox::cleanup(){
	SDL_FreeSurface(boxpic);
}
void minibox::handle_boom(SDL_Rect){

}
void minibox::show(){
	if(status)
		apply_surface(place.x,place.y,boxpic,screen);
}
