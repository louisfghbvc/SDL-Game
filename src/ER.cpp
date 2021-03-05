/*
 * ER.cpp
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
const int monster_Attack=1;
const int monster_Dead =1;

SDL_Surface *ER = NULL;
SDL_Surface *ERA = NULL;
SDL_Surface *ERD = NULL;

SDL_Rect er;
SDL_Rect erA;
SDL_Rect erD;

extern SDL_Surface *screen;

monster_ER::monster_ER(int x, int y)
{
    //Initialize movement variables
    place.x = x;
    place.y=y;
    place.w=80;
    place.h=52;
    velocity = 0;
    Hp=5;
    //Initialize animation variables
    status = monster_RIGHT;
    status2=0;
    status3=0;
    Hpflag=1;
    timecnt=0;
}

void monster_ER::loadER(){
    ER = load_image_alpha( ".\\smmon\\ER 80X52.png");
    ERA = load_image_alpha( ".\\smmon\\ER_A 111X52.png");
    ERD = load_image_alpha( ".\\smmon\\ER_D 80X52.png");
}
void monster_ER::setclips(){

         er.x = 0;
        er.y = 0;
         er.w = 80;
         er.h = 52;

         erA.x = 0;
         erA.y = 0;
         erA.w = 111;
         erA.h = 52;

         erD.x = 0;
         erD.y = 0;
         erD.w = 80;
         erD.h = 52;
}
void monster_ER::handle_events()
{
    srand(time(NULL));

         int j = rand()%3;

        switch( j )
        {
        case 0 :  velocity = monster_WIDTH / 4; break;//往右
        case 1 :  velocity = -(monster_WIDTH) / 4; break;//往左
        case 2 :
			velocity = 0;break;
        case 3:    break;
        case 4: break;
        case 5: break;
        case 6: break;
        case 7: break;
        case 8: break;
        case 9: break;
        case 10: break;
        case 11: break;
        }


}
void monster_ER::cleanup(){
	SDL_FreeSurface(ER);
	SDL_FreeSurface(ERA);
	SDL_FreeSurface(ERD);
}
void monster_ER::move()
{
    //Move
    place.x += velocity;

    //Keep the stick figure in bounds
    if( ( place.x < 0 ) || ( place.x + 100 > SCREEN_WIDTH ) )
    {
        place.x -= velocity;
    }
}

void monster_ER::show(SDL_Rect thing)
{
	   if( thing.x>= place.x )
	    {
	        //Set the animation to left
	        status = monster_LEFT;
	    }
	    //If Foo is moving right
	    else if( thing.x< place.x )
	    {
	        //Set the animation to right
	        status = monster_RIGHT;
	    }
    if(isDead() == true)
    {
        status3 = monster_Dead;
    }
    //Loop the animation

    if(status3 == monster_Dead)
    {
    	velocity = 0;
            apply_surface( place.x, SCREEN_HEIGHT - 52- place.y, ERD, screen, &erD);
    }
    //Loop the animation

        if( status2 == monster_Attack )
        {

        	apply_surface( place.x, SCREEN_HEIGHT - 52- place.y, ERA, screen, &erA);
        }
        else
        	apply_surface( place.x, SCREEN_HEIGHT - 52- place.y, ER, screen, &er );
}



bool monster_ER::beattack(SDL_Rect thing){
    if(place.y<=(thing.y+thing.h)&&(thing.y-place.y)<=63){
        if(thing.x<=(place.x+place.w)&&thing.x>=place.x)
            return true;
    }
    return false;
}

bool monster_ER::isattack(SDL_Rect thing){
    if(place.y<= (thing.y+thing.h)&&beattack(thing) == false)
        if(thing.x+200<=(place.x+place.w)&&thing.x>=place.x+200)//10範圍
            return true;
        return false;

}
void monster_ER::HandleHP(SDL_Rect bad){
    if(beattack(bad)==true){
        place.x+=15;
        if(Hpflag==1)
            {
            Hp--;
            Hpflag=0;
            }
    }
}
void monster_ER::Hptime(){
    if(timecnt==20){
        Hpflag=1;
        timecnt=0;
    }
    timecnt++;
}
bool monster_ER::isDead(){
    if(Hp<=0)
        return true;
    else
        return false;
}
