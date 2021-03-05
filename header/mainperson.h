/*
 * mainperson.h
 *
 *  Created on: 2017�~5��12��
 *      Author: PC2017
 */
#include <SDL.h>
#include "..\header\useplace.h"
#include "..\header\shootbullet.h"
#include "..\header\map.h"
#ifndef SRC_MAINPERSON_H_
#define SRC_MAINPERSON_H_
class Superugly
{
    private:
    //Its rate of movement
    int velocity;

    //Its current frame
    int frame;

    //atk frame
    int cnt;

    //k-atk frame
    int cnt2;

    //Its animation status
    int status;

    //jump;
    int status2;

    //�W�@�t��
    int v;

    //����
    int height;

    //delay atkspeed
    int jps;

    //gravity
    int a;

    //some atk picture x fixed
    static const int handx[5];

    static const int rehandx[5];

    static const int khandx[7];

    static const int krehandx[7];

    int HP;

    int MP;

    int HPflag;//1 �i����

    int timecnt;//�p�ƾ�

    public:
    //Initializes the variables
    useplace prop;

    bullet abullet;
    Superugly(Background *m[]);

    bool load_SB_files();

    void cleanSB();

    void set_clips();
    //Handles input
    void handle_events();

    void handleHP(SDL_Rect);
    void handleHP(SDL_Rect,int ,int);

    void Hptime();//limit time
    //Moves the stick figure
    void move();//move x
    //Shows the stick figure
    void show();

    void showHP();

    void showMP();

    void dofixx();

    void undofixx();
    //detect be attacked by something
    bool beattack(SDL_Rect);
    //�H����m
    SDL_Rect place;

    //atk;
    int status3;
    int reset;
    Background *mymap[9];
    int past, now;
};
#endif /* SRC_MAINPERSON_H_ */
