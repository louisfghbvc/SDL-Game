/*
 * useplace.h
 *
 *  Created on: 2017¦~6¤ë3¤é
 *      Author: ASUS
 */

#include "..\header\SDLtool.h"
#include "..\header\map.h"
#ifndef SRC_USEPLACE_H_
#define SRC_USEPLACE_H_

class useplace{
public:
	void setclips();
	void showplace();
	void showkey();
	bool loadprop();
	void cleanup();
	void showuseprop();
	int which;//-1~2;
	int keynum[4];
};
class magicbook{
public:
	magicbook(int=0,int=0);
	void showbook(int x,int y);
	bool touch(int x,int y);
	SDL_Rect place;
	int flag;//decide if be taken
};
class ziaboo{
public:
	ziaboo(int=0,int=0);
	void showziaboo();
	bool touch(SDL_Rect);
	SDL_Rect place;
	int flag;//decide if be taken
};
class powerbat{
public:
	powerbat(int=0,int=0);
	void showbat();
	bool touch(SDL_Rect);
	SDL_Rect place;
	int flag;//decide if be taken
};
#endif /* SRC_USEPLACE_H_ */
