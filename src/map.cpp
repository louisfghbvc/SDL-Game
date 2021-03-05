/*
 * map.cpp
 *
 *  Created on: 2017¦~5¤ë29¤é
 *      Author: jason
 */
#include <iostream>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "..\header\map.h"
#include "..\header\SDLtool.h"
#include "..\header\middlemonster.h"

extern SDL_Surface *screen;
SDL_Surface *material[7];
SDL_Surface *door_image[2];
SDL_Surface *key_image[9];
SDL_Surface *box_image[2];
SDL_Surface *heal_image[2];
SDL_Surface *ornament_image[5];
SDL_Rect background_clips;
SDL_Rect key_clips[8];
mato mato1(150,550);

void set_background_clips(void)
{
    background_clips.x = 0;
    background_clips.y = 0;
    background_clips.w = MATERIAL_LONG;
    background_clips.h = MATERIAL_LONG;

    key_clips[0].x = 70 * 4;
    key_clips[0].y = 0;
    key_clips[0].w = 70;
    key_clips[0].h = 30;

    key_clips[1].x = 0;
    key_clips[1].y = 0;
    key_clips[1].w = 70;
    key_clips[1].h = 30;

    key_clips[2].x = 70 * 1;
    key_clips[2].y = 0;
    key_clips[2].w = 70;
    key_clips[2].h = 30;

    key_clips[3].x = 70 * 2;
    key_clips[3].y = 0;
    key_clips[3].w = 70;
    key_clips[3].h = 30;

    key_clips[4].x = 70 * 3;
    key_clips[4].y = 0;
    key_clips[4].w = 70;
    key_clips[4].h = 30;

    key_clips[5].x = 70 * 5;
    key_clips[5].y = 0;
    key_clips[5].w = 70;
    key_clips[5].h = 30;

    key_clips[6].x = 70 * 6;
    key_clips[6].y = 0;
    key_clips[6].w = 70;
    key_clips[6].h = 30;

    key_clips[7].x = 70 * 7;
    key_clips[7].y = 0;
    key_clips[7].w = 70;
    key_clips[7].h = 30;
}
bool load_background_files(void)
{
    material[0] = load_image_alpha(".\\struct\\wood25X25.png");
    material[1] = load_image_alpha(".\\struct\\rock25X25.png");
    material[2] = load_image_alpha(".\\struct\\concrete25X25.png");
    material[3] = load_image_alpha(".\\struct\\bric25X25.png");
    material[4] = load_image_alpha(".\\struct\\FE25X25.png");
    material[5] = load_image_alpha(".\\struct\\blistone25X25.png");
    material[6] = load_image_alpha(".\\struct\\obsidian25X25.png");
    if(material[0] == NULL || material[1] == NULL || material[2] == NULL || material[3] == NULL || material[4] == NULL || material[5] == NULL || material[6] == NULL)
        return false;
    door_image[0] = load_image_alpha(".\\struct\\doorsv.png");
    door_image[1] = load_image_alpha(".\\struct\\doors.png");
    if(door_image[0] == NULL || door_image[1] == NULL)
        return false;
    key_image[0] = load_image_alpha(".\\struct\\keymf30X10.png");
    key_image[1] = load_image_alpha(".\\struct\\keym130X10.png");
    key_image[2] = load_image_alpha(".\\struct\\keym230X10.png");
    key_image[3] = load_image_alpha(".\\struct\\keym330X10.png");
    key_image[4] = load_image_alpha(".\\struct\\keym430X10.png");
    key_image[5] = load_image_alpha(".\\struct\\key30X10.png");
    key_image[6] = load_image_alpha(".\\struct\\keys230X10.png");
    key_image[7] = load_image_alpha(".\\struct\\keys330X10.png");
    key_image[8] = load_image_alpha(".\\struct\\keys70X30.png");
    if(key_image[0] == NULL || key_image[1] == NULL || key_image[2] == NULL || key_image[3] == NULL || key_image[4] == NULL || key_image[5] == NULL || key_image[6] == NULL || key_image[7] == NULL || key_image[8] == NULL)
        return false;
    box_image[0] = load_image_alpha(".\\struct\\boxC100X100.png");
    box_image[1] = load_image_alpha(".\\struct\\boxo100X135.png");
    if(box_image[0] == NULL || box_image[1] == NULL)
        return false;
    ornament_image[0] = load_image_alpha(".\\struct\\light120X110.png");
    ornament_image[1] = load_image_alpha(".\\struct\\fire100X150.png");
    ornament_image[2] = load_image_alpha(".\\struct\\downlamp50X35.png");
    ornament_image[3] = load_image_alpha(".\\struct\\uplamp50X55.png");
    ornament_image[4] = load_image_alpha(".\\struct\\light2150X60.png");
    if(ornament_image[0] == NULL || ornament_image[1] == NULL || ornament_image[2] == NULL || ornament_image[3] == NULL || ornament_image[4] == NULL)
        return false;
    heal_image[0] = load_image_alpha(".\\struct\\onlyable45X45.png");
    heal_image[1] = load_image_alpha(".\\struct\\plate200X64.png");
    if(heal_image[0] == NULL || heal_image[1] == NULL)
        return false;
    return true;
}
void clean_background(void)
{
    int i;

    for(i = 0; i < 7; ++i)
        SDL_FreeSurface(material[i]);
    for(i = 0; i < 2; ++i)
        SDL_FreeSurface(door_image[i]);
    for(i = 0; i < 9; ++i)
        SDL_FreeSurface(key_image[i]);
    for(i = 0; i < 2; ++i)
        SDL_FreeSurface(box_image[i]);
    for(i = 0; i < 5; ++i)
        SDL_FreeSurface(ornament_image[i]);
    for(i = 0; i < 2; ++i)
        SDL_FreeSurface(heal_image[i]);
}
Floor::Floor(void)
{
    int i;

    for(i = 0; i < 5; ++i)
        fnum[i] = -1;
    width_num = 0;
    for(i = 0; i < 2; ++i)
        image[i] = NULL;
}
Floor::Floor(SDL_Surface *im[], int num[])
{
    int i;

    for(i = 0; i < 5; ++i)
        fnum[i] = num[i];
    width_num = fnum[2] / MATERIAL_LONG;
    image[0] = im[0];
    if(fnum[4] != 0)
        image[1] = im[1];
}
int Floor::getx(void) const
{
    return fnum[0];
}
int Floor::gety(void) const
{
    return fnum[1];
}
int Floor::getw(void) const
{
    return fnum[2];
}
int Floor::geth(void) const
{
    return (fnum[3] + fnum[4]);
}
bool Floor::xrange(int x)
{
    if(fnum[0] <= x && x <= (fnum[0] + fnum[2]))
        return true;
    return false;
}
bool Floor::yrange(int y)
{
    if(fnum[1] <= y && y <= (fnum[1] + fnum[3] + fnum[4]))
        return true;
    return false;
}
void Floor::show(void)
{
    int i;

    for(i = 0; i < (width_num * (fnum[3] / MATERIAL_LONG)); ++i)
        apply_surface(fnum[0] + (MATERIAL_LONG * (i % width_num)), fnum[1] + (MATERIAL_LONG * (i / width_num)), image[0], screen, &background_clips);
    for(i = 0; i < (width_num * (fnum[4] / MATERIAL_LONG)); ++i)
        apply_surface(fnum[0] + (MATERIAL_LONG * (i % width_num)), fnum[1] + fnum[3] + (MATERIAL_LONG * (i / width_num)), image[1], screen, &background_clips);
}
Terrace::Terrace(void)
{
    int i;

    for(i = 0; i < 4; ++i)
        tnum[i] = -1;
    width_num = 0;
    image = NULL;
}
Terrace::Terrace(SDL_Surface *im, int num[])
{
    int i;

    for(i = 0; i < 4; ++i)
        tnum[i] = num[i];
    width_num = tnum[2] / MATERIAL_LONG;
    image = im;
}
int Terrace::getx(void) const
{
    return tnum[0];
}
int Terrace::gety(void) const
{
    return tnum[1];
}
int Terrace::getw(void) const
{
    return tnum[2];
}
int Terrace::geth(void) const
{
    return tnum[3];
}
bool Terrace::xrange(int x)
{
    if(tnum[0] <= x && x <= (tnum[0] + tnum[2]))
        return true;
    return false;
}
bool Terrace::yrange(int y)
{
    if(tnum[1] <= y && y <= (tnum[1] + tnum[3]))
        return true;
    return false;
}
void Terrace::show(void)
{
    int i;

    for(i = 0; i < (width_num * (tnum[3] / MATERIAL_LONG)); ++i)
        apply_surface(tnum[0] + (MATERIAL_LONG * (i % width_num)), tnum[1] + (MATERIAL_LONG * (i / width_num)), image, screen, &background_clips);
}
Healsystem::Healsystem()
{
    int i;

    for(i = 0; i < 3; ++i)
        hnum[i] = -1;
}
Healsystem::Healsystem(int num[])
{
    int i;

    for(i = 0; i < 3; ++i)
        hnum[i] = num[i];
}
bool Healsystem::xrange(int x)
{
    if(hnum[0] <= x && x <= (hnum[0] + 200))
        return true;
    return false;
}
bool Healsystem::yrange(int y)
{
    if(hnum[1] <= y && y <= (hnum[1] + 64))
        return true;
    return false;
}
bool Healsystem::use(void)
{
    if(hnum[2] > 0)
    {
        --hnum[2];
        return true;
    }
    return false;
}
void Healsystem::show(void)
{
    apply_surface(hnum[0], hnum[1], heal_image[1], screen, NULL);
    if(hnum[2] > 0)
        apply_surface(hnum[0] + 100 - 20, hnum[1] - 20, heal_image[0], screen, NULL);
}
Box::Box()
{
    int i;

    for(i = 0; i < 2; ++i)
        bxnum[i] = -1;
    open = false;
}
Box::Box(int num[])
{
    int i;

    for(i = 0; i < 2; ++i)
        bxnum[i] = num[i];
    open = false;
}
bool Box::openbox(int x, int y, int w, int h)
{
    bool ans = false;

    if(bxnum[0] <= x && x <= (bxnum[0] + 100) && bxnum[1] <= y && y <= (bxnum[1] + 100) && open == false)
        ans = true;
    if(bxnum[0] <= x && x <= (bxnum[0] + 100) && bxnum[1] <= (y + h) && (y + h) <= (bxnum[1] + 100) && open == false)
        ans = true;
    if(bxnum[0] <= (x + w) && (x + w) <= (bxnum[0] + 100) && bxnum[1] <= y && y <= (bxnum[1] + 100) && open == false)
        ans = true;
    if(bxnum[0] <= (x + w) && (x + w) <= (bxnum[0] + 100) && bxnum[1] <= (y + h) && (y + h) <= (bxnum[1] + 100) && open == false)
        ans = true;
    if(ans)
    {
        open = true;
        return true;
    }
    return false;
}
void Box::show(void)
{
    if(open)
        apply_surface(bxnum[0], bxnum[1] - 35, box_image[1], screen, NULL);
    else
        apply_surface(bxnum[0], bxnum[1], box_image[0], screen, NULL);
}
Key::Key()
{
    int i;

    for(i = 0; i < 3; ++i)
        knum[i] = -1;
    image = NULL;
    appear = false;
}
Key::Key(SDL_Surface *im, int num[])
{
    int i;

    for(i = 0; i < 3; ++i)
        knum[i] = num[i];
    image = im;
    appear = true;
}
int Key::getkeynum(void)
{
    return knum[2];
}
bool Key::keyrange(int x, int y, int w, int h)
{
    bool ans = false;
    if(x <= knum[0] && knum[0] <=  (x + w) && y <= knum[1] && knum[1] <= (y + h)&& appear == true)
        ans = true;
    if(x <= knum[0] && knum[0] <=  (x + w) && y <= (knum[1] + 10) && (knum[1] + 10) <= (y + h)&& appear == true)
        ans = true;
    if(x <= (knum[0] + 30) && (knum[0] + 30) <=  (x + w) && y <= knum[1] && knum[1] <= (y + h)&& appear == true)
        ans = true;
    if(x <= (knum[0] + 30) && (knum[0] + 30) <=  (x + w) && y <= (knum[1] + 10) && (knum[1] + 10) <= (y + h)&& appear == true)
        ans = true;
    return ans;
}
bool Key::getkey(int x, int y, int w, int h)
{
    if(keyrange(x, y, w, h))
    {
        appear = false;
        return true;
    }
    return false;
}
void Key::show(void)
{
    if(appear)
        apply_surface(knum[0], knum[1], image, screen, NULL);
}
Door::Door(void)
{
    int i;

    for(i = 0; i < 5; ++i)
        dnum[i] = -1;
    mapnum = -1;
    keylife = -1;
    image = NULL;
    set_clips(0);
}
Door::Door(SDL_Surface *im, int num[])
{
    int i;

    for(i = 0; i < 5; ++i)
        dnum[i] = num[i];
    mapnum = dnum[4];
    keylife = dnum[3];
    image = im;
    set_clips(dnum[2]);
}
int Door::getdoornum(void)
{
    return dnum[2];
}
int Door::getmapnum(void)
{
    return mapnum;
}
int Door::getx(void)
{
    return dnum[0];
}
int Door::gety(void)
{
    return dnum[1];
}
void Door::set_clips(int t)
{
    int i;

    switch(t)
    {
    case 0:
        for(i = 0; i < 3; ++i)
        {
            door_clips[i].x = 200;
            door_clips[i].y = 200 * i;
            door_clips[i].w = 40;
            door_clips[i].h = 200;
        }
        break;
    case 1:
        if(image == door_image[1])
            for(i = 0; i < 3; ++i)
            {
                door_clips[i].x = 200;
                door_clips[i].y = 200 * i;
                door_clips[i].w = 200;
                door_clips[i].h = 200;
            }
        else
            for(i = 0; i < 3; ++i)
            {
                door_clips[i].x = 40;
                door_clips[i].y = 200 * i;
                door_clips[i].w = 40;
                door_clips[i].h = 200;
            }
        break;
    case 2:
        for(i = 0; i < 3; ++i)
        {
            door_clips[i].x = 80;
            door_clips[i].y = 200 * i;
            door_clips[i].w = 40;
            door_clips[i].h = 200;
        }
        break;
    case 3:
        for(i = 0; i < 3; ++i)
        {
            door_clips[i].x = 0;
            door_clips[i].y = 0;
            door_clips[i].w = 200;
            door_clips[i].h = 200;
        }
        break;
    case 4:
        for(i = 0; i < 3; ++i)
        {
            door_clips[i].x = 160;
            door_clips[i].y = 200 * i;
            door_clips[i].w = 40;
            door_clips[i].h = 200;
        }
        break;
    case 5:
        for(i = 0; i < 3; ++i)
        {
            door_clips[i].x = 160;
            door_clips[i].y = 200 * i;
            door_clips[i].w = 40;
            door_clips[i].h = 200;
        }
        break;
    case 6:
        for(i = 0; i < 3; ++i)
        {
            door_clips[i].x = 1400;
            door_clips[i].y = 200 * i;
            door_clips[i].w = 200;
            door_clips[i].h = 200;
        }
        break;
    case 7:
        for(i = 0; i < 3; ++i)
        {
            door_clips[i].x = 320;
            door_clips[i].y = 200 * i;
            door_clips[i].w = 40;
            door_clips[i].h = 200;
        }
        break;
    case 8:
        for(i = 0; i < 3; ++i)
        {
            door_clips[i].x = 0;
            door_clips[i].y = 200 * i;
            door_clips[i].w = 40;
            door_clips[i].h = 200;
        }
        break;
    case 9:
        for(i = 0; i < 3; ++i)
        {
            door_clips[i].x = 0;
            door_clips[i].y = 200 * i;
            door_clips[i].w = 200;
            door_clips[i].h = 200;
        }
        break;
    case 10:
        for(i = 0; i < 3; ++i)
        {
            door_clips[i].x = 1000;
            door_clips[i].y = 200 * i;
            door_clips[i].w = 200;
            door_clips[i].h = 200;
        }
        break;
    }
}
bool Door::xrange(int x)
{
    switch(dnum[2])
    {
    case 0:
    case 2:
    case 4:
    case 7:
    case 8:
        if(dnum[0] <= x && x <= (dnum[0] + 40))
            return true;
        break;
    case 1:
        if(image == door_image[1])
        {
            if((dnum[0] + 20) <= x && x <= (dnum[0] + 180))
                return true;
        }
        else if(dnum[0] <= x && x <= (dnum[0] + 40))
            return true;
        break;
    case 3:
    case 5:
    case 6:
    case 9:
    case 10:
        if((dnum[0] + 20) <= x && x <= (dnum[0] + 180))
            return true;
        break;
    }
    return false;
}
bool Door::yrange(int y)
{
    switch(dnum[2])
    {
    case 0:
    case 2:
    case 4:
    case 7:
    case 8:
        if(dnum[1] <= y && y <= (dnum[1] + 200))
            return true;
        break;
    case 1:
        if(image == door_image[1])
        {
            if(dnum[1] <= y && y <= (dnum[1] + 200))
                return true;
        }
        else if(dnum[1] <= y && y <= (dnum[1] + 200))
            return true;
        break;
    case 3:
    case 5:
    case 9:
    case 10:
        if(dnum[1] <= y && y <= (dnum[1] + 200))
            return true;
        break;
    case 6:
        if((dnum[1] - 200) <= y && y <= dnum[1])
            return true;
        break;
    }
    return false;
}
bool Door::isNotLocked(void)
{
    if(keylife > 0)
        return false;
    return true;
}
int Door::open(void)
{
    --keylife;
    if(keylife < 0)
        return mapnum;
    return -1;
}
void Door::show(void)
{
    switch(dnum[2])
    {
    case 0:
    case 4:
        switch(keylife)
        {
        case 2:
            apply_surface(dnum[0], dnum[1], image, screen, &door_clips[0]);
            break;
        case 1:
            apply_surface(dnum[0], dnum[1], image, screen, &door_clips[1]);
            break;
        default:
            apply_surface(dnum[0], dnum[1], image, screen, &door_clips[2]);
            break;
        }
        break;
    case 1:
        if(image == door_image[1])
            switch(keylife)
            {
            case 1:
                apply_surface(dnum[0], dnum[1], image, screen, &door_clips[0]);
                break;
            case 0:
                apply_surface(dnum[0], dnum[1], image, screen, &door_clips[1]);
                break;
            default:
                apply_surface(dnum[0], dnum[1], image, screen, &door_clips[2]);
                break;
            }
        else
            switch(keylife)
            {
            case 1:
                apply_surface(dnum[0], dnum[1], image, screen, &door_clips[0]);
                break;
            default:
                apply_surface(dnum[0], dnum[1], image, screen, &door_clips[1]);
                break;
            }
        break;
    case 6:
        switch(keylife)
        {
        case 1:
            apply_surface(dnum[0], dnum[1], image, screen, &door_clips[0]);
            break;
        case 0:
            apply_surface(dnum[0], dnum[1], image, screen, &door_clips[1]);
            break;
        default:
            apply_surface(dnum[0], dnum[1], image, screen, &door_clips[2]);
            break;
        }
        break;
    case 2:
    case 3:
    case 5:
    case 7:
        switch(keylife)
        {
        case 1:
            apply_surface(dnum[0], dnum[1], image, screen, &door_clips[0]);
            break;
        default:
            apply_surface(dnum[0], dnum[1], image, screen, &door_clips[1]);
            break;
        }
        break;
    case 8:
    case 9:
    case 10:
        switch(keylife)
        {
        case 0:
            apply_surface(dnum[0], dnum[1], image, screen, &door_clips[0]);
            break;
        default:
            apply_surface(dnum[0], dnum[1], image, screen, &door_clips[1]);
            break;
        }
        break;
    }
}
Background::Background(void)
{
    doornum = 0;
    bimage0 = NULL;
    height_num = 0;
}
Background::~Background(void)
{

}
Background::Background(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[])
{
    int flonum0[5] = {fnum[0], fnum[1], fnum[2], fnum[3], fnum[4]}, flonum1[5] = {fnum[5], fnum[6], fnum[7], fnum[8], fnum[9]};
    SDL_Surface *floim0[2] = {fim[0], fim[1]}, *floim1[2] = {fim[2], fim[3]};
    Floor f0(floim0, flonum0), f1(floim1, flonum1);
    int dornum0[5] = {dnum[0], dnum[1], dnum[2], dnum[3], dnum[4]};
    Door d0(dim[0], dornum0);

    flo0 = f0;
    flo1 = f1;
    door[0] = d0;
    doornum = 1;
    height_num = (SCREEN_HEIGHT - flo0.geth() - flo1.geth()) / MATERIAL_LONG;
    if(dim[1] != NULL)
    {
        int dornum1[5] = {dnum[5], dnum[6], dnum[7], dnum[8], dnum[9]};
        Door d1(dim[1], dornum1);

        door[1] = d1;
        ++doornum;
    }
    if(dim[2] != NULL)
    {
        int dornum2[5] = {dnum[10], dnum[11], dnum[12], dnum[13], dnum[14]};
        Door d2(dim[2], dornum2);

        door[2] = d2;
        ++doornum;
    }
    bimage0 = bim;
}
bool Background::walkRange(int x, int y, int w, int h)
{
    if(x < 0)
        return false;
    if((x + w) > 1200)
        return false;
    if(x < flo0.getx() && flo0.getx() < (x + w) && y < flo0.gety() && flo0.gety() < (y + h))
        return false;
    if(x < (flo0.getx() + flo0.getw()) && (flo0.getx() + flo0.getw()) < (x + w) && y < flo0.gety() && flo0.gety() < (y + h))
        return false;
    if(x < flo1.getx() && flo1.getx() < (x + w) && y < flo1.gety() && flo1.gety() < (y + h))
        return false;
    if(x < (flo1.getx() + flo1.getw()) && (flo1.getx() + flo1.getw()) < (x + w) && y < flo1.gety() && flo1.gety() < (y + h))
        return false;
    return true;
}
bool Background::jumpRange(int x, int y, int w, int h)
{
    if(flo0.xrange(x) && flo0.yrange(y))
        return false;
    if(flo0.xrange(x + w) && flo0.yrange(y))
        return false;
    if(flo1.xrange(x) && flo1.yrange(y))
        return false;
    if(flo1.xrange(x + w) && flo1.yrange(y))
        return false;
    return true;
}
bool Background::downRange(int x, int y, int w, int h)
{
    if(flo1.xrange(x) && flo1.yrange(y + h))
        return false;
    if(flo1.xrange(x + w) && flo1.yrange(y + h))
        return false;
    return true;
}
int Background::walkx(int x, int y, int w, int h)
{
    if(x < 0)
        return 0;
    if((x + w) > 1200)
        return (1200 - w);
    if(x < flo0.getx() && flo0.getx() < (x + w) && y < flo0.gety() && flo0.gety() < (y + h))
        return (flo0.getx() - w);
    if(x < (flo0.getx() + flo0.getw()) && (flo0.getx() + flo0.getw()) < (x + w) && y < flo0.gety() && flo0.gety() < (y + h))
        return (flo0.getx() + flo0.getw());
    if(x < flo1.getx() && flo1.getx() < (x + w) && y < flo1.gety() && flo1.gety() < (y + h))
        return (flo1.getx() - w);
    if(x < (flo1.getx() + flo1.getw()) && (flo1.getx() + flo1.getw()) < (x + w) && y < flo1.gety() && flo1.gety() < (y + h))
        return (flo1.getx() + flo1.getw());
    return -1;
}
int Background::jumpy(int x, int y, int w, int h)
{
    if(flo0.xrange(x) && flo0.yrange(y))
        return (flo0.gety() + flo0.geth());
    if(flo0.xrange(x + w) && flo0.yrange(y))
        return (flo0.gety() + flo0.geth());
    return -1;
}
int Background::downy(int x, int y, int w, int h)
{
    if(flo1.xrange(x) && flo1.yrange(y + h))
        return (flo1.gety() - h);
    if(flo1.xrange(x + w) && flo1.yrange(y + h))
        return (flo1.gety() - h);
    return -1;
}
int Background::enterdoornum(int past)
{
    if(door[0].getmapnum() == past)
        return 0;
    if(doornum >= 2)
        if(door[1].getmapnum() == past)
            return 1;
    if(doornum >= 3)
        if(door[2].getmapnum() == past)
            return 2;
    return -1;
}
int Background::enterx(int n)
{
    if(door[n].getx() + 80 > 1200)
        return (door[n].getx() - 80);
    return door[n].getx();
}
int Background::entery(int n)
{
    return door[n].gety();
}
int Background::theDoor(int x, int y, int w, int h)
{
    if((door[0].xrange(x) && door[0].yrange(y)) || (door[0].xrange(x + w) && door[0].yrange(y)))
        return 0;
    if(doornum >= 2)
        if((door[1].xrange(x) && door[1].yrange(y)) || (door[1].xrange(x + w) && door[1].yrange(y)))
            return 1;
    if(doornum >= 3)
        if((door[2].xrange(x) && door[2].yrange(y)) || (door[2].xrange(x + w) && door[2].yrange(y)))
            return 2;
    return -1;
}
bool Background::theDoorisNotLocked(int n)
{
    return door[n].isNotLocked();
}
int Background::matchtheDoor(int n)
{
    return door[n].getdoornum();
}
int Background::opentheDoor(int n)
{
    return door[n].open();
}
bool Background::thekey(int x, int y, int w, int h)
{
    return false;
}
int Background::getthekey(int x, int y, int w, int h)
{
    return -1;
}
bool Background::openthebox(int x, int y, int w, int h)
{
    return false;
}
bool Background::usehealsystem(int x, int y, int w, int h)
{
    return false;
}
void Background::show(void)
{
    int i;

    for(i = 0; i < (MATERIAL_WIDTH_NUMBER * height_num); ++i)
        apply_surface(MATERIAL_LONG * (i % MATERIAL_WIDTH_NUMBER), flo0.geth() + MATERIAL_LONG * (i / MATERIAL_WIDTH_NUMBER), bimage0, screen, &background_clips);
    flo0.show();
    flo1.show();
    door[0].show();
    if(doornum >= 2)
        door[1].show();
    if(doornum >= 3)
        door[2].show();
}
Map_type1::Map_type1(void)
    :Background()
{

}
Map_type1::Map_type1(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[])
{
    int newfnum[10] = {0, 0, SCREEN_WIDTH, fnum[0], 0, 0, SCREEN_HEIGHT - fnum[1], SCREEN_WIDTH, fnum[1], 0};
    SDL_Surface *newfim[4] = {fim[0], NULL, fim[1], NULL};

    int flonum0[5] = {newfnum[0], newfnum[1], newfnum[2], newfnum[3], newfnum[4]}, flonum1[5] = {newfnum[5], newfnum[6], newfnum[7], newfnum[8], newfnum[9]};
    SDL_Surface *floim0[2] = {newfim[0], newfim[1]}, *floim1[2] = {newfim[2], newfim[3]};
    Floor f0(floim0, flonum0), f1(floim1, flonum1);
    int dornum0[5] = {dnum[0], dnum[1], dnum[2], dnum[3], dnum[4]};
    Door d0(dim[0], dornum0);

    flo0 = f0;
    flo1 = f1;
    door[0] = d0;
    doornum = 1;
    height_num = (SCREEN_HEIGHT - flo0.geth() - flo1.geth()) / MATERIAL_LONG;
    if(dim[1] != NULL)
    {
        int dornum1[5] = {dnum[5], dnum[6], dnum[7], dnum[8], dnum[9]};
        Door d1(dim[1], dornum1);

        door[1] = d1;
        ++doornum;
    }
    if(dim[2] != NULL)
    {
        int dornum2[5] = {dnum[10], dnum[11], dnum[12], dnum[13], dnum[14]};
        Door d2(dim[2], dornum2);

        door[2] = d2;
        ++doornum;
    }
    bimage0 = bim;
}
Map_0::Map_0()
    :Map_type1()
{

}
Map_0::Map_0(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[])
    :Map_type1(bim, fim, fnum, dim, dnum)
{
    SDL_Surface *floim2[2] = {material[5], NULL};
    int flonum2[5] = {850, 700 - 100, 150, 100, 0};
    Floor f2(floim2, flonum2);

    flo2 = f2;
}
bool Map_0::walkRange(int x, int y, int w, int h)
{
    if(Background::walkRange(x, y, w, h))
    {
        if(x < flo2.getx() && flo2.getx() < (x + w) && y < flo2.gety() && flo2.gety() < (y + h))
            return false;
        if(x < (flo2.getx() + flo2.getw()) && (flo2.getx() + flo2.getw()) < (x + w) && y < flo2.gety() && flo2.gety() < (y + h))
            return false;
        return true;
    }
    return Background::walkRange(x, y, w, h);
}
bool Map_0::downRange(int x, int y, int w, int h)
{
    if(Background::downRange(x, y, w, h))
    {
        if(flo2.xrange(x) && flo2.yrange(y + h))
            return false;
        if(flo2.xrange(x + w) && flo2.yrange(y + h))
            return false;
        return true;
    }
    return Background::downRange(x, y, w, h);
}
int Map_0::walkx(int x, int y, int w, int h)
{
    if(Background::walkx(x, y, w, h) == -1)
    {
        if(x < flo2.getx() && flo2.getx() < (x + w) && y < flo2.gety() && flo2.gety() < (y + h))
            return (flo2.getx() - w);
        if(x < (flo2.getx() + flo2.getw()) && (flo2.getx() + flo2.getw()) < (x + w) && y < flo2.gety() && flo2.gety() < (y + h))
            return (flo2.getx() + flo2.getw());
        return -1;
    }
    return Background::walkx(x, y, w, h);
}
int Map_0::downy(int x, int y, int w, int h)
{
    if(Background::downy(x, y, w, h) == -1)
    {
        if(flo2.xrange(x) && flo2.yrange(y + h))
            return (flo2.gety() - h);
        if(flo2.xrange(x + w) && flo2.yrange(y + h))
            return (flo2.gety() - h);
        return -1;
    }
    return Background::downy(x, y, w, h);
}
void Map_0::show(void)
{
    Background::show();
    flo2.show();
    apply_surface(300 - 25, 200 - 15, ornament_image[2], screen, NULL);
    apply_surface(1200 - 325, 200 - 15, ornament_image[2], screen, NULL);
    apply_surface(100 - 20, 400 - 110, ornament_image[0], screen, NULL);
}
Map_1::Map_1()
    :Map_type1()
{
    bimage1 = NULL;
}
Map_1::Map_1(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[])
    :Map_type1(bim, fim, fnum, dim, dnum)
{
    SDL_Surface *floim2[2] = {material[0], NULL};
    int flonum2[5] = {1200 - 200, 700 - 100, 200, 100, 0};
    Floor f2(floim2, flonum2);

    flo2 = f2;

    int bxnum[2] = {400, 700 - 100};
    Box b0(bxnum);

    bo0 = b0;
    int knum[3] = {1200 - 115, 700 - 110, 0};
    Key k0(key_image[0], knum);

    ke0 = k0;
    bimage1 = material[0];
}
bool Map_1::walkRange(int x, int y, int w, int h)
{
    if(Background::walkRange(x, y, w, h))
    {
        if(x < flo2.getx() && flo2.getx() < (x + w) && y < flo2.gety() && flo2.gety() < (y + h))
            return false;
        if(x < (flo2.getx() + flo2.getw()) && (flo2.getx() + flo2.getw()) < (x + w) && y < flo2.gety() && flo2.gety() < (y + h))
            return false;
        return true;
    }
    return Background::walkRange(x, y, w, h);
}
bool Map_1::downRange(int x, int y, int w, int h)
{
    if(Background::downRange(x, y, w, h))
    {
        if(flo2.xrange(x) && flo2.yrange(y + h))
            return false;
        if(flo2.xrange(x + w) && flo2.yrange(y + h))
            return false;
        return true;
    }
    return Background::downRange(x, y, w, h);
}
int Map_1::walkx(int x, int y, int w, int h)
{
    if(Background::walkx(x, y, w, h) == -1)
    {
        if(x < flo2.getx() && flo2.getx() < (x + w) && y < flo2.gety() && flo2.gety() < (y + h))
            return (flo2.getx() - w);
        if(x < (flo2.getx() + flo2.getw()) && (flo2.getx() + flo2.getw()) < (x + w) && y < flo2.gety() && flo2.gety() < (y + h))
            return (flo2.getx() + flo2.getw());
        return -1;
    }
    return Background::walkx(x, y, w, h);
}
int Map_1::downy(int x, int y, int w, int h)
{
    if(Background::downy(x, y, w, h) == -1)
    {
        if(flo2.xrange(x) && flo2.yrange(y + h))
            return (flo2.gety() - h);
        if(flo2.xrange(x + w) && flo2.yrange(y + h))
            return (flo2.gety() - h);
        return -1;
    }
    return Background::downy(x, y, w, h);
}
bool Map_1::thekey(int x, int y, int w, int h)
{
    if(ke0.keyrange(x, y, w, h))
        return true;
    return false;
}
int Map_1::getthekey(int x, int y, int w, int h)
{
    if(ke0.getkey(x, y, w, h))
        return ke0.getkeynum();
    return -1;
}
bool Map_1::openthebox(int x, int y, int w, int h)
{
    if(bo0.openbox(x, y, w, h))
        return true;
    return false;
}
void Map_1::show(void)
{
    int i;

    for(i = 0; i < (MATERIAL_WIDTH_NUMBER * height_num); ++i)
        apply_surface(MATERIAL_LONG * (i % MATERIAL_WIDTH_NUMBER), flo0.geth() + MATERIAL_LONG * (i / MATERIAL_WIDTH_NUMBER), bimage0, screen, &background_clips);
    for(i = 0; i < (MATERIAL_WIDTH_NUMBER * 8); ++i)
        apply_surface(MATERIAL_LONG * (i % MATERIAL_WIDTH_NUMBER), 300 + MATERIAL_LONG * (i / MATERIAL_WIDTH_NUMBER), bimage1, screen, &background_clips);
    flo0.show();
    flo1.show();
    door[0].show();
    if(doornum >= 2)
        door[1].show();
    if(doornum >= 3)
        door[2].show();
    flo2.show();
    bo0.show();
    ke0.show();
}
Map_2::Map_2()
{
    int flonum0[5] = {0, 0, 500, 50, 25};
    int flonum1[5] = {0, 700, 1200, 100, 0};
    int flonum2[5] = {700, 0, 500, 50, 25};
    int flonum3[5] = {500, 700, 200, 100, 0};
    SDL_Surface *floim0[2] = {material[4], material[5]};
    SDL_Surface *floim1[2] = {material[3], NULL};
    SDL_Surface *floim2[2] = {material[4], material[5]};
    SDL_Surface *floim3[2] = {material[6], NULL};
    Floor f0(floim0, flonum0),
          f1(floim1, flonum1),
          f2(floim2, flonum2),
          f3(floim3, flonum3);
    int dornum0[5] = {0, 700 - 200, 8, 0, 0};
    Door d0(door_image[0], dornum0);

    flo0 = f0;
    flo1 = f1;
    flo2 = f2;
    flo3 = f3;
    door[0] = d0;
    doornum = 1;
    height_num = (SCREEN_HEIGHT - flo0.geth() - flo2.geth()) / MATERIAL_LONG;
    int dornum1[5] = {1200 - 40, 700 - 200, 8, 0, 3};
    Door d1(door_image[0], dornum1);

    door[1] = d1;
    ++doornum;
    bimage0 = material[1];
    SDL_Surface *terim[9] = {material[6], material[6], material[6], material[6], material[6], material[5], material[5], material[5], material[5]};
    int ternum[36] = {500, 50, 50, 25,
                      650, 50, 50, 25,
                      400, 200, 400, 25,
                      0, 290, 250, 25,
                      1200 - 250, 290, 250, 25,
                      400, 700 - 280, 100, 25,
                      1200 - 400 - 100, 700 - 280, 100, 25,
                      200, 700 - 140, 200, 25,
                      1200 - 200 - 200, 700 - 140, 200, 25
                     };
    int tmpnum0[4] = {ternum[0], ternum[1], ternum[2], ternum[3]};
    int tmpnum1[4] = {ternum[4], ternum[5], ternum[6], ternum[7]};
    int tmpnum2[4] = {ternum[8], ternum[9], ternum[10], ternum[11]};
    int tmpnum3[4] = {ternum[12], ternum[13], ternum[14], ternum[15]};
    int tmpnum4[4] = {ternum[16], ternum[17], ternum[18], ternum[19]};
    int tmpnum5[4] = {ternum[20], ternum[21], ternum[22], ternum[23]};
    int tmpnum6[4] = {ternum[24], ternum[25], ternum[26], ternum[27]};
    int tmpnum7[4] = {ternum[28], ternum[29], ternum[30], ternum[31]};
    int tmpnum8[4] = {ternum[32], ternum[33], ternum[34], ternum[35]};
    Terrace t0(terim[0], tmpnum0),
            t1(terim[1], tmpnum1),
            t2(terim[2], tmpnum2),
            t3(terim[3], tmpnum3),
            t4(terim[4], tmpnum4),
            t5(terim[5], tmpnum5),
            t6(terim[6], tmpnum6),
            t7(terim[7], tmpnum7),
            t8(terim[8], tmpnum8);

    ter0 = t0;
    ter1 = t1;
    ter2 = t2;
    ter3 = t3;
    ter4 = t4;
    ter5 = t5;
    ter6 = t6;
    ter7 = t7;
    ter8 = t8;
}
bool Map_2::walkRange(int x, int y, int w, int h)
{
    if(Background::walkRange(x, y, w, h))
    {
        if(x < flo2.getx() && flo2.getx() < (x + w) && y < flo2.gety() && flo2.gety() < (y + h))
            return false;
        if(x < (flo2.getx() + flo2.getw()) && (flo2.getx() + flo2.getw()) < (x + w) && y < flo2.gety() && flo2.gety() < (y + h))
            return false;
        if(x < flo3.getx() && flo3.getx() < (x + w) && y < flo3.gety() && flo3.gety() < (y + h))
            return false;
        if(x < (flo3.getx() + flo3.getw()) && (flo3.getx() + flo3.getw()) < (x + w) && y < flo3.gety() && flo3.gety() < (y + h))
            return false;
        return true;
    }
    return Background::walkRange(x, y, w, h);
}
bool Map_2::jumpRange(int x, int y, int w, int h)
{
    if(Background::jumpRange(x, y, w, h))
    {
        if(flo2.xrange(x) && flo2.yrange(y))
            return false;
        if(flo2.xrange(x + w) && flo2.yrange(y))
            return false;
        return true;
    }
    return Background::jumpRange(x, y, w, h);
}
bool Map_2::downRange(int x, int y, int w, int h)
{
    if(Background::downRange(x, y, w, h))
    {
        if(ter0.xrange(x) && ter0.yrange(y + h))
            return false;
        if(ter0.xrange(x + w) && ter0.yrange(y + h))
            return false;
        if(ter1.xrange(x) && ter1.yrange(y + h))
            return false;
        if(ter1.xrange(x + w) && ter1.yrange(y + h))
            return false;
        if(ter2.xrange(x) && ter2.yrange(y + h))
            return false;
        if(ter2.xrange(x + w) && ter2.yrange(y + h))
            return false;
        if(ter3.xrange(x) && ter3.yrange(y + h))
            return false;
        if(ter3.xrange(x + w) && ter3.yrange(y + h))
            return false;
        if(ter4.xrange(x) && ter4.yrange(y + h))
            return false;
        if(ter4.xrange(x + w) && ter4.yrange(y + h))
            return false;
        if(ter5.xrange(x) && ter5.yrange(y + h))
            return false;
        if(ter5.xrange(x + w) && ter5.yrange(y + h))
            return false;
        if(ter6.xrange(x) && ter6.yrange(y + h))
            return false;
        if(ter6.xrange(x + w) && ter6.yrange(y + h))
            return false;
        if(ter7.xrange(x) && ter7.yrange(y + h))
            return false;
        if(ter7.xrange(x + w) && ter7.yrange(y + h))
            return false;
        if(ter8.xrange(x) && ter8.yrange(y + h))
            return false;
        if(ter8.xrange(x + w) && ter8.yrange(y + h))
            return false;
        return true;
    }
    return Background::downRange(x, y, w, h);
}
int Map_2::walkx(int x, int y, int w, int h)
{
    if(Background::walkx(x, y, w, h) == -1)
    {
        if(x < flo2.getx() && flo2.getx() < (x + w) && y < flo2.gety() && flo2.gety() < (y + h))
            return (flo2.getx() - w);
        if(x < (flo2.getx() + flo2.getw()) && (flo2.getx() + flo2.getw()) < (x + w) && y < flo2.gety() && flo2.gety() < (y + h))
            return (flo2.getx() + flo2.getw());
        if(x < flo3.getx() && flo3.getx() < (x + w) && y < flo3.gety() && flo3.gety() < (y + h))
            return (flo3.getx() - w);
        if(x < (flo3.getx() + flo3.getw()) && (flo3.getx() + flo3.getw()) < (x + w) && y < flo3.gety() && flo3.gety() < (y + h))
            return (flo3.getx() + flo3.getw());
        return -1;
    }
    return Background::walkx(x, y, w, h);
}
int Map_2::jumpy(int x, int y, int w, int h)
{
    if(Background::jumpy(x, y, w, h) == -1)
    {
        if(flo2.xrange(x) && flo2.yrange(y))
            return (flo2.gety() + flo2.geth());
        if(flo2.xrange(x + w) && flo2.yrange(y))
            return (flo2.gety() + flo2.geth());
        return -1;
    }
    return Background::jumpy(x, y, w, h);
}
int Map_2::downy(int x, int y, int w, int h)
{
    if(Background::downy(x, y, w, h) == -1)
    {
        if(ter0.xrange(x) && ter0.yrange(y + h))
            return (ter0.gety() - h);
        if(ter0.xrange(x + w) && ter0.yrange(y + h))
            return (ter0.gety() - h);
        if(ter1.xrange(x) && ter1.yrange(y + h))
            return (ter1.gety() - h);
        if(ter1.xrange(x + w) && ter1.yrange(y + h))
            return (ter1.gety() - h);
        if(ter2.xrange(x) && ter2.yrange(y + h))
            return (ter2.gety() - h);
        if(ter2.xrange(x + w) && ter2.yrange(y + h))
            return (ter2.gety() - h);
        if(ter3.xrange(x) && ter3.yrange(y + h))
            return (ter3.gety() - h);
        if(ter3.xrange(x + w) && ter3.yrange(y + h))
            return (ter3.gety() - h);
        if(ter4.xrange(x) && ter4.yrange(y + h))
            return (ter4.gety() - h);
        if(ter4.xrange(x + w) && ter4.yrange(y + h))
            return (ter4.gety() - h);
        if(ter5.xrange(x) && ter5.yrange(y + h))
            return (ter5.gety() - h);
        if(ter5.xrange(x + w) && ter5.yrange(y + h))
            return (ter5.gety() - h);
        if(ter6.xrange(x) && ter6.yrange(y + h))
            return (ter6.gety() - h);
        if(ter6.xrange(x + w) && ter6.yrange(y + h))
            return (ter6.gety() - h);
        if(ter7.xrange(x) && ter7.yrange(y + h))
            return (ter7.gety() - h);
        if(ter7.xrange(x + w) && ter7.yrange(y + h))
            return (ter7.gety() - h);
        if(ter8.xrange(x) && ter8.yrange(y + h))
            return (ter8.gety() - h);
        if(ter8.xrange(x + w) && ter8.yrange(y + h))
            return (ter8.gety() - h);
        return -1;
    }
    return Background::downy(x, y, w, h);
}
void Map_2::show(void)
{
    Background::show();
    int i;

    for(i = 0; i < (8 * 3); ++i)
        apply_surface(500 + MATERIAL_LONG * (i % 8), MATERIAL_LONG * (i / 8), material[1], screen, &background_clips);
    flo2.show();
    flo3.show();
    ter0.show();
    ter1.show();
    ter2.show();
    ter3.show();
    ter4.show();
    ter5.show();
    ter6.show();
    ter7.show();
    ter8.show();
    apply_surface(600 - 25, 225, ornament_image[3], screen, NULL);
    apply_surface(150 - 10, 700 - 250 - 110, ornament_image[0], screen, NULL);
    apply_surface(1200 - 150 - 10, 700 - 250 - 110, ornament_image[0], screen, NULL);
}
Map_3::Map_3()
    :Map_type1()
{

}
Map_3::Map_3(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[])
    :Map_type1(bim, fim, fnum, dim, dnum)
{
    int bxnum[2] = {1200 - 350, 700 - 100};
    Box b0(bxnum);

    bo0 = b0;
}
bool Map_3::openthebox(int x, int y, int w, int h)
{
    if(bo0.openbox(x, y, w, h))
        return true;
    return false;
}
void Map_3::show(void)
{
    Map_type1::show();
    bo0.show();
    apply_surface(250 - 25, 100, ornament_image[3], screen, NULL);
    apply_surface(1200 - 275, 100, ornament_image[3], screen, NULL);
    apply_surface(400 - 50, 350, ornament_image[2], screen, NULL);
    apply_surface(1200 - 400, 350, ornament_image[2], screen, NULL);
}
Map_type2::Map_type2()
    :Background()
{

}
Map_type2::Map_type2(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[])
{
    int flonum0[5] = {0, 0, SCREEN_WIDTH, fnum[0], fnum[1]}, flonum1[5] = {0, SCREEN_HEIGHT - fnum[2] - fnum[3], SCREEN_WIDTH, fnum[2], fnum[3]};
    SDL_Surface *floim0[2] = {fim[0], fim[1]}, *floim1[2] = {fim[2], fim[3]};
    Floor f0(floim0, flonum0), f1(floim1, flonum1);
    int dornum0[5] = {dnum[0], dnum[1], dnum[2], dnum[3], dnum[4]};
    Door d0(dim[0], dornum0);

    flo0 = f0;
    flo1 = f1;
    door[0] = d0;
    doornum = 1;
    height_num = (SCREEN_HEIGHT - flo0.geth() - flo1.geth()) / MATERIAL_LONG;
    if(dim[1] != NULL)
    {
        int dornum1[5] = {dnum[5], dnum[6], dnum[7], dnum[8], dnum[9]};
        Door d1(dim[1], dornum1);

        door[1] = d1;
        ++doornum;
    }
    if(dim[2] != NULL)
    {
        int dornum2[5] = {dnum[10], dnum[11], dnum[12], dnum[13], dnum[14]};
        Door d2(dim[2], dornum2);

        door[2] = d2;
        ++doornum;
    }
    bimage0 = bim;
}
Map_4::Map_4()
    :Map_type2()
{
    bimage1 = NULL;
    bimage2 = NULL;
}
Map_4::Map_4(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[])
    :Map_type2(bim, fim, fnum, dim, dnum)
{
    int hsysnum0[3] = {500, 700 - 64, 3};
    Healsystem h0(hsysnum0);

    hsys0 = h0;
    bimage1 = material[0];
    bimage2 = material[4];
}
bool Map_4::usehealsystem(int x, int y, int w, int h)
{
    if((hsys0.xrange(x) && hsys0.yrange(y + h)) || (hsys0.xrange(x + w) && hsys0.yrange(y + h)))
        return hsys0.use();
    return false;
}
void Map_4::show(void)
{
    int i;

    for(i = 0; i < (MATERIAL_WIDTH_NUMBER * height_num); ++i)
        apply_surface(MATERIAL_LONG * (i % MATERIAL_WIDTH_NUMBER), flo0.geth() + MATERIAL_LONG * (i / MATERIAL_WIDTH_NUMBER), bimage0, screen, &background_clips);
    for(i = 0; i < (4 * 24); ++i)
        apply_surface(MATERIAL_LONG * (i % 4), 100 + MATERIAL_LONG * (i / 4), bimage2, screen, &background_clips);
    for(i = 0; i < (4 * 24); ++i)
        apply_surface(1100 + MATERIAL_LONG * (i % 4), 100 + MATERIAL_LONG * (i / 4), bimage2, screen, &background_clips);
    for(i = 0; i < (MATERIAL_WIDTH_NUMBER * 8); ++i)
        apply_surface(MATERIAL_LONG * (i % MATERIAL_WIDTH_NUMBER), 300 + MATERIAL_LONG * (i / MATERIAL_WIDTH_NUMBER), bimage1, screen, &background_clips);
    flo0.show();
    flo1.show();
    door[0].show();
    if(doornum >= 2)
        door[1].show();
    if(doornum >= 3)
        door[2].show();
    hsys0.show();
}
Map_5::Map_5()
    :Map_type2()
{

}
Map_5::Map_5(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[])
    :Map_type2(bim, fim, fnum, dim, dnum)
{
    SDL_Surface *floim2[2] = {material[4], NULL},
                             *floim3[2] = {material[4], NULL};
    int flonum2[5] = {0, 700 - 100, 150, 100, 0},
                     flonum3[5] = {1200 - 150, 700 - 100, 150, 100, 0};
    int ternum0[4] = {300, 700 - 200, 100, 25},
                     ternum1[4] = {1200 - 300 - 100, 700 - 200, 100, 25};
    Floor f2(floim2, flonum2),
          f3(floim3, flonum3);
    Terrace t0(material[4], ternum0),
            t1(material[4], ternum1);

    flo2 = f2;
    flo3 = f3;
    ter0 = t0;
    ter1 = t1;
    int kenum0[3] = {350 - 15, 700 - 200 - 10, 1},
                    kenum1[3] = {1200 - 350 - 15, 700 - 200 - 10, 2};
    Key k0(key_image[1], kenum0),
        k1(key_image[2], kenum1);

    ke0 = k0;
    ke1 = k1;
}
bool Map_5::walkRange(int x, int y, int w, int h)
{
    if(Background::walkRange(x, y, w, h))
    {
        if(x < flo2.getx() && flo2.getx() < (x + w) && y < flo2.gety() && flo2.gety() < (y + h))
            return false;
        if(x < (flo2.getx() + flo2.getw()) && (flo2.getx() + flo2.getw()) < (x + w) && y < flo2.gety() && flo2.gety() < (y + h))
            return false;
        if(x < flo3.getx() && flo3.getx() < (x + w) && y < flo3.gety() && flo3.gety() < (y + h))
            return false;
        if(x < (flo3.getx() + flo3.getw()) && (flo3.getx() + flo3.getw()) < (x + w) && y < flo3.gety() && flo3.gety() < (y + h))
            return false;
        return true;
    }
    return Background::walkRange(x, y, w, h);
}
bool Map_5::downRange(int x, int y, int w, int h)
{
    if(Background::downRange(x, y, w, h))
    {
        if(flo2.xrange(x) && flo2.yrange(y + h))
            return false;
        if(flo2.xrange(x + w) && flo2.yrange(y + h))
            return false;
        if(flo3.xrange(x) && flo3.yrange(y + h))
            return false;
        if(flo3.xrange(x + w) && flo3.yrange(y + h))
            return false;
        if(ter0.xrange(x) && ter0.yrange(y + h))
            return false;
        if(ter0.xrange(x + w) && ter0.yrange(y + h))
            return false;
        if(ter1.xrange(x) && ter1.yrange(y + h))
            return false;
        if(ter1.xrange(x + w) && ter1.yrange(y + h))
            return false;
        return true;
    }
    return Background::downRange(x, y, w, h);
}
int Map_5::walkx(int x, int y, int w, int h)
{
    if(Background::walkx(x, y, w, h) == -1)
    {
        if(x < flo2.getx() && flo2.getx() < (x + w) && y < flo2.gety() && flo2.gety() < (y + h))
            return (flo2.getx() - w);
        if(x < (flo2.getx() + flo2.getw()) && (flo2.getx() + flo2.getw()) < (x + w) && y < flo2.gety() && flo2.gety() < (y + h))
            return (flo2.getx() + flo2.getw());
        if(x < flo3.getx() && flo3.getx() < (x + w) && y < flo3.gety() && flo3.gety() < (y + h))
            return (flo3.getx() - w);
        if(x < (flo3.getx() + flo3.getw()) && (flo3.getx() + flo3.getw()) < (x + w) && y < flo3.gety() && flo3.gety() < (y + h))
            return (flo3.getx() + flo3.getw());
        return -1;
    }
    return Background::walkx(x, y, w, h);
}
int Map_5::downy(int x, int y, int w, int h)
{
    if(Background::downy(x, y, w, h) == -1)
    {
        if(flo2.xrange(x) && flo2.yrange(y + h))
            return (flo2.gety() - h);
        if(flo2.xrange(x + w) && flo2.yrange(y + h))
            return (flo2.gety() - h);
        if(flo3.xrange(x) && flo3.yrange(y + h))
            return (flo3.gety() - h);
        if(flo3.xrange(x + w) && flo3.yrange(y + h))
            return (flo3.gety() - h);
        if(ter0.xrange(x) && ter0.yrange(y + h))
            return (ter0.gety() - h);
        if(ter0.xrange(x + w) && ter0.yrange(y + h))
            return (ter0.gety() - h);
        if(ter1.xrange(x) && ter1.yrange(y + h))
            return (ter1.gety() - h);
        if(ter1.xrange(x + w) && ter1.yrange(y + h))
            return (ter1.gety() - h);
        return -1;
    }
    return Background::downy(x, y, w, h);
}
bool Map_5::thekey(int x, int y, int w, int h)
{
    if(ke0.keyrange(x, y, w, h))
        return true;
    if(ke1.keyrange(x, y, w, h))
        return true;
    return false;
}
int Map_5::getthekey(int x, int y, int w, int h)
{
    if(ke0.getkey(x, y, w, h))
        return ke0.getkeynum();
    if(ke1.getkey(x, y, w, h))
        return ke1.getkeynum();
    return -1;
}
void Map_5::show(void)
{
    Background::show();
    mato1.move();
    flo2.show();
    flo3.show();
    ter0.show();
    ter1.show();
    ke0.show();
    ke1.show();
    apply_surface(200, 700 - 150, ornament_image[1], screen, NULL);
    apply_surface(1200 - 200 - 100, 700 - 150, ornament_image[1], screen, NULL);
    mato1.show();
}
Map_6::Map_6()
    :Map_type2()
{

}
Map_6::Map_6(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[])
    :Map_type2(bim, fim, fnum, dim, dnum)
{
    int ternum0[4] = {300 + 25 + 100, 200, 400, 25},
                     ternum1[4] = {300, 200 + 110, 100, 25},
                                  ternum2[4] = {400, 200 + 110 + 130, 100, 25},
                                          ternum3[4] = {400 - 100, 200 + 110 + 130 + 25, 100, 25},
                                                  ternum4[4] = {200, 700 - 100 - 25, 100, 25};
    Terrace t0(material[6], ternum0),
            t1(material[6], ternum1),
            t2(material[6], ternum2),
            t3(material[6], ternum3),
            t4(material[6], ternum4);

    ter0 = t0;
    ter1 = t1;
    ter2 = t2;
    ter3 = t3;
    ter4 = t4;
    int knum[3] = {400 + 200 - 15, 200 - 10, 6};
    Key k0(key_image[6], knum);

    ke0 = k0;
}
bool Map_6::downRange(int x, int y, int w, int h)
{
    if(Background::downRange(x, y, w, h))
    {
        if(ter0.xrange(x) && ter0.yrange(y + h))
            return false;
        if(ter0.xrange(x + w) && ter0.yrange(y + h))
            return false;
        if(ter1.xrange(x) && ter1.yrange(y + h))
            return false;
        if(ter1.xrange(x + w) && ter1.yrange(y + h))
            return false;
        if(ter2.xrange(x) && ter2.yrange(y + h))
            return false;
        if(ter2.xrange(x + w) && ter2.yrange(y + h))
            return false;
        if(ter3.xrange(x) && ter3.yrange(y + h))
            return false;
        if(ter3.xrange(x + w) && ter3.yrange(y + h))
            return false;
        if(ter4.xrange(x) && ter4.yrange(y + h))
            return false;
        if(ter4.xrange(x + w) && ter4.yrange(y + h))
            return false;
        return true;
    }
    return Background::downRange(x, y, w, h);
}
int Map_6::downy(int x, int y, int w, int h)
{
    if(Background::downy(x, y, w, h) == -1)
    {
        if(ter0.xrange(x) && ter0.yrange(y + h))
            return (ter0.gety() - h);
        if(ter0.xrange(x + w) && ter0.yrange(y + h))
            return (ter0.gety() - h);
        if(ter1.xrange(x) && ter1.yrange(y + h))
            return (ter1.gety() - h);
        if(ter1.xrange(x + w) && ter1.yrange(y + h))
            return (ter1.gety() - h);
        if(ter2.xrange(x) && ter2.yrange(y + h))
            return (ter2.gety() - h);
        if(ter2.xrange(x + w) && ter2.yrange(y + h))
            return (ter2.gety() - h);
        if(ter3.xrange(x) && ter3.yrange(y + h))
            return (ter3.gety() - h);
        if(ter3.xrange(x + w) && ter3.yrange(y + h))
            return (ter3.gety() - h);
        if(ter4.xrange(x) && ter4.yrange(y + h))
            return (ter4.gety() - h);
        if(ter4.xrange(x + w) && ter4.yrange(y + h))
            return (ter4.gety() - h);
        return -1;
    }
    return Background::downy(x, y, w, h);
}
bool Map_6::thekey(int x, int y, int w, int h)
{
    if(ke0.keyrange(x, y, w, h))
        return true;
    return false;
}
int Map_6::getthekey(int x, int y, int w, int h)
{
    if(ke0.getkey(x, y, w, h))
        return ke0.getkeynum();
    return -1;
}
void Map_6::show(void)
{
    Background::show();
    ter0.show();
    ter1.show();
    ter2.show();
    ter3.show();
    ter4.show();
    ke0.show();
    apply_surface(0, 90, ornament_image[0], screen, NULL);
    apply_surface(1200 - 20, 90, ornament_image[0], screen, NULL);
}
Map_7::Map_7()
    :Map_type1()
{
    bimage1 = NULL;
}
Map_7::Map_7(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[])
    :Map_type1(bim, fim, fnum, dim, dnum)
{
    int bnum0[2] = {300, 600};
    Box b0(bnum0);

    bo0 = b0;
    int hnum0[3] = {1200 - 250 - 200, 700 - 64, 1};
    Healsystem h0(hnum0);

    hsys0 = h0;
    bimage1 = material[0];
}
bool Map_7::openthebox(int x, int y, int w, int h)
{
    if(bo0.openbox(x, y, w, h))
        return true;
    return false;
}
bool Map_7::usehealsystem(int x, int y, int w, int h)
{
    if((hsys0.xrange(x) && hsys0.yrange(y + h)) || (hsys0.xrange(x + w) && hsys0.yrange(y + h)))
        return hsys0.use();
    return false;
}
void Map_7::show(void)
{
    int i;
    for(i = 0; i < (MATERIAL_WIDTH_NUMBER * height_num); ++i)
        apply_surface(MATERIAL_LONG * (i % MATERIAL_WIDTH_NUMBER), flo0.geth() + MATERIAL_LONG * (i / MATERIAL_WIDTH_NUMBER), bimage0, screen, &background_clips);
    for(i = 0; i < (MATERIAL_WIDTH_NUMBER * 8); ++i)
        apply_surface(MATERIAL_LONG * (i % MATERIAL_WIDTH_NUMBER), 300 + MATERIAL_LONG * (i / MATERIAL_WIDTH_NUMBER), bimage1, screen, &background_clips);
    flo0.show();
    flo1.show();
    door[0].show();
    if(doornum >= 2)
        door[1].show();
    if(doornum >= 3)
        door[2].show();
    bo0.show();
    hsys0.show();
    apply_surface(0, 200 - 55, ornament_image[0], screen, NULL);
    apply_surface(1200 - 200, 200, ornament_image[2], screen, NULL);
    apply_surface(520 - 50, 700 - 150, ornament_image[1], screen, NULL);
    apply_surface(570 + 30, 700 - 150, ornament_image[1], screen, NULL);
}
Map_8::Map_8()
    :Map_type2()
{

}
Map_8::Map_8(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[])
    :Map_type2(bim, fim, fnum, dim, dnum)
{
    SDL_Surface *terim0 = material[6],
                 *terim1 = material[6],
                  *terim2 = material[6],
                   *terim3 = material[6],
                    *terim4 = material[6];
    int ternum0[4] = {0, 400, 225, 25},
                     ternum1[4] = {225 + 300 / 2, 400, 450, 25},
                                  ternum2[4] = {1200 - 225, 400, 225, 25},
                                          ternum3[4] = {225, 700 - 140, 225, 25},
                                                  ternum4[4] = {1200 - 225 - 225, 700 - 140, 225, 25};
    Terrace t0(terim0, ternum0),
            t1(terim1, ternum1),
            t2(terim2, ternum2),
            t3(terim3, ternum3),
            t4(terim4, ternum4);

    ter0 = t0;
    ter1 = t1;
    ter2 = t2;
    ter3 = t3;
    ter4 = t4;
    int bnum0[2] = {0, 400 - 100},
                   bnum1[2] = {125, 400 - 100},
                              bnum2[2] = {225 + 300 / 2 + 25, 400 - 100},
                                         bnum3[2] = {225 + 300 / 2 + 25 + 150, 400 - 100},
                                                 bnum4[2] = {225 + 300 / 2 + 25 + 300, 400 - 100},
                                                         bnum5[2] = {1200 - 225, 400 - 100},
                                                                 bnum6[2] = {1200 - 225 + 125, 400 - 100},
                                                                         bnum7[2] = {225, 700 - 140 - 100},
                                                                                 bnum8[2] = {225 + 125, 700 - 140 - 100},
                                                                                         bnum9[2] = {1200 - 225 - 225, 700 - 140 - 100},
                                                                                                 bnum10[2] = {1200 - 225 - 225 + 125, 700 - 140 - 100},
                                                                                                         bnum11[2] = {100, 700 - 100},
                                                                                                                 bnum12[2] = {100 + 125, 700 - 100},
                                                                                                                         bnum13[2] = {100 + 250, 700 - 100},
                                                                                                                                 bnum14[2] = {1200 - 450, 700 - 100},
                                                                                                                                         bnum15[2] = {1200 - 450 + 125, 700 - 100},
                                                                                                                                                 bnum16[2] = {1200 - 450 + 250, 700 - 100};
    Box b0(bnum0),
        b1(bnum1),
        b2(bnum2),
        b3(bnum3),
        b4(bnum4),
        b5(bnum5),
        b6(bnum6),
        b7(bnum7),
        b8(bnum8),
        b9(bnum9),
        b10(bnum10),
        b11(bnum11),
        b12(bnum12),
        b13(bnum13),
        b14(bnum14),
        b15(bnum15),
        b16(bnum16);

    bo[0] = b0;
    bo[1] = b1;
    bo[2] = b2;
    bo[3] = b3;
    bo[4] = b4;
    bo[5] = b5;
    bo[6] = b6;
    bo[7] = b7;
    bo[8] = b8;
    bo[9] = b9;
    bo[10] = b10;
    bo[11] = b11;
    bo[12] = b12;
    bo[13] = b13;
    bo[14] = b14;
    bo[15] = b15;
    bo[16] = b16;
}
bool Map_8::downRange(int x, int y, int w, int h)
{
    if(Background::downRange(x, y, w, h))
    {
        if(ter0.xrange(x) && ter0.yrange(y + h))
            return false;
        if(ter0.xrange(x + w) && ter0.yrange(y + h))
            return false;
        if(ter1.xrange(x) && ter1.yrange(y + h))
            return false;
        if(ter1.xrange(x + w) && ter1.yrange(y + h))
            return false;
        if(ter2.xrange(x) && ter2.yrange(y + h))
            return false;
        if(ter2.xrange(x + w) && ter2.yrange(y + h))
            return false;
        if(ter3.xrange(x) && ter3.yrange(y + h))
            return false;
        if(ter3.xrange(x + w) && ter3.yrange(y + h))
            return false;
        if(ter4.xrange(x) && ter4.yrange(y + h))
            return false;
        if(ter4.xrange(x + w) && ter4.yrange(y + h))
            return false;
        return true;
    }
    return Background::downRange(x, y, w, h);
}
int Map_8::downy(int x, int y, int w, int h)
{
    if(Background::downy(x, y, w, h) == -1)
    {
        if(ter0.xrange(x) && ter0.yrange(y + h))
            return (ter0.gety() - h);
        if(ter0.xrange(x + w) && ter0.yrange(y + h))
            return (ter0.gety() - h);
        if(ter1.xrange(x) && ter1.yrange(y + h))
            return (ter1.gety() - h);
        if(ter1.xrange(x + w) && ter1.yrange(y + h))
            return (ter1.gety() - h);
        if(ter2.xrange(x) && ter2.yrange(y + h))
            return (ter2.gety() - h);
        if(ter2.xrange(x + w) && ter2.yrange(y + h))
            return (ter2.gety() - h);
        if(ter3.xrange(x) && ter3.yrange(y + h))
            return (ter3.gety() - h);
        if(ter3.xrange(x + w) && ter3.yrange(y + h))
            return (ter3.gety() - h);
        if(ter4.xrange(x) && ter4.yrange(y + h))
            return (ter4.gety() - h);
        if(ter4.xrange(x + w) && ter4.yrange(y + h))
            return (ter4.gety() - h);
        return -1;
    }
    return Background::downy(x, y, w, h);
}
bool Map_8::openthebox(int x, int y, int w, int h)
{
    int i;

    for(i = 0; i < 17 && bo[i].openbox(x, y, w, h) == false; ++i);
    if(i==17)
        return false;
    else
        return true;
}
void Map_8::show(void)
{
    Map_type2::show();
    ter0.show();
    ter1.show();
    ter2.show();
    ter3.show();
    ter4.show();
    bo[0].show();
    bo[1].show();
    bo[2].show();
    bo[3].show();
    bo[4].show();
    bo[5].show();
    bo[6].show();
    bo[7].show();
    bo[8].show();
    bo[9].show();
    bo[10].show();
    bo[11].show();
    bo[12].show();
    bo[13].show();
    bo[14].show();
    bo[15].show();
    bo[16].show();
}
