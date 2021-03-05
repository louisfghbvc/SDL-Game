/*
 * sly.cpp
 *
 *  Created on: 2017¦~6¤ë11¤é
 *      Author: ASUS
 */

#include "..\header\SDLtool.h"
#include "..\header\middlemonster.h"

SDL_Surface *SP=NULL;
SDL_Surface *SP_A=NULL;
SDL_Surface *SPhand=NULL;
SDL_Surface *SPhandm=NULL;
extern SDL_Surface *screen;
SDL_Rect sp[2];
SDL_Rect sp_a[2];
SDL_Rect sphand[2];
SDL_Rect sphandm;

sly::sly(int x,int y){
	place.x=x;
	place.y=y;
	place.w=120;
	place.h=150;
	handplace.w=34;
	handplace.h=14;
	handmplace.w=60;
	handmplace.h=22;
	atkcd=0;
	Hp=5;
	Hpflag=1;
	timecnt=0;
	v=2;
	hv=20;
	status=1;
	hd=0;
	status3=1;
	set_sly_clips();
}
void sly::load_sly_files(){
	SP=load_image_alpha(".\\middle\\sly\\SP.png");
	SP_A=load_image_alpha(".\\middle\\sly\\SP_A.png");
	SPhand=load_image_alpha(".\\middle\\sly\\SP_hand_t.png");
	SPhandm=load_image_alpha(".\\middle\\sly\\SP_hand_m.png");
}
void sly::set_sly_clips(){
	int i;
	for(i=0;i<2;++i){
		sp[i].x=0;
		sp[i].y=i*150;
		sp[i].w=120;
		sp[i].h=150;
		sp_a[i].x=0;
		sp_a[i].y=i*150;
		sp_a[i].w=120;
		sp_a[i].h=150;
		sphand[i].x=0;
		sphand[i].y=22*i;
		sphand[i].w=60;
		sphand[i].h=22;
	}
		sphandm.x=0;
		sphandm.y=0;
		sphandm.w=34;
		sphandm.h=14;
}
void sly::cleanup(){
	SDL_FreeSurface(SP);
	SDL_FreeSurface(SP_A);
	SDL_FreeSurface(SPhand);
	SDL_FreeSurface(SPhandm);
}
void sly::slymove(SDL_Rect SB){
	if(SB.x<place.x)
		status=0;
	else
		status=1;
	if(status)
		place.x+=v;
	else
		place.x-=v;
}
void sly::movehamdt(){
	if(hd){
		handplace.x+=hv;
	}
	else
		handplace.x-=hv;
	if(handplace.x<0||handplace.x+handplace.w>SCREEN_WIDTH)
		status3=0;

}
void sly::show(){
	if(status3){
		if(status){
			apply_surface(place.x,place.y,SP_A,screen,&sp_a[1]);
			showhandt();
		}
		else{
			apply_surface(place.x,place.y,SP_A,screen,&sp_a[0]);
			showhandt();
		}
	}
	else{
		if(status){
		apply_surface(place.x,place.y,SP,screen,&sp[1]);
	}
	else{
		apply_surface(place.x,place.y,SP,screen,&sp[0]);
		}
	}
}
void sly::showhandt(){
	//int cd;
	if(hd){
	apply_surface(handplace.x,handplace.y,SPhand,screen,&sphand[1]);
	movehamdt();
	/*handmplace.x=handplace.x;
	handmplace.y=handplace.y+8;
	for(cd=0;cd<=5;++cd){
		handmplace.x-=34;
		showhandm();
		}*/
	}
	else{
	apply_surface(handplace.x,handplace.y,SPhand,screen,&sphand[0]);
	movehamdt();
	/*handmplace.x=handplace.x;
	handmplace.y=handplace.y+8;
	for(cd=0;cd<=5;++cd){
		handmplace.x+=34;
		showhandm();
		}*/
	}
}
void sly::showhandm(){
	if(status){
	apply_surface(handmplace.x,handmplace.y,SPhandm,screen,&sphandm);
	}
	else{
	apply_surface(handmplace.x,handmplace.y,SPhandm,screen,&sphandm);
	}
}
bool sly::isDead(){
	if(Hp<=0)
		return true;
	else
		return false;
}
bool sly::beattack(SDL_Rect thing){
	if(place.y<=(thing.y+thing.h)&&(thing.y-place.y)<=middle_HEIGHT){
		if(thing.x<=(place.x+place.w)&&thing.x>=place.x)
			return true;
		if(place.x<=(thing.x+thing.w)&&place.x>=thing.x)
			return true;
	}
	return false;
}
void sly::HandleHP(SDL_Rect bad){
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
void sly::handleFB(){
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
void sly::handlebat(){
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
void sly::Hptime(){
	if(timecnt>=10)
	{
		timecnt=0;
		Hpflag=1;
	}
	timecnt++;
	if(atkcd>=30){
		status3=1;
		if(status){
			hd=status;
		handplace.x=place.x+50;
		handplace.y=place.y+75;
		}
		else{
			hd=status;
			handplace.x=place.x+10;
			handplace.y=place.y+75;
		}
		atkcd=0;
	}
	atkcd++;
}
