/*
 * score_59.cpp
 *
 *  Created on: 2017年6月4日
 *      Author: home
 */
#include "..\header\SDLtool.h"
#include "..\header\monster.h"
#include <time.h>

const int monster_WIDTH = 80;
const int monster_HEIGHT = 100;

//The direction status of the stick figure
const int monster_RIGHT = 0;
const int monster_LEFT = 1;
const int monster_Attack = 2;

SDL_Surface *score_59 = NULL;
SDL_Surface *score_59A = NULL;
SDL_Surface *score_59D = NULL;

SDL_Rect score59[2];
SDL_Rect score59A[2];
SDL_Rect score59D[2];

extern SDL_Surface *screen;

monster_score_59::monster_score_59(int x, int y)
{
    //Initialize movement variables
    place.x = x;
    place.y=y;
    place.w=100;
    place.h=53;
    velocity = 0;
    Hp=1;
    //Initialize animation variables
    status = monster_RIGHT;
    status2=0;
    setclips();
}

void monster_score_59::loadscore59(){
    score_59 = load_image_alpha( ".\\smmon\\book2 100X53.png");
    score_59A = load_image_alpha( ".\\smmon\\book2_A 137X53.png");
    score_59D = load_image_alpha( ".\\smmon\\book2_D 100X53.png");
}
void monster_score_59::setclips(){
	int i;
    for ( i = 0; i < 2; ++i)
    {
         score59[i].x = 0;
         score59[i].y = 0;
        score59[i].w = 100;
        score59[i].h = 53;
    }

    for ( i = 0; i < 2; ++i)
    {
        score59A[i].x = 0;
        score59A[i].y = 100*i;
         score59A[i].w = 137;
         score59A[i].h = 53;
    }

    for ( i = 0; i < 2; ++i)
    {
        score59D[i].x = 0;
        score59D[i].y = 100*i;
        score59D[i].w = 100;
        score59D[i].h = 53;
    }
}
void monster_score_59::cleanup(){
	SDL_FreeSurface(score_59);
	SDL_FreeSurface(score_59A);
	SDL_FreeSurface(score_59D);
}
void monster_score_59::move()
{
	if(isDead()==false){
		static int h =0;
		srand(h*10);
		h++;
		int j = rand()%25;

		switch( j )
		{
		case 0 :  velocity = monster_WIDTH / 4; break;//往右
		case 1 :  velocity = -(monster_WIDTH) / 4; break;//往左
		case 2 :
			velocity = 0;
			break;
		case 3:	velocity = monster_WIDTH / 4; break;
		case 5: velocity = -(monster_WIDTH) / 4; break;
		case 10:
		case 16:break;
		}
		//Move
		place.x += velocity;

		//Keep the stick figure in bounds
		if( ( place.x < 0 ) || ( place.x + 80 > SCREEN_WIDTH ) )
		{
			place.x -= velocity;
		}
	    //If Foo is moving left
	    if( velocity == -(monster_WIDTH) / 4 )
	    {
	        //Set the animation to left
	        status = monster_LEFT;
	    }
	    //If Foo is moving right
	    else if( velocity ==  monster_WIDTH / 4 )
	    {
	        //Set the animation to right
	        status = monster_RIGHT;
	    }
	}

}
void monster_score_59::show(SDL_Rect thing)
{

    if(isattack(thing) == true)
    {
    	status2 = monster_Attack;
    }
    else
    	status2=0;

    if(isDead()==true)
    {
    	velocity = 0;

    	if( status == monster_RIGHT)
        {
            apply_surface( place.x, place.y, score_59D, screen, &score59D[ 0 ]);
        }
        if( status == monster_LEFT)
        {
            apply_surface( place.x, place.y, score_59D, screen, &score59D[ 1 ]);
        }

    }
    else{
		if( status == monster_RIGHT )
		{
			if( status2 == monster_Attack )
				apply_surface( place.x,  place.y, score_59A, screen, &score59A[ 0 ]);
			else
				apply_surface( place.x,  place.y, score_59, screen, &score59[ 0 ] );
		}
		else if( status == monster_LEFT )
		{
			if( status2 == monster_Attack )
				apply_surface( place.x, place.y, score_59A, screen, &score59A[ 1 ]);
			else
				apply_surface( place.x, place.y, score_59, screen, &score59[ 1 ] );
		}
    }

}

bool monster_score_59::beattack(SDL_Rect thing){
	if(place.y<=(thing.y+thing.h)&&(thing.y-place.y)<=53){
		if(thing.x<=(place.x+place.w)&&thing.x>=place.x)
			return true;
		if(place.x<=(thing.x+thing.w)&&place.x>=thing.x)
			return true;
	}
	return false;
}

bool monster_score_59::isattack(SDL_Rect thing){
	if(place.y<= (thing.y+thing.h)&&beattack(thing) == false)
	{
		if(thing.x<=(place.x+57+place.w)&&thing.x>=place.x+57)
			return true;
		if(place.x<=(thing.x+57+thing.w)&&place.x>=thing.x+57)
			return true;
	}
		return false;

}
void monster_score_59::HandleHP(SDL_Rect bad){
    if(beattack(bad)==true){
    	if(status==monster_LEFT)
    		place.x+=15;
    	else
    		place.x-=15;
    		Hp--;
    }
}
bool monster_score_59::isDead(){
	if(Hp<=0)
		return true;
	else
		return false;
}
void monster_score_59::firebook(){
    Hp =0;
}
void monster_score_59::crutch(){
    Hp --;
}
