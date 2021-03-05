/*
 * skymo.cpp
 *
 *  Created on: 2017¦~6¤ë8¤é
 *      Author: ASUS
 */
#include "..\header\middlemonster.h"
#include "..\header\SDLtool.h"

SDL_Surface *skymopic=NULL;
SDL_Surface *skymoatk=NULL;
SDL_Surface *skymos=NULL;
extern SDL_Surface *screen;
SDL_Rect skymoclips[2];
SDL_Rect skymoatkclipsR[5];
SDL_Rect skymoatkclipsL[5];
SDL_Rect red;

skymo::skymo(int x,int y){
	place.x=x;
	place.y=y;
	place.w=middle_WIDTH;
	place.h=middle_HEIGHT;
	shplace.w=130;
	shplace.h=120;
	Hp=2;
	Hpflag=1;
	status=1;//1 right 0 left
	status2=0;//1 atk
	timecnt=0;
	cd=0;
	frame=0;
	shstatus=0;
	atkt=0;
	set_clips();
}
void skymo::load_skymo_files(){
	skymopic = load_image_alpha(".\\middle\\skymo\\TM_S.png");
	skymoatk = load_image_alpha(".\\middle\\skymo\\TM_A.png");
	skymos = load_image_alpha(".\\middle\\skymo\\devilshield.png");
}
void skymo::set_clips(){
	int i;
	for(i=0;i<2;++i){
		skymoclips[i].x=0;
		skymoclips[i].y=middle_HEIGHT*i;
		skymoclips[i].w=middle_WIDTH;
		skymoclips[i].h=middle_HEIGHT;
	}
	for(i=0;i<5;++i){
		skymoatkclipsL[i].x=middle_WIDTH*i;
		skymoatkclipsL[i].y=0;
		skymoatkclipsL[i].w=middle_WIDTH;
		skymoatkclipsL[i].h=middle_HEIGHT;
		skymoatkclipsR[i].x=middle_WIDTH*i;
		skymoatkclipsR[i].y=middle_HEIGHT;
		skymoatkclipsR[i].w=middle_WIDTH;
		skymoatkclipsR[i].h=middle_HEIGHT;
	}
	red.x=0;
	red.y=0;
	red.w=130;
	red.h=120;
}
void skymo::cleanup(){
	SDL_FreeSurface(skymopic);
	SDL_FreeSurface(skymoatk);
}
bool skymo::beattack(SDL_Rect thing){
	if(place.y<=(thing.y+thing.h)&&(thing.y-place.y)<=middle_HEIGHT){
		if(thing.x<=(place.x+place.w)&&thing.x>=place.x)
			return true;
		if(place.x<=(thing.x+thing.w)&&place.x>=thing.x)
			return true;
	}
	return false;
}
void skymo::showpic(SDL_Rect peo){
	if(peo.x<place.x)
		status=0;
	else
		status=1;
	if(status2==0){
		if(status)
			apply_surface(place.x,place.y,skymopic,screen,&skymoclips[1]);
		else
			apply_surface(place.x,place.y,skymopic,screen,&skymoclips[0]);
	}
	else{
		if(status)
			apply_surface(place.x,place.y,skymoatk,screen,&skymoatkclipsR[frame]);
		else
			apply_surface(place.x,place.y,skymoatk,screen,&skymoatkclipsL[frame]);
		frame++;
		if(frame>=4){
			frame=0;
			status2=0;
			shstatus=1;
			shplace.x=peo.x;
			shplace.y=peo.y;
			atkt=0;
		}
	}
	if(shstatus){
		apply_surface(shplace.x,shplace.y,skymos,screen,&red);
		atkt++;
	}

}
void skymo::HandleHp(SDL_Rect bad){
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
void skymo::handleFB(){
	Hp--;
}
void skymo::handlebat(){
	Hp--;
}
void skymo::sometime(){
	if(timecnt==10){
    	Hpflag=1;
    	timecnt=0;
    }
    timecnt++;
    if(cd==50){
    	status2=1;
    	cd=0;
    }
    cd++;
}
bool skymo::isDead(){
	if(Hp<=0)
		return true;
	else
		return false;
}
