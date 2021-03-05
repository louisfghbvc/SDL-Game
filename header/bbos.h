#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include "..\header\map.h"
#include "..\header\mainperson.h"
#include "..\header\middlemonster.h"
using namespace std;

#ifndef BBOS_H_
#define BBOS_H_
extern int pp;
extern SDL_Surface *BOSS[5];
extern SDL_Surface *screen;
extern Mix_Music *bmus ;

	  class NI{
	  public:
	  		NI(int ,int);
	  		bool ifbehit(SDL_Rect );
	  		void acting(Superugly&,Background*);
	  	private:
	  		bool isdead();
	  		void fang(SDL_Rect );
	  		void move(Background*);
	  		bool attack(SDL_Rect,Background*);
	  		void set_clips();
	  			SDL_Rect clipbody[2];
	  			SDL_Rect clipA[5][2];
	  			SDL_Rect clipfang[1];
	  			SDL_Rect clipst[3];
	  			int paralleloffSet;
	  			int verticaloffSet;
	  			int fangx[4];
	  			int fangy[4];
	  			int state; //>10:attack <10:not attack
	  			int parallelvelocity;
	  			int verticalvelocity;
	  			int hp;
	  			int damage;  //to mr
	  			int frame;
	  		    double oldazimuth[4];
	  		    bool ifst;
	};

	 class TV{
	public:
		TV(int ,int);
		bool ifbehit(SDL_Rect);
		void acting(Superugly&,Background*);
	private:
		bool isdead();
		int paralleloffSet;
		int verticaloffSet;
		void set_clips();
		void move(Background*);
		void attack(SDL_Rect);
		SDL_Rect clip[8];
		int state; //11:attack
		int parallelvelocity;
		int verticalvelocity;
		int hp;
		int damage;  //to mr
		int frame;
	};

	 class MINI{
	 public:
	 		MINI(int ,int);
	 		bool ifbehit(SDL_Rect);
	 		void acting(Superugly,Background*);
	 private:
	 		bool isdead();
	 		void move(int,Background*);
	 		void set_clips();
	 		SDL_Rect clip[8];
	 		int paralleloffSet;
	 		int verticaloffSet;
	 		int parallelvelocity;
	 		int verticalvelocity;
	 		int hp;
	 		int frame;

	};



	 class TML{
	 public:
		 TML(int ,int);
		 void acting(Superugly&,Background*);
		 bool ifbehit(SDL_Rect);
	 private:
		 bool isdead();
		 int paralleloffSet;
		 int verticaloffSet;
		 void move(Background*);
		 void attack(SDL_Rect);
		 void set_clips();
		 SDL_Rect clipbody[2];
		 SDL_Rect clipbook[2];
		 SDL_Rect clipbookA[2];
		 int state; //22:attack
		 int parallelvelocity;
		 int verticalvelocity;
		 int hp;
		 int damage;  //to mr
		 int frame;
	};


 bool load_pic(string);
double getazimuth(int ,int ,int,int );
void loadmus(char*);

#endif /* BBOS_H_ */
