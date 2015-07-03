#ifndef _POKER_H_
#define _POKER_H_

#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <algorithm>

using namespace std;


enum{
	GAMEOVER = 0,
	PLAYING   = 1
};
enum{
	CALL   = 11,
	CHECK  = 12,
	ALLIN  = 13,
	FOLD   = 14,
	RAISE  = 15
};

enum{
	IDEL		= 20,
	SEAT_PRO	= 21,
	BLIND_PRO	= 22,
	HOLD_PRO	= 23,
	INQ_PRO     = 24,

	FLOP_PRO	= 25,
	TURN_PRO	= 26,
	RIVER_PRO	= 27,
	SHOWD_PRO	= 28,
	POT_PRO		= 29
};
enum{
	NO_END     = 30,
	SEAT_END   = 31,
	BLIND_END  = 33,
	HOLD_END   = 33,
	INQ_END    = 34,
	FLOP_END   = 35,
	TURN_END   = 36,
	RIVER_END  = 37,
	SHOWD_END  = 38,
	POT_END    = 39
};
enum
{
	SPADES   = 'S',   //ºÚÌÒ
	HEARTS   = 'H',   //ºìÌÒ
	CLUBS    = 'C',   //Ã·»¨
	DIAMONDS = 'D',    //·½¿é
	COLOR    =  2,
	POINT    =  3
};

enum
{
	INQ_preflop = 40,
	INQ_flop    = 41,
	INQ_turn    = 42,
	INQ_river   = 43
};

enum
{
	FOLD_C = 50,
	NOFOLD = 51
};

enum
{
	ALL_IN_PAC = 'a',
	CHECK_PAC  = 'c',
	RAISE_PAC  = 'r',
	FOLD_PAC   = 'f',
	BLIND_PAC  = 'b'
};

class holdcard
{
public:
	string color;
	string point; //2-9 x(10)jqka
};
class flopcard
{
public:
	string color;
	string point; //2-9 x(10)jqka
};
class turncard
{
public:
	string color;
	string point; //2-9 x(10)jqka
};
class rivercard
{
public:
	string color;
	string point; //2-9 x(10)jqka
};
class gamer
{
public:
	string bblind;
	string sblind;
	holdcard h_card;
	flopcard f_card;
	turncard t_card;
	rivercard r_card;
   	int process_cnt;
	int process_reg;
	int foldcard;
	string play_action;
	int play_all;
	
	void add_bblind(char gchar)
	{
		bblind.push_back(gchar);
	}
	void add_sblind(char gchar)
	{
		sblind.push_back(gchar);
	}
	void add_h_card(char gchar,int flag) //flag 2 color flag 3 point
	{
		if(flag == COLOR)
			h_card.color.push_back(gchar);
		else if(flag == POINT)
			h_card.point.push_back(gchar);
	}
	void add_f_card(char gchar,int flag) //flag 2 color flag 3 point
	{
		if(flag == COLOR)
			f_card.color.push_back(gchar);
		else if(flag == POINT)
			f_card.point.push_back(gchar);
	}
	void add_t_card(char gchar,int flag) //flag 2 color flag 3 point
	{
		if(flag == COLOR)
			t_card.color.push_back(gchar);
		else if(flag == POINT)
			t_card.point.push_back(gchar);
	}
	void add_r_card(char gchar,int flag) //flag 2 color flag 3 point
	{
		if(flag == COLOR)
			r_card.color.push_back(gchar);
		else if(flag == POINT)
			r_card.point.push_back(gchar);
	}
	void add_play_ac(char gchar)
	{
		play_action.push_back(gchar);
	}
	void process_cnt_change(int pcc)
	{
		process_cnt = pcc;
	}
	void foldcard_change(int statu)
	{
		foldcard = statu;
	}
	void clear_gamer()
	{
		bblind.clear();
		sblind.clear();
		h_card.color.clear();
		h_card.point.clear();
		f_card.color.clear();
		f_card.point.clear();
		t_card.color.clear();
		t_card.point.clear();
		r_card.color.clear();
		r_card.point.clear();
		play_action.clear();
		process_reg = IDEL;
		foldcard = NOFOLD;
		play_all = 0;
	}
};


extern string b_reg;
extern int process;
extern string msg_reg;
extern int cnt;
extern gamer g;
extern int sockfd;
extern int ac_time;
int get_info(char buff);
#endif

