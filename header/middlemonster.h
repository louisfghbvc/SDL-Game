/*
 * middlemonster.h
 *
 *  Created on: 2017年6月10日
 *      Author: ASUS
 */

#include "..\header\umo_rock.h"
#include "..\header\SDLtool.h"
#ifndef SRC_MIDDLEMONSTER_H_
#define SRC_MIDDLEMONSTER_H_
#define  middle_WIDTH 120
#define  middle_HEIGHT 150
class umo{
public:
	umo(int x=0,int y= 0);
	void load_umo_files();
	void set_umo_clips();
	void umomove();
	void cleanup();
	void show();//顯示運魔
	void moverock();
	void showrock();
	bool beattack(SDL_Rect);
	void HandleHP(SDL_Rect);
	void handleFB();
	void handlebat();
	void Hptime();
	bool isDead();
	SDL_Rect place;//運魔's place
	int status3;//攻擊 1
	int atkcd;//50
	umo_rock a;//a rock
private:
	int status;//左0右1
	int v;
	int hv;
	int Hp;
	int Hpflag;
	int timecnt;
};

class skymo{
public:
	skymo(int=0,int=0);
	void load_skymo_files();
	void set_clips();
	void cleanup();
	void showpic(SDL_Rect);
	bool beattack(SDL_Rect);
	void HandleHp(SDL_Rect);
	void handleFB();
	void handlebat();
	void sometime();
	bool isDead();
	SDL_Rect place;
	SDL_Rect shplace;
	int atkt;
private:
	int Hp;
	int Hpflag;
	int timecnt;
	int status;
	int status2;
	int shstatus;
	int cd;
	int frame;
};
class mato{
public:
	mato(int=0,int=0);
	void load_mato_flies();
	void set_clips();
	void cleanup();
	void move();
	void show();
	SDL_Rect place;
private:
	int status;
	int v;
	int angle;
};
class minibox{
public:
	minibox(int=0,int=0);
	void load_box_flies();
	void set_bclips();
	void cleanup();
	void show();
	void handle_boom(SDL_Rect);
	SDL_Rect place;
private:
	int status;//0 boom
};
class sly{
public:
	sly(int x=0,int y= 0);
	void load_sly_files();
	void set_sly_clips();
	void slymove(SDL_Rect);
	void movehamdt();//移動手頭
	void movehandm();//移動手臂
	void cleanup();
	void show();//顯示史萊姆
	void showhandt();
	void showhandm();
	bool beattack(SDL_Rect);
	void HandleHP(SDL_Rect);
	void handleFB();
	void handlebat();
	void Hptime();
	bool isDead();
	SDL_Rect place;//史萊姆's place
	SDL_Rect handplace;//手
	SDL_Rect handmplace;//伸長
	int status3;//攻擊 1
	int atkcd;//
private:
	int status;//左0右1
	int v;//移動速度
	int Hp;
	int Hpflag;
	int timecnt;
	int hv;//手速度
	int hd;//方向

};
#endif /* SRC_MIDDLEMONSTER_H_ */
