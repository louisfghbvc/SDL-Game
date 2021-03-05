/*
 * umo_rock.h
 *
 *  Created on: 2017¦~6¤ë4¤é
 *      Author: ASUS
 */
#include "..\header\SDLtool.h"
#ifndef SRC_UMO_ROCK_H_
#define SRC_UMO_ROCK_H_

class umo_rock
{
public:
	umo_rock();
	void setplace(SDL_Rect);
	int rockdown;
	SDL_Rect rplace;
	int g;//v
};

#endif /* SRC_UMO_ROCK_H_ */
