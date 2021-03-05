/*
 * umo.cpp
 *
 *  Created on: 2017¦~6¤ë4¤é
 *      Author: ASUS
 */

#include "..\header\SDLtool.h"
#include "..\header\middlemonster.h"
#include "..\header\umo_rock.h"
#include <time.h>

const int rock_WIDTH=65;
const int rock_HEIGHT=70;

SDL_Rect clipsumoatk[2];
SDL_Rect clipsumostand[2];
SDL_Rect cliprock;
SDL_Surface *rock=NULL;
SDL_Surface *umoatk=NULL;
SDL_Surface *umostand=NULL;

extern SDL_Surface *screen;

void umo::load_umo_files(){
	rock=load_image_alpha(".\\middle\\umo\\rock.png");
	umoatk=load_image_alpha(".\\middle\\umo\\TM_A.png");
	umostand = load_image_alpha(".\\middle\\umo\\TM.png");
}
void umo::cleanup(){
	SDL_FreeSurface(rock);
	SDL_FreeSurface(umoatk);
	SDL_FreeSurface(umostand);
}
void umo::set_umo_clips(){
	int i;
	for(i=0;i<2;++i)
	{
		clipsumoatk[i].x=0;
		clipsumoatk[i].y=i*middle_HEIGHT;
		clipsumoatk[i].w=middle_WIDTH;
		clipsumoatk[i].h=middle_HEIGHT;
		clipsumostand[i].x=0;
		clipsumostand[i].y=i*middle_HEIGHT;
		clipsumostand[i].w=middle_WIDTH;
		clipsumostand[i].h=middle_HEIGHT;
	}
	cliprock.x=0;
	cliprock.y=0;
	cliprock.w=rock_WIDTH;
	cliprock.h=rock_HEIGHT;
}
umo::umo(int x, int y){
	place.x=x;
	place.y=y;
	place.w=middle_WIDTH;
	place.h=middle_HEIGHT;
	status=1;
	status3=0;
	v=0;
	hv=0;
	atkcd=0;
	Hp=7;
	Hpflag=0;
	timecnt=0;
	set_umo_clips();
}
void umo::umomove(){
	srand(time(NULL));
	int i=rand()%4;
	if(status3==0){
			switch(i){
	case 0:
		status=1;
		v=middle_WIDTH/20;
		break;
	case 1:
		status=0;
		v=-middle_WIDTH/20;
		break;
	case 2:
		hv=middle_HEIGHT/20;
		break;
	case 3:
		hv=-middle_HEIGHT/20;
		break;
			}
	place.x+=v;
	place.y+=hv;
	if(place.x+middle_WIDTH>SCREEN_WIDTH||place.x<0)
		place.x-=v;
	if(place.y<0||place.y+middle_HEIGHT>SCREEN_HEIGHT)
		place.y-=hv;
	}
}
void umo::show(){
	if(status3==1&&status==1){
		apply_surface(place.x,place.y,umoatk,screen,&clipsumoatk[0]);
	}
	else if(status3==1&&status==0){
		apply_surface(place.x,place.y,umoatk,screen,&clipsumoatk[1]);
	}
	else if(status3==0&&status==1)
		apply_surface(place.x,place.y,umostand,screen,&clipsumostand[0]);
	else if(status3==0&&status==0)
		apply_surface(place.x,place.y,umostand,screen,&clipsumostand[1]);

}
void umo::showrock(){
	apply_surface(a.rplace.x,a.rplace.y,rock,screen,&cliprock);
	a.rplace.y+=a.g;
	if(a.rplace.y+rock_HEIGHT>SCREEN_HEIGHT)
	{
		a.rockdown=0;
		a.rplace.y=0;
		status3=0;
	}
	a.g+=10;
}
void umo::moverock(){
    atkcd++;
	if(atkcd==45){
		atkcd=0;
		a.rockdown=1;
		status3=1;
		a.g=0;
	}
}
bool umo::beattack(SDL_Rect thing){
	if(place.y<=(thing.y+thing.h)&&(thing.y-place.y)<=middle_HEIGHT){
		if(thing.x<=(place.x+place.w)&&thing.x>=place.x)
			return true;
		if(place.x<=(thing.x+thing.w)&&place.x>=thing.x)
			return true;
	}
	return false;
}
void umo::HandleHP(SDL_Rect bad){
    if(beattack(bad)==true){
    	if(status==0)
    		place.x+=15;
    	else
    		place.x-=15;
    	if(place.x<0)
    		place.x+=15;
    	else if(place.x+middle_WIDTH>SCREEN_WIDTH)
    		place.x-=15;
    	if(Hpflag==1)
    		{
    		Hp--;
    		Hpflag=0;
    		}
    }
}
void umo::handleFB(){
	Hp--;
	if(status==0)
		place.x+=15;
	else
		place.x-=15;
	if(place.x<0)
		place.x+=15;
	else if(place.x+middle_WIDTH>SCREEN_WIDTH)
		place.x-=15;
}
void umo::handlebat(){
	Hp--;
	if(status==0)
		place.x+=15;
	else
		place.x-=15;
	if(place.x<0)
		place.x+=15;
	else if(place.x+middle_WIDTH>SCREEN_WIDTH)
		place.x-=15;
}
void umo::Hptime(){
	if(timecnt==10){
    	Hpflag=1;
    	timecnt=0;
    }
    timecnt++;
}
bool umo::isDead(){
	if(Hp<=0)
		return true;
	else
		return false;
}
umo_rock::umo_rock(){
	rplace.w=rock_WIDTH;
	rplace.h=rock_HEIGHT;
	rockdown=0;
	g=0;
}
void umo_rock::setplace(SDL_Rect th){
	rplace.x=th.x;
	rplace.y=0;
}
