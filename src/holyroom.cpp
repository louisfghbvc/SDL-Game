//============================================================================
// Name        : holyroom.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
 
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "..\header\SDLtool.h"
#include "..\header\mainperson.h"
#include "..\header\middlemonster.h"
#include "..\header\monster.h"
#include "..\header\map.h"
#include "..\header\bbos.h"
extern SDL_Surface *screen;
extern SDL_Event event;
extern SDL_Surface *material[7];
extern SDL_Surface *door_image[2];
extern mato mato1;
monster_score_39 a(200,647);
monster_score_59 b(400,647);
monster_score_0 c(300,637);

void set_all_clips(void)
{
	set_background_clips();
}
bool load_files(void)
{
	if(load_background_files() == false)
		return false;
	return true;
}
void clean_up(void)
{
	clean_background();
	SDL_Quit();
}
int main(int argc, char *args[])
{
    bool quit = false;

    if(init() == false)
        return 1;
    if(load_files() == false)
        return 1;
    /***/
    SDL_Surface *mymapbim0 = material[1],
        			*mymapbim1 = material[1],
    				*mymapbim3 = material[1],
    				*mymapbim4 = material[6],
        			*mymapbim5 = material[1],
    				*mymapbim6 = material[1],
    				*mymapbim7 = material[1],
    				*mymapbim8 = material[4];
        SDL_Surface *mymapfim0[2] = {material[5], material[3]},
        			*mymapfim1[2] = {material[3], material[5]},
    				*mymapfim3[2] = {material[3], material[3]},
    				*mymapfim4[4] = {material[6], material[0], material[5], NULL},
    				*mymapfim5[4] = {material[4], material[6], material[6], material[4]},
    				*mymapfim6[4] = {material[6], NULL, material[3], material[6]},
    				*mymapfim7[2] = {material[3], material[3]},
    				*mymapfim8[4] = {material[5], NULL, material[1], material[3]};
        SDL_Surface *mymapdim0[3] = {door_image[0], door_image[1], door_image[0]},
        			*mymapdim1[3] = {door_image[0], NULL, NULL},
    				*mymapdim3[3] = {door_image[0], door_image[1], door_image[0]},
    				*mymapdim4[3] = {door_image[0], NULL, NULL},
    				*mymapdim5[3] = {door_image[0], door_image[0], NULL},
    				*mymapdim6[3] = {door_image[0], door_image[1], door_image[0]},
    				*mymapdim7[3] = {door_image[0], door_image[0], NULL},
        			*mymapdim8[3] = {door_image[0], door_image[1], door_image[0]};
        int mymapfnum0[2] = {50, 100},
        	mymapfnum1[6] = {100, 100},
    		mymapfnum3[2] = {100, 100},
    		mymapfnum4[4] = {50, 50, 100, 0},
    		mymapfnum5[4] = {50, 50, 50, 50},
    		mymapfnum6[4] = {50, 0, 25, 75},
    		mymapfnum7[2] = {100, 100},
    		mymapfnum8[4] = {50, 0, 50, 50};
        int mymapdnum0[15] = {0, 700 - 200, 0, 2, 18, 500, 700 - 200, 9, 0, 1, 1200 - 40, 700 - 200, 8, 0, 2},
        	mymapdnum1[5] = {0, 700 - 200, 8, 0, 0},
    		mymapdnum3[15] = {0, 700 - 200, 8, 0, 2, 500, 700 - 200, 1, 1, 4, 1200 - 40, 700 - 200, 8, 0, 5},
    		mymapdnum4[5] = {0, 700 - 200, 1, 0, 3},
    		mymapdnum5[10] = {0, 700 - 100 - 200, 8, 0, 3, 1200 - 40, 700 - 100 - 200, 2, 1, 6},
    		mymapdnum6[15] = {0, 700 - 200, 2, 0, 5, 600 - 100, 700 - 5, 6, 1, 26, 1200 - 40, 700 - 200, 8, 0, 7},
    		mymapdnum7[10] = {0, 700 - 200, 8, 0, 6, 1200 - 40, 700 - 200, 8, 0, 8},
    		mymapdnum8[15] = {0, 700 - 200, 8, 0, 7, 600 - 100, 700 - 200, 9, 0, 9, 1200 - 40, 700 - 200, 8, 0, 10};
        Map_0 mymap0(mymapbim0, mymapfim0, mymapfnum0, mymapdim0, mymapdnum0);
        Map_1 mymap1(mymapbim1, mymapfim1, mymapfnum1, mymapdim1, mymapdnum1);
        Map_2 mymap2;
        Map_3 mymap3(mymapbim3, mymapfim3, mymapfnum3, mymapdim3, mymapdnum3);
        Map_4 mymap4(mymapbim4, mymapfim4, mymapfnum4, mymapdim4, mymapdnum4);
        Map_5 mymap5(mymapbim5, mymapfim5, mymapfnum5, mymapdim5, mymapdnum5);
        Map_6 mymap6(mymapbim6, mymapfim6, mymapfnum6, mymapdim6, mymapdnum6);
        Map_7 mymap7(mymapbim7, mymapfim7, mymapfnum7, mymapdim7, mymapdnum7);
        Map_8 mymap8(mymapbim8, mymapfim8, mymapfnum8, mymapdim8, mymapdnum8);
        Background *mymap[9] = {&mymap0, &mymap1, &mymap2, &mymap3, &mymap4, &mymap5, &mymap6, &mymap7, &mymap8};
    Superugly person(mymap);
    sly slya(400,550);
    umo umoa(200,200);
    /***/
    set_all_clips();
    mato1.load_mato_flies();
    a.loadscore39();
    b.loadscore59();
    c.loadscore0();
    umoa.load_umo_files();
    slya.load_sly_files();
    NI ni(500,300);
    Timer time;


    int i = 1;

    while(quit == false)
    {
    	time.start();
        if ( SDL_PollEvent( &event ))
        {
        	person.handle_events();
            if( event.type == SDL_QUIT )
                quit = true;
        }
        /***/
    person.move();

	/***/
    //*****
    person.show();

    person.dofixx();

    if(person.now==0){
        a.move();
        b.move();
        c.move();
    	a.show(person.place);
    	b.show(person.place);
    	c.show(person.place);
    	if(!a.isDead())
    		person.handleHP(a.place);
    	if(!b.isDead())
    	person.handleHP(b.place);
    	if(!c.isDead())
    	person.handleHP(c.place);
        a.Hptime();
        c.Hptime();
    }
    if(person.now==2){ni.acting(person,mymap[2]);}
	if(person.now==3)
    {
		if(slya.isDead()==false){
		slya.slymove(person.place);
    	slya.show();
    	person.handleHP(slya.place);
    	person.handleHP(slya.handplace);
	    slya.Hptime();
		}
    }
	if(person.now==6){
		if(umoa.isDead()==false){
			umoa.moverock();
			umoa.umomove();
		    umoa.show();
		    if(umoa.atkcd==0)
		    	umoa.a.setplace(person.place);
			if(umoa.a.rockdown==1){
				umoa.showrock();
				person.handleHP(umoa.a.rplace);
				}
			person.handleHP(umoa.place);
		    umoa.Hptime();
		}
	}
    if(person.abullet.shoot==1)
    	{
    	person.abullet.dofixx();
    	person.abullet.showbullet();
    	if(person.now==0){
		a.HandleHP(person.abullet.bulletplace);
    	b.HandleHP(person.abullet.bulletplace);
    	c.HandleHP(person.abullet.bulletplace);
    	}
    	if(person.now==2){
    	ni.ifbehit(person.abullet.bulletplace);
    	}
    	if(person.now==3)slya.HandleHP(person.abullet.bulletplace);
    	if(person.now==6)umoa.HandleHP(person.abullet.bulletplace);
    	person.abullet.undofixx();
    	}

    if(person.status3==1){
    	if(person.now==0){
		a.HandleHP(person.place);
    	b.HandleHP(person.place);
    	c.HandleHP(person.place);
    	}
    	if(person.now==2){
    	ni.ifbehit(person.place);
    	}
    	if(person.now==3)slya.HandleHP(person.place);
    	if(person.now==6)umoa.HandleHP(person.place);
    }
    if(person.now==5){
    	person.handleHP(mato1.place);
    }
    person.undofixx();
    person.Hptime();
    //*****
        SDL_Flip(screen);

        if(time.getTicks() < (1000 / FRAMES_PER_SECOND))
        	SDL_Delay((1000 / FRAMES_PER_SECOND) - time.getTicks());
        ++i;

    }

    clean_up();
	person.cleanSB();
    return 0;
}
