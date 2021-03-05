/*
 * score_0.cpp
 *
 *  Created on: 2017年6月4日
 *      Author: home
 */

#include "..\header\SDLtool.h"
#include "..\header\monster.h"

const int monster_WIDTH = 80;
const int monster_HEIGHT = 100;

//The direction status of the stick figure
const int monster_RIGHT = 0;
const int monster_LEFT = 1;
const int monster_Attack = 2;

SDL_Surface *score_0 = NULL;
SDL_Surface *score_0A = NULL;
SDL_Surface *score_0D = NULL;

SDL_Rect score0[2];
SDL_Rect score0A[2];
SDL_Rect score0D[2];

extern SDL_Surface *screen;

monster_score_0::monster_score_0(int x, int y)
{
    //Initialize movement variables
    place.x = x;
    place.y =  y;
    place.w = 80;
    place.h = 63;
    velocity = 0;
    Hp=5;
    //Initialize animation variables
    status = monster_RIGHT;
    status2=0;
    Hpflag=1;
    timecnt=0;
    setclips();
}

void monster_score_0::loadscore0(){
    score_0 = load_image_alpha( ".\\smmon\\book 3 80X63.png");
    score_0A = load_image_alpha( ".\\smmon\\book 3 _A 80X56.png");
    score_0D = load_image_alpha( ".\\smmon\\book 3 _D 80X63.png");
}
void monster_score_0::setclips(){
	int i;
    for ( i = 0; i < 2; ++i)
    {
         score0[i].x = 0;
        score0[i].y = 100*i;
         score0[i].w = 80;
         score0[i].h = 63;
    }

    for ( i = 0; i < 2; ++i)
    {
         score0A[i].x = 0;
         score0A[i].y = 100*i;
         score0A[i].w = 80;
         score0A[i].h = 56;
    }

    for ( i = 0; i < 2; ++i)
    {
         score0D[i].x = 0;
         score0D[i].y = 100*i;
         score0D[i].w = 80;
         score0D[i].h = 63;
    }
}
void monster_score_0::cleanup(){
	SDL_FreeSurface(score_0);
	SDL_FreeSurface(score_0A);
	SDL_FreeSurface(score_0D);
}
void monster_score_0::move()
{
	if(isDead()==false){
		  static int h =0;
		  srand(h*10);
		  h++;
		  int j = rand()%40;
        switch( j )
        {
        case 0 :  velocity = monster_WIDTH / 4; break;//往右
        case 1 :  velocity = -(monster_WIDTH) / 4; break;//往左
        case 2 :
			velocity = 0;
            break;
        case 20: velocity = monster_WIDTH / 4; break;
        case 10: velocity = -(monster_WIDTH) / 4; break;
        }
		place.x += velocity;

		//Keep the stick figure in bounds
		if( ( place.x < 0 ) || ( place.x + 100 > SCREEN_WIDTH ) )
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

void monster_score_0::show(SDL_Rect thing)
{
    if(isattack(thing) == true)
    {
    	status2 = monster_Attack;
    }
    else
    	status2 = 0;

    if(isDead() == true)
    {
    	velocity = 0;
    	if( status == monster_RIGHT )
    	{
    		apply_surface(place.x, place.y, score_0D,screen, &score0D[0]);
    	}

    	else if( status == monster_LEFT )
    	{
    		apply_surface(place.x, place.y, score_0D,screen, &score0D[1]);
    	}
    }
    else{
		if( status == monster_RIGHT )
		{
			if( status2 == monster_Attack )
				apply_surface( place.x,  place.y, score_0A, screen, &score0A[ 0 ]);
			else
				apply_surface( place.x, place.y, score_0, screen, &score0[ 0 ] );
		}
		else if( status == monster_LEFT )
		{
			if( status2 == monster_Attack )
				apply_surface( place.x,  place.y, score_0A, screen, &score0A[ 1 ]);
			else
				apply_surface( place.x,  place.y, score_0, screen, &score0[ 1 ] );
		}

    }
}

bool monster_score_0::beattack(SDL_Rect thing){
	if(place.y<=(thing.y+thing.h)&&(thing.y-place.y)<=63){
		if(thing.x<=(place.x+place.w)&&thing.x>=place.x)
			return true;
		if(place.x<=(thing.x+thing.w)&&place.x>=thing.x)
			return true;
	}
	return false;
}

bool monster_score_0::isattack(SDL_Rect thing){
	if(place.y<=(thing.y+thing.h)&&beattack(thing) == false)
	{
		if(thing.x<=(place.x+50+place.w)&&thing.x>=place.x+50)
			return true;
		if(place.x<=(thing.x+50+thing.w)&&place.x>=thing.x+50)
			return true;
	}
		return false;
}
void monster_score_0::HandleHP(SDL_Rect bad){
    if(beattack(bad)==true){
    	if(Hpflag){
    		Hp--;
    		Hpflag=0;
    	}
    }
}
void monster_score_0::Hptime(){
	if(timecnt==10){
		Hpflag=1;
		timecnt=0;
	}
	timecnt++;
}
bool monster_score_0::isDead(){
	if(Hp<=0)
		return true;
	else
		return false;
}

void cleanup()
{
	SDL_FreeSurface(score_0);
	SDL_FreeSurface(score_0D);
	SDL_FreeSurface(score_0A);
}
void monster_score_0::firebook(){
    Hp =0;
}
void monster_score_0::crutch(){
    Hp --;
}
