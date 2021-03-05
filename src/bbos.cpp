#include "..\header\bbos.h"
#include "..\header\SDL_rotozoom.h"
#include "..\header\SDLtool.h"
#include <cmath>
#include "..\header\monster.h"
using namespace std;

#define TV_h 323
#define TV_w 500
#define PI 3.14159265359
#include <SDL.h>
#include <SDL_image.h>
#include <string>

 int pp;
 SDL_Surface *BOSS[5];
 Mix_Music *bmus;


NI::NI(int x,int y)
{   pp=0;
	paralleloffSet=x;
	verticaloffSet=y;
	state=0;
	parallelvelocity=0;
	verticalvelocity=0;
	hp=50;
	damage=2;
	load_pic(".\\BOSS\\NIOK\\NI.png");
	load_pic(".\\BOSS\\NIOK\\NIA.png");
	load_pic(".\\BOSS\\NIOK\\floatingsword.png");
	load_pic(".\\BOSS\\NIOK\\NIS.png");
	set_clips();
	frame=0;
	loadmus(".\\mus\\Boss\\16.ogg");
	fangx[0]=paralleloffSet+50;
	fangy[0]=verticaloffSet-75;
	fangx[1]=paralleloffSet+100;
	fangy[1]=verticaloffSet-25;
	fangx[2]=paralleloffSet-50;
	fangy[2]=verticaloffSet-50;
	fangx[3]=paralleloffSet-100;
	fangy[3]= verticaloffSet-50;
	int i;
	for(i=0;i<4;i++){oldazimuth[i]=0;}
	ifst=false;
	frame=0;
}

bool NI::isdead()
{
	if(hp<=0){pp=0; BOSS[0]=NULL; BOSS[1]=NULL; BOSS[2]=NULL; BOSS[3]=NULL;  paralleloffSet=0; verticaloffSet=0; return true;}
	return false;
}

void NI::acting(Superugly &mr,Background *map){

	if(!Mix_PlayingMusic()){Mix_PlayMusic( bmus, -1 );}
	if(ifst){
		if(!isdead()){int i;
			for(i=0;i<4;i++){mr.handleHP(clipfang[0],fangx[i],fangy[i]);}
			fang(mr.place);
			move(map);
			mr.handleHP(clipbody[0],paralleloffSet,verticaloffSet);
			if(state>10){
				mr.handleHP(clipA[0][0],paralleloffSet+(frame==1?0:-164),verticaloffSet-69);
				attack(mr.place,map);}  }}
	else{
		static int i=0;

		apply_surface( paralleloffSet-79, verticaloffSet-84, BOSS[3], screen, &clipst[ i/2 ] );  if(i==5){ifst=true;}   i++;
}
}

void NI::move(Background *map)
{   static int i=0,p1,p2;
if(i==0){p1=(rand()%10)*pow(-1,rand());}
if(i==10){i=-1;}
i++;
	if(state<=10){

	if(p1>0){frame=0;}else{frame=1;}
	paralleloffSet+=p1;

	p2=(rand()%15)*pow(-1,rand());
	verticaloffSet+=p2;
	if(!map->walkRange(paralleloffSet,verticaloffSet,clipbody[0].w,clipbody[0].h)){paralleloffSet-=p1;  verticaloffSet-=p2;}
	apply_surface( paralleloffSet, verticaloffSet, BOSS[0], screen, &clipbody[ frame ] );/////
	}
	state++;
}

