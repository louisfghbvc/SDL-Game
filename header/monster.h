/*
 * monster.h
 *
 *  Created on: 2017¦~6¤ë14¤é
 *      Author: ASUS
 */

#include "..\header\SDLtool.h"

#ifndef SRC_MONSTER_H_
#define SRC_MONSTER_H_
class monster_BG
{
    private:

    //Its animation status
    int status;

    int status2;

    int timecnt;

    int Hp;

    int Hpflag;

    int hand_velocity;

    int cd;

    int shoot;

    public:
    //Initializes the variables
    monster_BG(int ,int );

    //The offset
    SDL_Rect place;
    SDL_Rect handplace;

    void loadBG();

    void setclips();
    //Handles input
    void cleanup();

    //Shows the stick figure
    void show();

    bool beattack(SDL_Rect);

    void HandleHP(SDL_Rect);

    void handmove(SDL_Rect thing);

    void firebook();

    void crutch();

    void HpTime();

    bool isDead();
};
class monster_ER
{
	private:

    //Its rate of movement
    int velocity;

    //Its animation status
    int status;

    int status2;

    int status3;

    int timecnt;

    int Hp;

    int Hpflag;

    public:
    //Initializes the variables
    monster_ER(int ,int );

    //The offset
	SDL_Rect place;

	void loadER();

	void setclips();
    //Handles input
    void handle_events();
    void cleanup();
    //Moves the stick figure
    void move();

    //Shows the stick figure
    void show(SDL_Rect);

    bool isattack(SDL_Rect);

    bool beattack(SDL_Rect);

    void HandleHP(SDL_Rect);

    void Hptime();

    bool isDead();
};
class monster_score_0
{
    private:

    //Its rate of movement
    int velocity;

    int Hp;
    //Its animation status
    int status;

    int status2;

    int Hpflag;

    int timecnt;

    public:
    //Initializes the variables
    monster_score_0(int ,int );

    //The offset
    SDL_Rect place;

    void loadscore0();

    void setclips();

    void cleanup();
    //Moves the stick figure
    void move();

    //Shows the stick figure
    void show(SDL_Rect);

    bool isattack(SDL_Rect);

    bool beattack(SDL_Rect);

    void HandleHP(SDL_Rect);

    void Hptime();

    bool isDead();

    void firebook();

    void crutch();
};
class monster_score_39
{
    private:

    //Its rate of movement
    int velocity;

    //Its current frame
    int frame;

    //Its animation status
    int status;

    int status2;

    int Hp;

    int status3;

    int Hpflag;

    int timecnt;

    public:
    //Initializes the variables
    monster_score_39(int ,int );

    //The offset
    SDL_Rect place;

    void setclips();

    void cleanup();
    //Moves the stick figure
    void move();

    void loadscore39();
    //Shows the stick figure
    void show(SDL_Rect);

    bool isattack(SDL_Rect);

    bool beattack(SDL_Rect);
    void HandleHP(SDL_Rect);

    void Hptime();

    bool isDead();

    void firebook();

    void crutch();
};
class monster_score_59
{
    private:

    //Its rate of movement
    int velocity;

    //Its animation status
    int status;

    int status2;

    int Hp;

    public:
    //Initializes the variables
    monster_score_59(int ,int );

    //The offset
    SDL_Rect place;

    void loadscore59();

    void setclips();

    void cleanup();
    //Moves the stick figure
    void move();

    //Shows the stick figure
    void show(SDL_Rect);

    bool isattack(SDL_Rect);

    bool beattack(SDL_Rect);

    void HandleHP(SDL_Rect);

    bool isDead();

    void firebook();

    void crutch();

};
class monster_TC
{
	private:

    //Its rate of movement
    int velocity;

    //Its current frame
    int frame;

    //Its animation status
    int status;

    int status2;

    int status3;

    int timecnt;

    int Hp;

    int Hpflag;

    public:
    //Initializes the variables
    monster_TC(int ,int );

    //The offset
	SDL_Rect place;

	void loadTC();

	void setclips();
    //Handles input
    void handle_events();
    void cleanup();
    //Moves the stick figure
    void move();

    //Shows the stick figure
    void show(SDL_Rect);

    bool isattack(SDL_Rect);

    bool beattack(SDL_Rect);

    void HandleHP(SDL_Rect);

    void Hptime();

    bool isDead();
};


#endif /* SRC_MONSTER_H_ */
