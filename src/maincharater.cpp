//============================================================================
// Name        : animation.cpp
// Author      : Viola
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <string>
#include "..\header\SDLtool.h"
#include "..\header\mainperson.h"
#include "..\header\middlemonster.h"
#include "..\header\map.h"
using namespace std;

//The dimenstions of the stick figure
const int SB_WIDTH = 80;
const int SB_HEIGHT = 120;
const int ATK_WIDTH = 150;

//The direction status of the stick figure
const int SB_RIGHT = 1;
const int SB_LEFT = 0;
const int SB_UP = 0;
const int SB_DOWN = 1;
const int SB_N = 0;
const int SB_ATK = 1;
const int SB_ATK2 = 2;

//The surfaces
SDL_Surface *super = NULL;
SDL_Surface *jump = NULL;
SDL_Surface *watk = NULL;
SDL_Surface *katk = NULL;
SDL_Surface *airatk = NULL;
SDL_Surface *hp = NULL;
SDL_Surface *mp = NULL;


// 圖片座標
SDL_Rect clipsRight[ 3 ];
SDL_Rect clipsLeft[ 3 ];
SDL_Rect clipsJump[ 2 ];
SDL_Rect clipsAiratk[ 2 ];
SDL_Rect clipsatkL[ 5 ];
SDL_Rect clipsatkR[ 5 ];
SDL_Rect clipskatkL[ 7 ];
SDL_Rect clipskatkR[ 7 ];
SDL_Rect clipshp[ 6 ];
SDL_Rect clipsmp[ 6 ];


//The event structure
extern SDL_Surface *screen ;
extern SDL_Event event;


//********************************main****************************//


Superugly::Superugly(Background *m[])
{
    //Initialize movement variables
	place.x=0;
	place.y=100;//SCREEN_HEIGHT - SB_HEIGHT-100;
	place.w=SB_WIDTH;
	place.h=SB_HEIGHT;
    velocity = 0;
    v = 0;
    a = -5;
    height = 0;
    //Initialize animation variables
    frame = 0;
    cnt = 0;
    cnt2 =0;
    jps=0;
    HP=5;
    HPflag=1;
    timecnt=0;
    MP=5;
    status = SB_RIGHT;
    status2 = -1;//no jump
    status3 = SB_N;
    int i;
    for(i = 0; i < 9; ++i)
    	mymap[i] = m[i];
    now = 0;
    past = -1;
    load_SB_files();
    abullet.load_bullet();
    prop.loadprop();
    set_clips();
    prop.setclips();
}
const int Superugly::handx[5]={-70,-59,-57,0,0};
const int Superugly::rehandx[5]={0,0,0,-12,-46};
const int Superugly::khandx[7]={0,0,-10,-20,-10,0,0};
const int Superugly::krehandx[7]={-44,-47,-28,-10,-30,-47,-44};