bool NI::attack(SDL_Rect place,Background *map){  /////
    static int fr=0;
    if(fr==0&&paralleloffSet<=place.x){parallelvelocity=50; frame=1;}
    else if(fr==0&&verticaloffSet>=place.x){parallelvelocity=50*(-1); frame=0;}
	if(fr>=5){if(fr==11){fr=0; state=0; parallelvelocity=0;  return false;}
	paralleloffSet+=parallelvelocity;
	if(!map->walkRange(paralleloffSet,verticaloffSet,clipbody[0].w,clipbody[0].h)){paralleloffSet-=parallelvelocity;}
	apply_surface( paralleloffSet+(frame==1?0:-164), verticaloffSet-69, BOSS[1], screen, &clipA[ 4 ][frame] );
	}
	else{apply_surface( paralleloffSet+(frame==1?0:-164), verticaloffSet-69, BOSS[1], screen, &clipA[ fr ][frame] );}  /////
    fr++;
    return true;
}
void NI::fang(SDL_Rect mr){
	int i;  static int foa=0,ox[4],oy[4];
	if(foa<70){
		for(i=0;i<4;i++){
		clipfang[ i ].w=1+10*clipfang[ i ].w*abs((cos(getazimuth(mr.x,mr.y,fangx[i], fangy[i]))/cos(oldazimuth[i])));
		clipfang[ i ].h=1+10*clipfang[ i ].h*abs((sin(getazimuth(mr.x,mr.y,fangx[i], fangy[i]))/sin(oldazimuth[i])));
		oldazimuth[i]= getazimuth(mr.x,mr.y,fangx[i], fangy[i])+90; foa++; }/////
		for(i=0;i<4;i++){ox[i]=mr.x; oy[i]=mr.y;}
		for(i=0;i<4;i++){apply_surface( fangx[i], fangy[i], rotozoomSurface(BOSS[2],getazimuth(mr.x,mr.y,fangx[i], fangy[i])+90,1.0,0), screen, &clipfang[ 0 ] );}
	}
	else{//////////
		if(foa<100){fangx[0]+=(ox[0]-fangx[0])/5;
		fangy[0]+=(oy[0]-fangy[0])/5;
		for(i=1;i<4;i++){
				clipfang[ i ].w=1+10*clipfang[ i ].w*abs((cos(getazimuth(mr.x,mr.y,fangx[i], fangy[i]))/cos(oldazimuth[i])));
				clipfang[ i ].h=1+10*clipfang[ i ].h*abs((sin(getazimuth(mr.x,mr.y,fangx[i], fangy[i]))/sin(oldazimuth[i])));
				oldazimuth[i]= getazimuth(mr.x,mr.y,fangx[i], fangy[i])+90; foa++; }/////
		for(i=1;i<4;i++){ox[i]=mr.x; oy[i]=mr.y;}
		}
		else if(foa<130){fangx[1]+=(ox[1]-fangx[1])/5;
		fangy[1]+=(oy[1]-fangy[1])/5;
		for(i=2;i<4;i++){
				clipfang[ i ].w=1+10*clipfang[ i ].w*abs((cos(getazimuth(mr.x,mr.y,fangx[i], fangy[i]))/cos(oldazimuth[i])));
				clipfang[ i ].h=1+10*clipfang[ i ].h*abs((sin(getazimuth(mr.x,mr.y,fangx[i], fangy[i]))/sin(oldazimuth[i])));
				oldazimuth[i]= getazimuth(mr.x,mr.y,fangx[i], fangy[i])+90; foa++; }/////
		for(i=2;i<4;i++){ox[i]=mr.x; oy[i]=mr.y;}
		}
		else if(foa<160){fangx[2]+=(ox[2]-fangx[2])/5;
		fangy[2]+=(oy[2]-fangy[2])/5;
		for(i=3;i<4;i++){
				clipfang[ i ].w=1+10*clipfang[ i ].w*abs((cos(getazimuth(mr.x,mr.y,fangx[i], fangy[i]))/cos(oldazimuth[i])));
				clipfang[ i ].h=1+10*clipfang[ i ].h*abs((sin(getazimuth(mr.x,mr.y,fangx[i], fangy[i]))/sin(oldazimuth[i])));
				oldazimuth[i]= getazimuth(mr.x,mr.y,fangx[i], fangy[i])+90; foa++; }/////
		for(i=3;i<4;i++){ox[i]=mr.x; oy[i]=mr.y;}
		}
		else if(foa<190){fangx[3]+=(ox[3]-fangx[3])/5;
		fangy[3]+=(oy[3]-fangy[3])/5;
		}

		int i;
		for(i=0;i<4;i++){
			apply_surface( fangx[i], fangy[i], rotozoomSurface(BOSS[2],getazimuth(ox[i],oy[i],fangx[i], fangy[i])+90,1.0,0), screen, &clipfang[ 0 ] );}
		foa++;
	}

    if(foa>190){foa=0;}


}

