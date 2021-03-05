/*
 * useplace.cpp
 *
 *  Created on: 2017¦~6¤ë4¤é
 *      Author: ASUS
 */
#include "..\header\SDLtool.h"
#include "..\header\SDL_rotozoom.h"
#include "..\header\useplace.h"
#include "..\header\map.h"

SDL_Surface *proppic = NULL;
SDL_Surface *bookpic=NULL;
SDL_Surface *erapic=NULL;
SDL_Surface *woodpic=NULL;
SDL_Surface *sheild=NULL;

SDL_Rect clipsprop;
SDL_Rect clipskey;
SDL_Rect cbook;
SDL_Rect cera;
SDL_Rect cwood;
SDL_Rect csheild;

extern SDL_Surface *screen;
extern SDL_Surface *key_image[9];
extern SDL_Rect key_clips[8];

void useplace::setclips(){
	clipsprop.x=0;
	clipsprop.y=0;
	clipsprop.w=90;
	clipsprop.h=70;
	clipskey.x=90;
	clipskey.y=0;
	clipskey.w=320;
	clipskey.h=70;
	cbook.x=0;
	cbook.y=0;
	cbook.w=70;
	cbook.h=70;
	cera.x=0;
	cera.y=0;
	cera.w=55;
	cera.h=70;
	cwood.x=0;
	cwood.y=0;
	cwood.w=40;
	cwood.h=70;
	csheild.x=0;
	csheild.y=0;
	csheild.w=130;
	csheild.h=120;
	which=-1;
	int i;
	for(i=0;i<4;++i)
		keynum[i]=-1;
}
void useplace::showkey(){
	int i;
	for(i=0;i<4;++i)
	{
		if(keynum[i]!=-1)
			apply_surface(SCREEN_WIDTH-310+i*80,30, rotozoomSurface(key_image[keynum[i]],0,2.0,0), screen, NULL);
	}
}
void useplace::showplace(){
	apply_surface(SCREEN_WIDTH-410,0, proppic, screen, &clipsprop);
	apply_surface(SCREEN_WIDTH-320,0, proppic, screen, &clipskey);
	showuseprop();
	showkey();
}

void useplace::showuseprop(){
	switch(which){
	case 0:
		apply_surface(SCREEN_WIDTH-400,0, bookpic, screen, &cbook);
		break;
	case 1:
		apply_surface(SCREEN_WIDTH-400,0, erapic, screen, &cera);
		break;
	case 2:
		apply_surface(SCREEN_WIDTH-390,0, woodpic, screen, &cwood);
		break;
	}
}
bool useplace::loadprop(){
    proppic =load_image_alpha(".\\SB\\thingplace.png");
    woodpic = load_image_alpha(".\\SB\\cmstc.png");
    erapic = load_image_alpha(".\\SB\\eraise.png");
    bookpic = load_image_alpha(".\\SB\\FB.png");
    sheild =load_image_alpha(".\\SB\\shield.png");
    if(proppic==NULL)
    	return false;
	return true;
}
void useplace::cleanup(){
    SDL_FreeSurface( proppic );
    SDL_FreeSurface( bookpic );
    SDL_FreeSurface( erapic );
    SDL_FreeSurface( woodpic );
    SDL_FreeSurface( sheild );
}
magicbook::magicbook(int x,int y){
	place.x=x;
	place.y=y;
	place.w=70;
	place.h=70;
	flag=1;
}
void magicbook::showbook(int x,int y){
	apply_surface(x,y, bookpic, screen, NULL);
	place.x=x;
	place.y=y;
}
bool magicbook::touch(int x,int y){
	if(place.y<=(y+120)&&(y-place.y)<=70){
		if(x<=(place.x+place.w)&&x>=place.x)
			return true;
		if(place.x<=(x+80)&&place.x>=x)
			return true;
	}
	return false;
}
ziaboo::ziaboo(int x,int y){
	place.x=x;
	place.y=y;
	place.w=55;
	place.h=70;
	flag=1;
}
void ziaboo::showziaboo(){
		apply_surface(place.x,place.y, erapic, screen, &cera);
}
bool ziaboo::touch(SDL_Rect man){
	if(place.y<=(man.y+man.h)&&(man.y-place.y)<=70){
		if(man.x<=(place.x+place.w)&&man.x>=place.x)
			return true;
		if(place.x<=(man.x+man.w)&&place.x>=man.x)
			return true;
	}
	return false;
}
powerbat::powerbat(int x,int y){
	place.x=x;
	place.y=y;
	place.w=40;
	place.h=70;
	flag=1;
}
void powerbat::showbat(){
	apply_surface(place.x,place.y, woodpic, screen, &cwood);
}
bool powerbat::touch(SDL_Rect man){
	if(place.y<=(man.y+man.h)&&(man.y-place.y)<=70){
		if(man.x<=(place.x+place.w)&&man.x>=place.x)
			return true;
		if(place.x<=(man.x+man.w)&&place.x>=man.x)
			return true;
	}
	return false;
}
