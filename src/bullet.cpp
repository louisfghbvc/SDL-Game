/*
 * bullet.cpp
 *
 *  Created on: 2017¦~6¤ë4¤é
 *      Author: ASUS
 */

#include "..\header\shootbullet.h"
#include "..\header\SDLtool.h"
SDL_Surface *bulletpic = NULL;
extern SDL_Surface *screen;

bullet::bullet(){
	cd=0;
	v=40;
	shoot=0;
	direct=1;
	bulletplace.w=45;
	bulletplace.h=5;
	clipbullet.x=0;
	clipbullet.y=0;
	clipbullet.w=45;
	clipbullet.h=5;
}
void bullet::dofixx(){
	if(direct==1){
		bulletplace.x+=111+v;
		bulletplace.y+=60;
	}
	else{
		bulletplace.x-=v;
		bulletplace.y+=60;
	}

}
void bullet::undofixx(){
	if(direct==1){
		bulletplace.x-=111;
		bulletplace.y-=60;
	}
	else{
		bulletplace.y-=60;
	}
	cd++;
	if(cd>=6){
		cd=0;
		shoot=0;
	}
}
void bullet::showbullet(){
	if(direct==1){
		apply_surface(bulletplace.x, bulletplace.y, bulletpic, screen, &clipbullet);
	}
	else{
		apply_surface(bulletplace.x,bulletplace.y ,bulletpic ,screen ,&clipbullet);
	}
}
void bullet::load_bullet(){
    bulletpic = load_image_alpha(".\\SB\\shoot2.png");
}
void bullet::cleanup(){
    SDL_FreeSurface( bulletpic );
}
