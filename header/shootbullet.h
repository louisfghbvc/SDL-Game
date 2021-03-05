/*
 * shootbullet.h
 *
 *  Created on: 2017¦~5¤ë29¤é
 *      Author: ASUS
 */

#include <SDL.h>
#ifndef SRC_SHOOTBULLET_H_
#define SRC_SHOOTBULLET_H_

class bullet
{
public:

	void showbullet();

	bullet();

	SDL_Rect bulletplace;
	SDL_Rect clipbullet;
	int shoot;
	//0 is left,1 is right
	int direct;
	void dofixx();
	void undofixx();
	void load_bullet();
	void cleanup();
private:
	int v;
	int cd;
};
#endif /* SRC_SHOOTBULLET_H_ */
