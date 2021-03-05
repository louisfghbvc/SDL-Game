/*
 * TC.cpp
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
const int monster_Dead = 1;
SDL_Surface *TC = NULL;
SDL_Surface *TCH = NULL;
SDL_Surface *TCD = NULL;

SDL_Rect tc;
SDL_Rect tcH;
SDL_Rect tcD;

extern SDL_Surface *screen;

monster_TC::monster_TC(int x, int y)
{
    //Initialize movement variables
    place.x = x;
    place.y=y;
    place.w=40;
    place.h=100;
    velocity = 0;
    Hp=5;
    //Initialize animation variables
    frame = 0;
    status = monster_RIGHT;
    status2=0;
    status3=0;
    timecnt=0;
    Hpflag =1;
}

void monster_TC::loadTC(){
    TC = load_image_alpha( ".\\smmon\\TC 40X100.png");
    TCH = load_image_alpha( ".\\smmon\\TC_H 21X33.png");
    TCD = load_image_alpha( ".\\smmon\\TC_D 40X100.png");
}
void monster_TC::setclips(){

         tc.x = 0;
        tc.y = 0;
         tc.w = 40;
         tc.h = 100;

         tcH.x = 0;
         tcH.y = 0;
         tcH.w = 21;
        tcH.h = 33;

         tcD.x = 0;
         tcD.y = 0;
         tcD.w = 40;
         tcD.h = 100;
}
void monster_TC::handle_events()
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
        case 12: break;
        }


}
void monster_TC::cleanup(){
	SDL_FreeSurface(TC);
	SDL_FreeSurface(TCH);
	SDL_FreeSurface(TCD);
}
void monster_TC::move()
{
    //Move
    place.x += velocity;

    //Keep the stick figure in bounds
    if( ( place.x < 0 ) || ( place.x + 100 > SCREEN_WIDTH ) )
    {
        place.x -= velocity;
    }
}

void monster_TC::show(SDL_Rect thing)
{
    //If Foo is moving left
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
            apply_surface( place.x, SCREEN_HEIGHT - 100- place.y, TCD, screen, &tcD);
    }
    //Loop the animation


    if( status2 == monster_Attack )
    {

    	apply_surface( place.x, SCREEN_HEIGHT - 100- place.y, TCH, screen, &tcH);
    }
    else
    	apply_surface( place.x, SCREEN_HEIGHT - 100- place.y, TC, screen, &tc );
}


bool monster_TC::beattack(SDL_Rect thing){
    if(place.y<=(thing.y+thing.h)&&(thing.y-place.y)<=63){
        if(thing.x<=(place.x+place.w)&&thing.x>=place.x)
            return true;
    }
    return false;
}

bool monster_TC::isattack(SDL_Rect thing){
    if(place.y<= (thing.y+thing.h)&&beattack(thing) == false)
        if(thing.x+10<=(place.x+place.w)&&thing.x>=place.x+10)//10範圍
            return true;
        return false;

}
void monster_TC::HandleHP(SDL_Rect bad){
    if(beattack(bad)==true){
        place.x+=15;
        if(Hpflag==1)
            {
            Hp--;
            Hpflag=0;
            }
    }
}
void monster_TC::Hptime(){
    if(timecnt==20){
        Hpflag=1;
        timecnt=0;
    }
    timecnt++;
}
bool monster_TC::isDead(){
    if(Hp<=0)
        return true;
    else
        return false;
}
