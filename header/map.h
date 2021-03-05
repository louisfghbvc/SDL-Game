/*
 * map.h
 *
 *  Created on: 2017¦~5¤ë29¤é
 *      Author: jason
 */
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#ifndef MAP_H_
#define MAP_H_

#define MATERIAL_LONG 25
#define MATERIAL_WIDTH_NUMBER 48
#define MATERIAL_HEIGHT_NUMBER 32

void set_background_clips(void);
bool load_background_files(void);
void clean_background(void);

class Floor
{
private:
    int fnum[5], width_num;
    SDL_Surface *image[2];
public:
    Floor(void);
    Floor(SDL_Surface *im[], int num[]);
    int getx(void) const;
    int gety(void) const;
    int getw(void) const;
    int geth(void) const;
    bool xrange(int x);
    bool yrange(int y);
    void show(void);
};
class Terrace
{
private:
    int tnum[4], width_num;
    SDL_Surface *image;
public:
    Terrace(void);
    Terrace(SDL_Surface *im, int num[]);
    int getx(void) const;
        int gety(void) const;
        int getw(void) const;
        int geth(void) const;
        bool xrange(int x);
            bool yrange(int y);
    void show(void);
};
class Healsystem
{
private:
    int hnum[3];
public:
    Healsystem();
    Healsystem(int num[]);
    bool xrange(int x);
    bool yrange(int y);
    bool use(void);
    void show(void);
};
class Box
{
private:
    int bxnum[2];
    bool open;
public:
    Box();
    Box(int num[]);
    bool openbox(int x, int y, int w, int h);
    void show(void);
};
class Key
{
private:
    int knum[3];
    SDL_Surface *image;
    bool appear;
public:
    Key();
    Key(SDL_Surface *im, int num[]);
    int getkeynum(void);
    bool keyrange(int x, int y, int w, int h);
    bool getkey(int x, int y, int w, int h);
    void show(void);
};
class Door
{
private:
    int dnum[5], mapnum, keylife;
    SDL_Surface *image;
    SDL_Rect door_clips[3];
public:
    Door(void);
    Door(SDL_Surface *im, int num[]);
    int getdoornum(void);
    int getmapnum(void);
    int getx(void);
    int gety(void);
    void set_clips(int t);
    bool xrange(int x);
    bool yrange(int y);
    bool isNotLocked(void);
    int open(void);
    void show(void);
};
class Background
{
protected:
    Floor flo0, flo1;
    Door door[3];
    int doornum, height_num;
    SDL_Surface *bimage0;
public:
    Background(void);
    virtual ~Background(void);
    Background(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[]);
    virtual bool walkRange(int x, int y, int w, int h);
    virtual bool jumpRange(int x, int y, int w, int h);
    virtual bool downRange(int x, int y, int w, int h);
    virtual int walkx(int x, int y, int w, int h);
    virtual int jumpy(int x, int y, int w, int h);
    virtual int downy(int x, int y, int w, int h);
    int enterdoornum(int past);
    int enterx(int n);
    int entery(int n);
    int theDoor(int x, int y, int w, int h);
    bool theDoorisNotLocked(int n);
    int matchtheDoor(int n);
    int opentheDoor(int n);
    virtual bool thekey(int x, int y, int w, int h);
    virtual int getthekey(int x, int y, int w, int h);
    virtual bool openthebox(int x, int y, int w, int h);
    virtual bool usehealsystem(int x, int y, int w, int h);
    virtual void show(void);
};
class Map_type1 : public Background
{
public:
    Map_type1();
    Map_type1(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[]);
};
class Map_0 : public Map_type1
{
protected:
    Floor flo2;
public:
    Map_0();
    Map_0(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[]);
    virtual bool walkRange(int x, int y, int w, int h);
        virtual bool downRange(int x, int y, int w, int h);
        virtual int walkx(int x, int y, int w, int h);
        virtual int downy(int x, int y, int w, int h);
    virtual void show(void);
};
class Map_1 : public Map_type1
{
protected:
    Floor flo2;
    Box bo0;
    Key ke0;
    SDL_Surface *bimage1;
public:
    Map_1();
    Map_1(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[]);
    virtual bool walkRange(int x, int y, int w, int h);
            virtual bool downRange(int x, int y, int w, int h);
            virtual int walkx(int x, int y, int w, int h);
            virtual int downy(int x, int y, int w, int h);
            virtual bool thekey(int x, int y, int w, int h);
    virtual int getthekey(int x, int y, int w, int h);
    virtual bool openthebox(int x, int y, int w, int h);
    virtual void show(void);
};
class Map_2 : public Background
{
protected:
    Floor flo2, flo3;
    Terrace ter0, ter1, ter2, ter3, ter4, ter5, ter6, ter7, ter8;
public:
    Map_2();
    virtual bool walkRange(int x, int y, int w, int h);
    virtual bool jumpRange(int x, int y, int w, int h);
        virtual bool downRange(int x, int y, int w, int h);
        virtual int walkx(int x, int y, int w, int h);
        virtual int jumpy(int x, int y, int w, int h);
        virtual int downy(int x, int y, int w, int h);
    virtual void show(void);
};
class Map_3 : public Map_type1
{
protected:
    Box bo0;
public:
    Map_3();
    Map_3(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[]);
    virtual bool openthebox(int x, int y, int w, int h);
    virtual void show(void);
};
class Map_type2 : public Background
{
public:
    Map_type2();
    Map_type2(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[]);
};
class Map_4 : public Map_type2
{
protected:
    Healsystem hsys0;
    SDL_Surface *bimage1, *bimage2;
public:
    Map_4();
    Map_4(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[]);
    virtual bool usehealsystem(int x, int y, int w, int h);
    virtual void show(void);
};
class Map_5 : public Map_type2
{
protected:
    Floor flo2, flo3;
    Terrace ter0, ter1;
    Key ke0, ke1;
public:
    Map_5();
    Map_5(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[]);
    virtual bool walkRange(int x, int y, int w, int h);
            virtual bool downRange(int x, int y, int w, int h);
            virtual int walkx(int x, int y, int w, int h);
            virtual int downy(int x, int y, int w, int h);
            virtual bool thekey(int x, int y, int w, int h);
    virtual int getthekey(int x, int y, int w, int h);
    virtual void show(void);
};
class Map_6 : public Map_type2
{
protected:
    Terrace ter0, ter1, ter2, ter3, ter4;
    Key ke0;
public:
    Map_6();
    Map_6(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[]);
                virtual bool downRange(int x, int y, int w, int h);
                virtual int downy(int x, int y, int w, int h);
                virtual bool thekey(int x, int y, int w, int h);
    virtual int getthekey(int x, int y, int w, int h);
    virtual void show(void);
};
class Map_7 : public Map_type1
{
protected:
    Box bo0;
    Healsystem hsys0;
    SDL_Surface *bimage1;
public:
    Map_7();
    Map_7(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[]);
    virtual bool openthebox(int x, int y, int w, int h);
    virtual bool usehealsystem(int x, int y, int w, int h);
    virtual void show(void);
};
class Map_8 : public Map_type2
{
protected:
    Terrace ter0, ter1, ter2, ter3, ter4;
    Box bo[17];
public:
    Map_8();
    Map_8(SDL_Surface *bim, SDL_Surface *fim[], int fnum[], SDL_Surface *dim[], int dnum[]);
    virtual bool downRange(int x, int y, int w, int h);
                    virtual int downy(int x, int y, int w, int h);
                    virtual bool openthebox(int x, int y, int w, int h);
    virtual void show(void);
};
#endif /* MAP_H_ */