bool NI::ifbehit(SDL_Rect mra){
	if(state<=10&&verticaloffSet<=(mra.y+mra.h)&&(mra.y-verticaloffSet)<=225){
			if(mra.x<=(paralleloffSet+223)&&mra.x>=paralleloffSet)
				{ hp--; return true; }
			if(paralleloffSet<=(mra.x+mra.w)&&paralleloffSet>=mra.x)
				{ hp--;return true; }
		}
		return false;
}

void NI::set_clips(){
	int i;
	for(i=0;i<2;i++){
		clipbody[i].h=225;
		clipbody[i].w=223;
		clipbody[i].x=223*i;
		clipbody[i].y=0;
	}
	for(i=0;i<10;i++){
			clipA[i%5][i/5].h=294;
			clipA[i%5][i/5].w=387;
			clipA[i%5][i/5].x=387*(i/5);
			clipA[i%5][i/5].y=294*(i%5);
		}
	for(i=0;i<4;i++){
			clipfang[i].h=38;
			clipfang[i].w=200;
			clipfang[i].x=0;
			clipfang[i].y=0;
		}
	for(i=0;i<3;i++){
				clipst[i].h=309;
				clipst[i].w=302;
				clipst[i].x=302*i;
				clipst[i].y=0;
			}
}


TV::TV(int x,int y)
{   pp=0;
	paralleloffSet=x;
	verticaloffSet=y;
	state=0;
	parallelvelocity=0;
	verticalvelocity=0;
	hp=30;
	damage=1;
	load_pic(".\\BOSS\\TVOK\\TV.png");
	set_clips();
	frame=0;
	loadmus(".\\mus\\Boss\\06.ogg");
}
void TV::acting(Superugly &mr,Background* map){
	if(!Mix_PlayingMusic()){Mix_PlayMusic( bmus, -1 );}
	if(!isdead()){mr.handleHP(clip[0],paralleloffSet,verticaloffSet);
		move(map); attack(mr.place); state=0; state++;}

}

bool TV::isdead()
{
	if(hp<=0){pp=0; BOSS[0]=NULL; paralleloffSet=0; verticaloffSet=0; return true;}
	return false;
}

void TV::move(Background* map)
{   static int t=0;
	verticaloffSet+=10*cos((++t)/2.5);    //if(!mapin){verticaloffSet-=10*cos((++t)/2.5;}
	apply_surface( paralleloffSet, verticaloffSet, BOSS[0], screen, &clip[ (frame/2)%8 ] );
	frame++;

}

void TV::attack(SDL_Rect mr){
	static int enu=0;
	static monster_score_0 s1(100,100); if(enu==0){s1.loadscore0(); s1.setclips();} s1.move(); s1.show(mr);
	static monster_score_0 s2(125,100); if(enu==0){s2.loadscore0(); s2.setclips();}  s2.move(); s2.show(mr);
	static monster_score_0 s3(87,100); if(enu==0){s3.loadscore0(); s3.setclips();} s3.move(); s3.show(mr);
	static monster_score_0 s4(50,100); if(enu==0){s4.loadscore0(); s4.setclips();} s4.move(); s4.show(mr);
	static monster_score_0 s5(46,100); if(enu==0){s5.loadscore0(); s5.setclips();}  s5.move(); s5.show(mr);
	static monster_score_0 s6(444,100); if(enu==0){s6.loadscore0(); s6.setclips();}  s6.move(); s6.show(mr);
	static monster_score_0 s7(258,100); if(enu==0){s7.loadscore0(); s7.setclips();}  s7.move(); s7.show(mr);
	static monster_score_0 s8(357,100); if(enu==0){s8.loadscore0(); s8.setclips();}  s8.move(); s8.show(mr);
	static monster_score_0 s9(95,100); if(enu==0){s9.loadscore0(); s9.setclips();} s9.move(); s9.show(mr);
	 enu++;
}

bool TV::ifbehit(SDL_Rect mra){
	if(verticaloffSet<=(mra.y+mra.h)&&(mra.y-verticaloffSet)<=225){
				if(mra.x<=(paralleloffSet+223)&&mra.x>=paralleloffSet)
					{ hp--; return true; }
				if(paralleloffSet<=(mra.x+mra.w)&&paralleloffSet>=mra.x)
					{ hp--;return true; }
			}
			return false;
}

