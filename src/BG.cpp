/*
 * BG.cpp
 *
 *  Created on: 2017¦~6¤ë7¤é
 *      Author: home
 */

#include "..\header\SDLtool.h"
#include "..\header\monster.h"
#include <time.h>

const int monster_WIDTH = 80;
const int monster_HEIGHT = 86;

//The direction status of the stick figure
const int monster_RIGHT = 0;
const int monster_LEFT = 1;
SDL_Surface *BG = NULL; 
SDL_Surface *BGA = NULL;
SDL_Surface *BGD = NULL;

SDL_Rect bg[2];
SDL_Rect bgA;
SDL_Rect bgD[2];

extern SDL_Surface *screen;

monster_BG::monster_BG(int x, int y)
{
    //Initialize movement variables
    place.x = x;
    place.y= y;
    place.w=80;
    place.h=86;
    handplace.x=x;
    handplace.y=y+27;
    handplace.w = 34;
    handplace.h = 14;
    hand_velocity = 0;
    Hp=3;
    Hpflag=1;
    timecnt=0;
    //Initialize animation variables
    status = monster_RIGHT;
    status2 = 0;
    cd=0;
    shoot=1;
    setclips();
}

void monster_BG::loadBG(){
    BG = load_image_alpha( ".\\smmon\\BG 80X86.png");
    BGA = load_image_alpha( ".\\smmon\\hand_A 34X14.png");
    BGD = load_image_alpha( ".\\smmon\\BG_D 80X86.png");
}
void monster_BG::setclips(){
    int i;
    for ( i = 0; i < 2; ++i)
    {
         bg[i].x = 0;
        bg[i].y = 86*i;
         bg[i].w = 80;
         bg[i].h = 86;
    }

         bgA.x = 0;
         bgA.y = 0;
         bgA.w = 34;
         bgA.h = 14;

    for ( i = 0; i < 2; ++i)
    {
         bgD[i].x = 0;
         bgD[i].y = 86*i;
         bgD[i].w = 80;
         bgD[i].h = 86;
    }
}
void monster_BG::cleanup(){
    SDL_FreeSurface(BG);
    SDL_FreeSurface(BGA);
    SDL_FreeSurface(BGD);
}
void monster_BG::handmove(SDL_Rect thing)
{
	if(isDead()==false){
		if(status == monster_RIGHT)
		{
			hand_velocity = -20;
		}
		else if(status == monster_LEFT)
		{
			hand_velocity = 20;
		}
		if(shoot)
			handplace.x += hand_velocity;

		if(handplace.x<0||handplace.x+handplace.w>=SCREEN_WIDTH){
			shoot=0;
			handplace.x=place.x;
		}

		if( thing.x>= place.x )
		{
			//Set the animation to left
			status = monster_LEFT;
		}

		else if( thing.x< place.x )
		{
			//Set the animation to right
			status = monster_RIGHT;
		}
	}
}

void monster_BG::show()
{
    if(isDead()==true)
    {
        if( status == monster_RIGHT)
        {
            apply_surface( place.x, place.y, BGD, screen, &bgD[ 0 ]);
        }
        if( status == monster_LEFT)
        {
            apply_surface( place.x, place.y, BGD, screen, &bgD[ 1 ]);
        }
    }
    //Loop the animation
    else{
    if( status == monster_RIGHT )
    {
		apply_surface( place.x, place.y, BG, screen, &bg[ 0 ]);
    }
    else if( status == monster_LEFT )
    {
		apply_surface( place.x, place.y, BG, screen, &bg[ 1 ]);
    }
    if(shoot)
    	apply_surface( handplace.x, handplace.y, BGA, screen, &bgA);
    }
}

bool monster_BG::beattack(SDL_Rect thing){
	if(place.y<=(thing.y+thing.h)&&(thing.y-place.y)<=86){
		if(thing.x<=(place.x+place.w)&&thing.x>=place.x)
			return true;
		if(place.x<=(thing.x+thing.w)&&place.x>=thing.x)
			return true;
		}
	return false;
}
void monster_BG::HandleHP(SDL_Rect bad){
    if(beattack(bad)==true){
    	if(Hpflag){
    		Hp--;
    		Hpflag=0;
    	}
    }
}
void monster_BG::HpTime(){
	if(timecnt==0){
		timecnt=0;
		Hpflag=1;
	}
	timecnt++;
    if(cd==50)
    {
    	cd=0;
    	shoot=1;
    }
    cd++;
}
bool monster_BG::isDead(){
    if(Hp<=0)
        return true;
    else
        return false;
}
void monster_BG::firebook(){
    Hp--;
}
void monster_BG::crutch(){
    Hp = 0;
}
