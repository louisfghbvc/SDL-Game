/*
 * middlemonster.h
 *
 *  Created on: 2017�~6��10��
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
	void show();//��ܹB�]
	void moverock();
	void showrock();
	bool beattack(SDL_Rect);
	void HandleHP(SDL_Rect);
	void handleFB();
	void handlebat();
	void Hptime();
	bool isDead();
	SDL_Rect place;//�B�]'s place
	int status3;//���� 1
	int atkcd;//50
	umo_rock a;//a rock
private:
	int status;//��0�k1
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
	void movehamdt();//���ʤ��Y
	void movehandm();//���ʤ��u
	void cleanup();
	void show();//��ܥv�ܩi
	void showhandt();
	void showhandm();
	bool beattack(SDL_Rect);
	void HandleHP(SDL_Rect);
	void handleFB();
	void handlebat();
	void Hptime();
	bool isDead();
	SDL_Rect place;//�v�ܩi's place
	SDL_Rect handplace;//��
	SDL_Rect handmplace;//����
	int status3;//���� 1
	int atkcd;//
private:
	int status;//��0�k1
	int v;//���ʳt��
	int Hp;
	int Hpflag;
	int timecnt;
	int hv;//��t��
	int hd;//��V

};
#endif /* SRC_MIDDLEMONSTER_H_ */