void TV::set_clips(){
	int i;
	for(i=0;i<8;i++){
		clip[i].h=TV_h;
		clip[i].w=TV_w;
		clip[i].x=0;
		clip[i].y=TV_h*i;
	}
}


MINI::MINI(int x,int y)
{   pp=0;
	paralleloffSet=x;
	verticaloffSet=y;
	parallelvelocity=0;
	verticalvelocity=0;
	hp=1;
	loadmus(".\\mus\\Boss\\08.ogg");
	load_pic(".\\BOSS\\miniOK\\mini.png");
	set_clips();
	frame=0;

}

void MINI::acting(Superugly mr,Background *map){if(!Mix_PlayingMusic()){Mix_PlayMusic( bmus, -1 );}  if(!isdead()){move(mr.place.x,map);} }

bool MINI::isdead()
{
	if(hp<=0){BOSS[0]=NULL; pp=0; paralleloffSet=0; verticaloffSet=0; return true;}
	return false;
}

void MINI::move(int c,Background* map)
{
   if(paralleloffSet>=c){paralleloffSet+=10; frame=1;}
   else{paralleloffSet-=10;  frame=0;}
   if(!map->walkRange(paralleloffSet,verticaloffSet,clip[0].w,clip[0].h)){paralleloffSet=rand()%1200;  verticaloffSet=rand()%650+50;}//////
	apply_surface( paralleloffSet, verticaloffSet, BOSS[0], screen, &clip[ frame ] );
}

bool MINI::ifbehit(SDL_Rect mra){                     //////////
	if(verticaloffSet<=(mra.y+mra.h)&&(mra.y-verticaloffSet)<=225){
				if(mra.x<=(paralleloffSet+223)&&mra.x>=paralleloffSet)
					{ hp--; return true; }
				if(paralleloffSet<=(mra.x+mra.w)&&paralleloffSet>=mra.x)
					{ hp--;return true; }
			}
			return false;
}

void MINI::set_clips(){
	int i;
	for(i=0;i<2;i++){
		clip[i].h=70;
		clip[i].w=70;
		clip[i].x=0;
		clip[i].y=70*i;
	}
}


TML::TML(int x,int y)
{   pp=0;
	paralleloffSet=x;
	verticaloffSet=y;
	state=0;
	parallelvelocity=0;
	verticalvelocity=0;
	hp=15;
	damage=0;
	load_pic(".\\BOSS\\TMLOK\\TML.png");
	load_pic(".\\BOSS\\TMLOK\\TMLb.png");
	load_pic(".\\BOSS\\TMLOK\\TMLbA.png");
	set_clips();
	frame=0;
	loadmus(".\\mus\\Boss\\20.ogg");

}
void TML::acting(Superugly& mr,Background *map)
{    if(!isdead()){  mr.handleHP(clipbody[0],paralleloffSet,verticaloffSet);
	if(state%100>=66&&state%100<=100){attack(mr.place);  }else{move(map);} state++;}
if(!Mix_PlayingMusic()){Mix_PlayMusic( bmus, -1 );}
}
bool TML::isdead()
{
	if(hp<=0){  BOSS[2]=NULL; BOSS[1]=NULL; BOSS[0]=NULL; pp=0; paralleloffSet=0; verticaloffSet=0; return true;}
	return false;
}

void TML::move(Background* map)
{   static int t=0;
static int i=0,p1,p2;
 if(i==0){p1=(rand()%25)*pow(-1,rand());}
 if(i==5){i=-1;}
	if(state==0){verticaloffSet+=10*cos(++t/3);}
	if(p1>0){frame=1;}else{frame=0;}
	paralleloffSet+=p1;
	p2=(rand()%10)*pow(-1,rand());
	verticaloffSet+=p2;
	if(!map->walkRange(paralleloffSet,verticaloffSet,clipbody[0].w,clipbody[0].h)){paralleloffSet-=p1;
	verticaloffSet-=p2;}
i++;
	apply_surface( paralleloffSet, verticaloffSet, BOSS[0], screen, &clipbody[ frame ] );/////
	apply_surface( paralleloffSet+(rand()%10), verticaloffSet-(rand()%10), BOSS[1], screen, &clipbook[ frame ] );

}

