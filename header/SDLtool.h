/*
 * SDLtool.h
 *
 *  Created on: 2017¦~6¤ë4¤é
 *      Author: ASUS
 */
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
using namespace std;
#ifndef SRC_SDLTOOL_H_
#define SRC_SDLTOOL_H_

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define SCREEN_BPP 32
#define FRAMES_PER_SECOND 10

class Timer
{
private:
	int startTicks;
public:
	Timer(void);
	void start(void);
	int getTicks(void);
};
SDL_Surface *load_image_alpha(string filename);
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
bool init(void);

#endif /* SRC_SDLTOOL_H_ */
