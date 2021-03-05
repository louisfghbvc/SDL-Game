/*
 * score_39.cpp
 *
 *  Created on: 2017年6月7日
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
const int monster_Attack = 2;

SDL_Surface *score_39 = NULL;
SDL_Surface *score_39A = NULL;
SDL_Surface *score_39D = NULL;

SDL_Rect score39[2];
SDL_Rect score39A[2];
SDL_Rect score39D[2];

extern SDL_Surface *screen;

monster_score_39::monster_score_39(int x, int y)
{
    //Initialize movement variables
    place.x = x;
    place.y = y;
    place.w=80;
    place.h=53;
    velocity = 0;
    Hp=3;
    Hpflag=1;
    timecnt=0;
    //Initialize animation variables
    status = monster_RIGHT;
    status2=0;
    status3=0;
    setclips();
}

void monster_score_39::loadscore39(){
    score_39 = load_image_alpha( ".\\smmon\\book1 80X53.png");
    score_39A = load_image_alpha( ".\\smmon\\book1_A 137X53.png");
    score_39D = load_image_alpha( ".\\smmon\\book1_D 80X53.png");
}
void monster_score_39::setclips(){
	int i;

    for ( i = 0; i < 2; ++i)
    {
         score39[i].x = 0;
         score39[i].y = 0;
        score39[i].w = 80;
        score39[i].h = 53*(i+1);
    }

    for ( i = 0; i < 2; ++i)
    {
        score39A[i].x = 0;
        score39A[i].y = 100*i;
         score39A[i].w = 137;
         score39A[i].h = 53;
    }

    for ( i = 0; i < 2; ++i)
    {
        score39D[i].x = 0;
        score39D[i].y = 100*i;
        score39D[i].w = 80;
        score39D[i].h = 53;
    }
}
void monster_score_39::cleanup(){
	SDL_FreeSurface(score_39);
	SDL_FreeSurface(score_39A);
	SDL_FreeSurface(score_39D);
}
void monster_score_39::move()
{
	if(isDead()==false){
		static int h =0;
		srand(h*10);
		h++;
		int j = rand()%50;
			switch( j )
			{
			case 0 :  velocity = monster_WIDTH / 4; break;//往右
			case 1 :  velocity = -(monster_WIDTH) / 4; break;//往左
			case 2 :
				velocity = 0;break;
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:break;
			}
	    place.x += velocity;

	    //Keep the stick figure in bounds
	    if( ( place.x < 0 ) || ( place.x + 80 > SCREEN_WIDTH ) )
	    {
	        place.x -= velocity;
	    }
	    if( velocity == -(monster_WIDTH) / 4 )
	    {
	        //Set the animation to left
	        status = monster_LEFT;
	    }
	    else if( velocity ==  monster_WIDTH / 4 )
	    {
	        //Set the animation to right
	        status = monster_RIGHT;
	    }
	}

}
void monster_score_39::show(SDL_Rect thing)
{
    if(isattack(thing) == true)
    {
    	status2 = monster_Attack;
    }
    else
    	status2=0;
    if(isDead() == true)
    {
     	velocity = 0;

    	if( status == monster_RIGHT)
        {
            apply_surface( place.x, place.y, score_39D, screen, &score39D[ 0 ]);
        }
        else if( status == monster_LEFT)
        {
            apply_surface( place.x, place.y, score_39D, screen, &score39D[ 1 ]);
        }
    }
    else{
		if( status == monster_RIGHT )
		{
			if( status2 == monster_Attack )
				apply_surface( place.x, place.y, score_39A, screen, &score39A[ 0 ]);
			else
				apply_surface( place.x, place.y, score_39, screen, &score39[0] );
		}
		else if( status == monster_LEFT )
		{
			if( status2 == monster_Attack )
				apply_surface( place.x, place.y, score_39A, screen, &score39A[ 1 ]);
			else
				apply_surface( place.x, place.y, score_39, screen, &score39A[1] );
		}
    }
}

bool monster_score_39::beattack(SDL_Rect thing){
	if(place.y<=(thing.y+thing.h)&&(thing.y-place.y)<=53){
		if(thing.x<=(place.x+place.w)&&thing.x>=place.x)
			return true;
		if(place.x<=(thing.x+thing.w)&&place.x>=thing.x)
			return true;
	}
	return false;
}

bool monster_score_39::isattack(SDL_Rect thing){
	if(place.y>=thing.y&&beattack(thing) == false)
	{
		if(thing.x<=(place.x+57+place.w)&&thing.x>=place.x+57)
			return true;
		if(place.x<=(thing.x+57+thing.w)&&place.x>=thing.x+57)
			return true;
	}
	return false;

}
void monster_score_39::HandleHP(SDL_Rect bad){
    if(beattack(bad)==true){
    	if(status==monster_LEFT)
    		place.x+=15;
    	else
    		place.x-=15;
    	if(Hpflag)
    		{
    		Hp--;
    		Hpflag=0;
    		}
    }
}
void monster_score_39::Hptime(){
	if(timecnt==10){
		Hpflag=1;
		timecnt=0;
	}
	timecnt++;
}
bool monster_score_39::isDead(){
	if(Hp<=0)
		return true;
	else
		return false;
}
void monster_score_39::firebook(){
    Hp =0;
}
void monster_score_39::crutch(){
    Hp --;
}