void TML::attack(SDL_Rect mr){

	static int enu=0;
		static monster_score_0 s1(100,100); if(enu==0){s1.loadscore0(); s1.setclips();} s1.move(); s1.show(mr);
		static monster_score_0 s2(125,100); if(enu==0){s2.loadscore0(); s2.setclips();}  s2.move(); s2.show(mr);
		static monster_score_0 s3(87,100); if(enu==0){s3.loadscore0(); s3.setclips();} s3.move(); s3.show(mr);
		static monster_score_0 s4(50,100); if(enu==0){s4.loadscore0(); s4.setclips();} s4.move(); s4.show(mr);
		static monster_score_0 s5(46,100); if(enu==0){s5.loadscore0(); s5.setclips();}  s5.move(); s5.show(mr);
		static monster_score_0 s6(444,100); if(enu==0){s6.loadscore0(); s6.setclips();}  s6.move(); s6.show(mr);
		static monster_score_0 s7(258,100); if(enu==0){s7.loadscore0(); s7.setclips();}  s7.move(); s7.show(mr);
		static monster_score_0 s8(357,100); if(enu==0){s8.loadscore0(); s8.setclips();}  s8.move(); s8.show(mr);
		static monster_score_0 s9(95,100); if(enu==0){s9.loadscore0(); s9.setclips();} s9.move(); s9.show(mr);
		static monster_score_0 s10(95,100); if(enu==0){s10.loadscore0(); s10.setclips();} s10.move(); s10.show(mr);
		static monster_score_0 s11(95,100); if(enu==0){s11.loadscore0(); s11.setclips();} s11.move(); s11.show(mr);
		static monster_score_0 s12(95,100); if(enu==0){s12.loadscore0(); s12.setclips();} s12.move(); s12.show(mr);
		static monster_score_0 s13(95,100); if(enu==0){s13.loadscore0(); s13.setclips();} s13.move(); s13.show(mr);
		static monster_score_0 s14(95,100); if(enu==0){s14.loadscore0(); s14.setclips();} s14.move(); s14.show(mr);
		static monster_score_0 s15(95,100); if(enu==0){s15.loadscore0(); s15.setclips();} s15.move(); s15.show(mr);
		 enu++;
	apply_surface( paralleloffSet, verticaloffSet, BOSS[0], screen, &clipbody[ frame ] );/////
		apply_surface( paralleloffSet+(rand()%50), verticaloffSet-(rand()%50), BOSS[2], screen, &clipbookA[ frame ] );
}

bool TML::ifbehit(SDL_Rect mra){
	if(verticaloffSet<=(mra.y+mra.h)&&(mra.y-verticaloffSet)<=225){
				if(mra.x<=(paralleloffSet+223)&&mra.x>=paralleloffSet)
					{ hp--; return true; }
				if(paralleloffSet<=(mra.x+mra.w)&&paralleloffSet>=mra.x)
					{ hp--;return true; }
			}
			return false;
}

void TML::set_clips(){
	int i;
	for(i=0;i<2;i++){
		clipbody[i].h=220;
		clipbody[i].w=180;
		clipbody[i].x=0;
		clipbody[i].y=220*i;
	}
	for(i=0;i<2;i++){
			clipbookA[i].h=120;
			clipbookA[i].w=115;
			clipbookA[i].x=0;
			clipbookA[i].y=120*i;
		}
	for(i=0;i<2;i++){
			clipbook[i].h=57;
			clipbook[i].w=47;
			clipbook[i].x=0;
			clipbook[i].y=57*i;
		}
}


bool load_pic(string name)
{

    BOSS[pp] = load_image_alpha(name);
    pp++;
    if( BOSS[pp-1] == NULL )
    {
        return false;
    }

    return true;
}

double getazimuth(int mrx,int mry,int enx,int eny){
	double up=(mrx-enx), dow=(mry-eny);
	double azimuth=atan(up/dow)*180/PI;
	if(up<0){
		if(dow<0){
			azimuth+=180.0;
		}
		else{
			azimuth+=360.0;}
	}
	else if(dow<0){
		azimuth+=180.0;
	}
	return azimuth;
}

void loadmus(char *a){
	if(bmus!=NULL){if(Mix_PlayingMusic()){Mix_HaltMusic();}}
	bmus=Mix_LoadMUS(a);


}