bool Superugly::load_SB_files()
{
    //Load the sprite sheet
    super = load_image_alpha( ".\\SB\\walk.png" );
    jump = load_image_alpha( ".\\SB\\jump.png" );
    watk = load_image_alpha( ".\\SB\\watk.png" );
    airatk = load_image_alpha(".\\SB\\airattack.png" );
    katk = load_image_alpha(".\\SB\\katk.png" );
    hp = load_image_alpha(".\\SB\\HP.png" );
    mp = load_image_alpha(".\\SB\\MP.png");
    //If there was a problem in loading the sprite
    if( super == NULL||jump==NULL||watk==NULL||airatk==NULL||katk==NULL||hp==NULL||mp==NULL)
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void Superugly::set_clips()
{
    //Clip the sprites
	int i;
	for(i=0; i<3 ;++i){
		clipsRight[ i ].x = SB_WIDTH*i;
		clipsRight[ i ].y = 0;
		clipsRight[ i ].w = SB_WIDTH;
		clipsRight[ i ].h = SB_HEIGHT;
		clipsLeft[ i ].x = SB_WIDTH*i;
		clipsLeft[ i ].y = SB_HEIGHT;
		clipsLeft[ i ].w = SB_WIDTH;
		clipsLeft[ i ].h = SB_HEIGHT;
	}
	for(i=0;i<2;++i){
		clipsJump[ i ].x = 0;
		clipsJump[ i ].y = SB_HEIGHT*i;
		clipsJump[ i ].w = SB_WIDTH;
		clipsJump[ i ].h = SB_HEIGHT;
	}
	for(i=0;i<5;++i){
		clipsatkR[ i ].x = ATK_WIDTH*i;
		clipsatkR[ i ].y = 0;
		clipsatkR[ i ].w = ATK_WIDTH;
		clipsatkR[ i ].h = SB_HEIGHT;
		clipsatkL[ i ].x = ATK_WIDTH*i;
		clipsatkL[ i ].y = SB_HEIGHT;
		clipsatkL[ i ].w = ATK_WIDTH;
		clipsatkL[ i ].h = SB_HEIGHT;
	}
	for(i=0;i<2;++i){
		clipsAiratk[ i ].x = 0;//1:x-90;
		clipsAiratk[ i ].y = SB_HEIGHT*i;
		clipsAiratk[ i ].w = ATK_WIDTH;
		clipsAiratk[ i ].h = SB_HEIGHT;
	}
	for(i=0;i<7;++i){
		clipskatkR[ i ].x = 120*i;
		clipskatkR[ i ].y = 0;
		clipskatkR[ i ].w = 120;//120X120
		clipskatkR[ i ].h = SB_HEIGHT;
		clipskatkL[ i ].x = 120*i;
		clipskatkL[ i ].y = SB_HEIGHT;
		clipskatkL[ i ].w = 120;
		clipskatkL[ i ].h = SB_HEIGHT;
	}
	for(i=0;i<6;++i){
		clipshp[ i ].x = 0;
		clipshp[ i ].y = 45*i;
		clipshp[ i ].w = 250;//250X45
		clipshp[ i ].h = 45;
		clipsmp[ i ].x = 0;
		clipsmp[ i ].y = 45*i;
		clipsmp[ i ].w = 250;
		clipsmp[ i ].h = 45;
	}
}

void Superugly::handle_events()
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Set the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_d: velocity += SB_WIDTH / 4; break;
            case SDLK_a: velocity -= SB_WIDTH / 4; break;
            case SDLK_w:
            		if(mymap[now]->downRange(place.x, place.y, place.w, place.h) == false && height == 0)
					{
            			status2 = SB_UP;
            			v = 40;
            		}
            	break;
            case SDLK_s:
            	if(mymap[now]->theDoor(place.x, place.y, place.w, place.h) != -1)
            	{
            		if(mymap[now]->theDoorisNotLocked(mymap[now]->theDoor(place.x, place.y, place.w, place.h)))
            	    {
            			past = now;
            	        now = mymap[now]->opentheDoor(mymap[now]->theDoor(place.x, place.y, place.w, place.h));
            	        place.x = mymap[now]->enterx(mymap[now]->enterdoornum(past));
            	        place.y = mymap[now]->entery(mymap[now]->enterdoornum(past));
            	    }
            		else{
            			int i=0;
            			for(i=0;i<4;++i){
            				if(prop.keynum[i] == mymap[now]->matchtheDoor(mymap[now]->theDoor(place.x, place.y, place.w, place.h)))
            				{
            					mymap[now]->opentheDoor(mymap[now]->theDoor(place.x, place.y, place.w, place.h));
            					prop.keynum[i] = -1;
            				}
            			}
            		}
            	}
            	if(mymap[now]->thekey(place.x,place.y,place.w,place.h)){
					int i;
					for(i=0;i<4&&prop.keynum[i]!=-1;++i);
					if(i!=4)
						prop.keynum[i]=mymap[now]->getthekey(place.x,place.y,place.w,place.h);
            	}
            	if(mymap[now]->openthebox(place.x,place.y,place.w,place.h)){
					prop.which=rand()%3;
            	}
            	if(mymap[now]->usehealsystem(place.x,place.y,place.w,place.h)){
            		if(HP<5)
            			HP++;
            	}
            	break;
            case SDLK_j:
            		if(status3 == SB_N){
            			status3 = SB_ATK;
            			if(jps==0)
            				jps=4;
            		}
					break;
            case SDLK_k:
        			if(status3 == SB_N){
        				status3 = SB_ATK2;
        				abullet.shoot=1;
        			}
        			break;
            case SDLK_l:
        		switch(prop.which){
        			case 0:
        				if(MP>=4)
        					{
        					MP-=4;
        					prop.which=-1;
        					reset=0;
        					}
        				break;
        			case 1:
        				if(MP>=5)
        					{
        					MP-=5;
        					prop.which=-1;
        					reset=0;
        					}
        				break;
        			case 2:
        				if(MP>=3)
        					{
        					MP-=3;
        					prop.which=-1;
        					reset=0;
        					}
        				break;
        		}
        		break;
            default:break;
        }
    }
    //If a key was released
    else if( event.type == SDL_KEYUP )
    {
        //Set the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_d: velocity -=SB_WIDTH / 4; break;
            case SDLK_a: velocity +=SB_WIDTH / 4 ; break;
            default:break;
        }
    }
}
void Superugly::move()
{
    //Move
    place.x += velocity;
    //Keep the stick figure in bounds
    dofixx();
    if(mymap[now]->walkRange(place.x, place.y, place.w, place.h) == false)
    {
        place.x = mymap[now]->walkx(place.x, place.y, place.w, place.h);
    }

    place.y-=v;
    if(mymap[now]->downRange(place.x, place.y, place.w, place.h) == true && status2 != SB_UP)
    {
    	status2 = SB_DOWN;
    	height = 0;
    	v += a;
    }
    else if(mymap[now]->downRange(place.x, place.y, place.w, place.h) != true && status2 == SB_DOWN)
    {
    	status2 = -1;
    	place.y = mymap[now]->downy(place.x, place.y, place.w, place.h);
    	v = 0;
    }
    if(status2==SB_UP){
    		v += a;//上升速度 越來越慢
    		if(v == 0)
    			status2 = SB_DOWN;
    		if(mymap[now]->jumpRange(place.x, place.y, place.w, place.h)==false)
    		{
    			v = 0;
    			status2 = SB_DOWN;
    			place.y = mymap[now]->jumpy(place.x, place.y, place.w, place.h);
    		}
    	}
}
void Superugly::show()
{
	mymap[now]->show();
	showHP();
	showMP();
	prop.showplace();
    //If SB is moving left
    if( velocity < 0 )
    {
        //Set the animation to left
        status = SB_LEFT;
        //Move to the next frame in the animation
        frame++;

    }
    //If SB is moving right
    else if( velocity > 0 )
    {
        //Set the animation to right
        status = SB_RIGHT;
        //Move to the next frame in the animation
        frame++;
    }
    //If SB standing
    else
    {
        //Restart the animation
        frame = 0;
    }
    //Loop the animation
    if( frame >= 3 )
    {
        frame = 0;
    }
    //Show the stick figure
	if(status3 == SB_ATK && status == SB_RIGHT && status2 == -1){
			place.w=ATK_WIDTH;
			apply_surface( place.x, place.y, watk, screen, &clipsatkR[ cnt ] );
			place.x-=handx[cnt];
			if(cnt>=4){
				status3 = SB_N;
				cnt=0;
			}
			cnt++;
	}
	else if(status3 == SB_ATK && status == SB_LEFT && status2 == -1){
			place.w=ATK_WIDTH;
			apply_surface(place.x, place.y, watk, screen, &clipsatkL[ cnt ] );
			place.x-=rehandx[cnt];
			if(cnt>=4){
				status3 = SB_N;
				cnt=0;
				}
			cnt++;
	}
	else if(status3 == SB_ATK2 && status == SB_RIGHT && status2 == -1){
			place.w=SB_WIDTH;
			apply_surface( place.x, place.y, katk, screen, &clipskatkR[ cnt2 ] );
			if(cnt2==1){
				abullet.direct=1;
				abullet.bulletplace=place;
			}
			place.x-=khandx[cnt2];
			if(cnt2>=6){
				status3 = SB_N;
				cnt2=0;
			}
			cnt2++;
	}
	else if(status3 == SB_ATK2 && status == SB_LEFT && status2 == -1){
			place.w=SB_WIDTH;
			apply_surface( place.x, place.y, katk, screen, &clipskatkL[ cnt2 ] );
			if(cnt2==1){
				abullet.direct=0;
				abullet.bulletplace=place;
			}
			place.x-=krehandx[cnt2];
			if(cnt2>=6){
				status3 = SB_N;
				cnt2=0;
				}
			cnt2++;
	}
	else if( status == SB_RIGHT && status2 == SB_UP)
    {
		if(status3 == SB_ATK){
			place.w=120;
			apply_surface( place.x, place.y, airatk, screen, &clipsAiratk[ 0 ] );
			jps--;
			if(jps==0)
				status3=SB_N;
			}
		else if(status3 == SB_ATK2){
			place.w=SB_WIDTH;
			apply_surface( place.x, place.y, katk, screen, &clipskatkR[ cnt2 ] );
			if(cnt2==1){
				abullet.direct=1;
				abullet.bulletplace=place;
			}
			place.x-=khandx[cnt2];
			SDL_Delay(5);
			if(cnt2>=6){
				status3 = SB_N;
				cnt2=0;
			}
			cnt2++;
		}
		else{
			place.w=SB_WIDTH;
			apply_surface( place.x, place.y, jump, screen, &clipsJump[ 0 ] );
		}
    }
    else if( status == SB_LEFT && status2 == SB_UP )
    {
		if(status3 == SB_ATK){
			place.w=120;
			apply_surface( place.x, place.y, airatk, screen, &clipsAiratk[ 1 ] );//fix x
			place.x+=53;
			jps--;
			if(jps==0)
				status3=SB_N;
		}
		else if(status3 == SB_ATK2){
			place.w=SB_WIDTH;
			apply_surface( place.x, place.y, katk, screen, &clipskatkL[ cnt2 ] );
			if(cnt2==1){
				abullet.direct=0;
				abullet.bulletplace=place;
			}
			place.x-=krehandx[cnt2];
			if(cnt2>=6){
				status3 = SB_N;
				cnt2=0;
				}
			cnt2++;
		}
		else{
			place.w=SB_WIDTH;
			apply_surface( place.x, place.y, jump, screen, &clipsJump[ 1 ] );
		}
    }
    else if( status == SB_RIGHT && status2 == SB_DOWN)
    {
		if(status3 == SB_ATK){
			place.w=120;
			apply_surface( place.x, place.y, airatk, screen, &clipsAiratk[ 0 ] );
		}
		else if(status3 == SB_ATK2){
			place.w=SB_WIDTH;
			apply_surface( place.x, place.y, katk, screen, &clipskatkR[ cnt2 ] );
			if(cnt2==1){
				abullet.direct=1;
				abullet.bulletplace=place;
			}
			place.x-=khandx[cnt2];
			if(cnt2>=6){
				status3 = SB_N;
				cnt2=0;
			}
			cnt2++;
		}
		else{
			place.w=SB_WIDTH;
			apply_surface( place.x, place.y, jump, screen, &clipsJump[ 0 ] );
		}
    }
    else if( status == SB_LEFT && status2 == SB_DOWN )
    {
		if(status3 == SB_ATK){

			place.w=120;
			apply_surface( place.x, place.y, airatk, screen, &clipsAiratk[ 1 ] );//fix x
			place.x+=53;
			jps--;
			if(jps==0)
				status3=SB_N;
		}
		else if(status3 == SB_ATK2){
			place.w=SB_WIDTH;
			apply_surface( place.x, place.y, katk, screen, &clipskatkL[ cnt2 ] );
			if(cnt2==1){
				abullet.direct=0;
				abullet.bulletplace=place;
			}
			place.x-=krehandx[cnt2];
			if(cnt2>=6){
				status3 = SB_N;
				cnt2=0;
				}
			cnt2++;
		}
		else{
			place.w=SB_WIDTH;
			apply_surface( place.x, place.y, jump, screen, &clipsJump[ 1 ] );
		}
    }
    else if(status == SB_RIGHT ){
    	place.w=SB_WIDTH;
        apply_surface( place.x, place.y, super, screen, &clipsRight[ frame ] );
    }
    else if(status == SB_LEFT ){
    	place.w=SB_WIDTH;
        apply_surface( place.x, place.y, super, screen, &clipsLeft[ frame ] );
    }
}
void Superugly::showHP(){
	apply_surface( 0, 0, hp, screen, &clipshp[ 5-HP ] );
}
void Superugly::showMP(){
	apply_surface( 0, 45, mp, screen, &clipsmp[ 5-MP ] );
}
void Superugly::dofixx(){
	if(status3==SB_ATK){
		if(status2==-1){
			if(status==SB_RIGHT){
				place.x+=handx[cnt];
			}
			else
				place.x+=rehandx[cnt];
		}
		else{
			place.y-=height;
			if(status==SB_LEFT){
				place.x-=53;
			}
		}
	}
	else if(status3==SB_ATK2){
		if(status2==-1){
			if(status==SB_RIGHT){
				place.x+=khandx[cnt2];
			}
			else
				place.x+=krehandx[cnt2];
		}
		else{
			place.y-=height;
			if(status==SB_LEFT)
				place.x+=krehandx[cnt2];
			else
				place.x+=khandx[cnt2];
		}
	}
	else{
		if(status2!=-1)
			place.y-=height;
	}
}
void Superugly::undofixx(){
	if(status3==SB_ATK){
		if(status2==-1){
			if(status==SB_RIGHT){
				place.x-=handx[cnt];
			}
			else
				place.x-=rehandx[cnt];
		}
		else{
			place.y+=height;
			if(status==SB_LEFT){
				place.x+=53;
			}
		}
	}
	else if(status3==SB_ATK2){
		if(status2==-1){
			if(status==SB_RIGHT){
				place.x-=khandx[cnt2];
			}
			else
				place.x-=krehandx[cnt2];
		}
		else{
			place.y+=height;
			if(status==SB_LEFT)
				place.x-=krehandx[cnt2];
			else
				place.x-=khandx[cnt2];
		}
	}
	else{
		if(status2!=-1)
			place.y+=height;
	}
}
bool Superugly::beattack(SDL_Rect thing){
	if(place.y<=(thing.y+thing.h)&&(thing.y-place.y)<=SB_HEIGHT){
		if(thing.x<=(place.x+SB_WIDTH)&&thing.x>=place.x)
			return true;
		if(place.x<=(thing.x+thing.w)&&place.x>=thing.x)
			return true;
		}
	return false;
}
void Superugly::handleHP(SDL_Rect bad){
    if(beattack(bad)==true){
    	if(HPflag==1)
    		{
    		HP--;
    		HPflag=0;
    		}
    	if(HP<0)
    		HP=5;
    }
}
void Superugly::handleHP(SDL_Rect bad,int x,int y){
	SDL_Rect a=bad;
	a.x=x;
	a.y=y;
    if(beattack(a)==true){
    	if(HPflag==1)
    		{
    		HP--;
    		HPflag=0;
    		}
    	if(HP<0)
    		HP=5;
    }
}
void Superugly::Hptime(){
	if(timecnt==35){
    	HPflag=1;
    	timecnt=0;
    	if(MP<5)
    		MP++;
    }
    timecnt++;
}
void Superugly::cleanSB()
{
    //Free the surface
    SDL_FreeSurface( super );
    SDL_FreeSurface( jump );
    SDL_FreeSurface( watk );
    SDL_FreeSurface( airatk );
    SDL_FreeSurface( katk );
    SDL_FreeSurface( hp );
    SDL_FreeSurface( mp );
    abullet.cleanup();
    prop.cleanup();
}
