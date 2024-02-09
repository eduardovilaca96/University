#ifndef __STATE_H__
#define __STATE_H__
#include "mapa.h"

typedef struct state {
	int playerX;
	int playerY;
	int health;
	bool hidden;
	int range;
	int damage;
	int score;
	int room;
} STATE;

void neardoor(STATE st){
	if(mvinch(st.playerX,st.playerY+1) == 892 || mvinch(st.playerX,st.playerY-1) == 892 || mvinch(st.playerX+1,st.playerY) == 863 || mvinch(st.playerX-1,st.playerY) == 863 ){
		mvprintw(LINES,COLS,"\nPress 'e' to open the door\n");
	}
}

int nearfountain(STATE st){
	int flag = 0;
	//F with CYAN
	if(mvinch(st.playerX,st.playerY+1) == 2098758 ||
	   mvinch(st.playerX,st.playerY-1) == 2098758 ||
	   mvinch(st.playerX+1,st.playerY) == 2098758 ||
	   mvinch(st.playerX-1,st.playerY) == 2098758 ||
	   mvinch(st.playerX-1,st.playerY-1) == 2098758 ||
	   mvinch(st.playerX-1,st.playerY+1) == 2098758 ||
	   mvinch(st.playerX+1,st.playerY-1) == 2098758 ||
	   mvinch(st.playerX+1,st.playerY+1) == 2098758
	   ){
		attron(COLOR_PAIR(6));
		mvprintw(LINES,COLS,"\nPress 'd' to heal\n");
		attroff(COLOR_PAIR(6));
		flag++; 
	}
	return flag;
}

void updateRoom(STATE *st,int upwall, int downwall){
	if(st->playerY < upwall && st->playerX < LINES/2){
		st->room = 1;
	}else if(st->playerY > upwall && st->playerX < LINES/2){
		st->room = 2;
	}else if(st->playerY < downwall && st->playerX > LINES/2){
		st->room = 3;
	}else{
		st->room = 4;
	}
}

void draw_health(STATE st){
	//health bar
	attron(COLOR_PAIR(7));
	mvprintw(LINES,0,"Health: [");
	int i;
	for (i = 0; i < 100 /5; i++)
	{
		if(st.health >= 60) attron(COLOR_PAIR(2));
		if(st.health < 60 && st.health >= 30) attron(COLOR_PAIR(3));
		if(st.health < 30) attron(COLOR_PAIR(1));
		if (i <= st.health / 5) mvprintw(LINES,9+i,"|");
		else mvprintw(LINES,9+i," ");
		attroff(COLOR_PAIR(2));
		attroff(COLOR_PAIR(1));
		attroff(COLOR_PAIR(3));
	}

	mvprintw(LINES,9+i,"] %d hp ",st.health);
	attroff(COLOR_PAIR(7));
}

void heal(STATE *st){
	if(st->health > 90) st->health = 100;
	else if(st->health < 100){
		st->health +=10;
		attron(COLOR_PAIR(6));
		mvprintw(LINES,COLS,"\nYou have healed +10hp\n");
		attroff(COLOR_PAIR(6));
	}
	draw_health(*st);
}

#endif 