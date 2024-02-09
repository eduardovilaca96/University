#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include "state.h"
#include "mapa.h"
#include "mob.h"

double distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void vision(STATE *st,int upwall, int downwall, int roomChars[][COLS+2]){

	if(st->room == 1){
		//show top left
		for (int y = 0; y < LINES/2+1; y++) {
			for (int x = 0; x < COLS+2; x++) {
				mvaddch(y, x, roomChars[y][x]);
			}
		}
		//hide bottom
		for (int y = LINES/2+1; y < LINES; y++) {
			for (int x = 0; x < COLS+2; x++) {
				mvaddch(y, x, ' ');
			}
		}
		//hide top right
		for (int y = 0; y < LINES; y++) {
			for (int x = upwall+1; x < COLS+2; x++) {
				mvaddch(y, x, ' ');
			}
		}
	}
	else if(st->room == 2){
		//show top right
		for (int y = 0; y < LINES/2+1; y++) {
			for (int x = upwall; x < COLS+2; x++) {
				mvaddch(y, x, roomChars[y][x]);
			}
		}
		//hide bottom
		for (int y = LINES/2+1; y < LINES; y++) {
			for (int x = 0; x < COLS+2; x++) {
				mvaddch(y, x, ' ');
			}
		}
		//hide top left
		for (int y = 0; y < LINES; y++) {
			for (int x = 0; x < upwall; x++) {
				mvaddch(y, x, ' ');
			}
		}
	}	
	else if(st->room == 3){
		//show bottom left
		for (int y = LINES/2; y < LINES; y++) {
			for (int x = 0; x < downwall+1; x++) {
				mvaddch(y, x, roomChars[y][x]);
			}
		}
		//hide top
		for (int y = 0; y < LINES/2; y++) {
			for (int x = 0; x < COLS+2; x++) {
				mvaddch(y, x, ' ');
			}
		}
		//hide bottom right
		for (int y = LINES/2; y < LINES; y++) {
			for (int x = downwall+1; x < COLS+2; x++) {
				mvaddch(y, x, ' ');
			}
		}
	}
	else{
		//show bottom right
		for (int y = LINES/2; y < LINES; y++) {
			for (int x = downwall; x < COLS+2; x++) {
				mvaddch(y, x, roomChars[y][x]);
			}
		}
		//hide top
		for (int y = 0; y < LINES/2; y++) {
			for (int x = 0; x < COLS+2; x++) {
				mvaddch(y, x, ' ');
			}
		}
		//hide bottom left
		for (int y = LINES/2; y < LINES; y++) {
			for (int x = 0; x < downwall; x++) {
				mvaddch(y, x, ' ');
			}
		}
	}
}


void do_movement_mob(STATE *st,MOB* mobs, int *nmobs){

	for (int i = 0; i < *nmobs; i++)
	{
		if(mobs[i].type == 'J')attron(COLOR_PAIR(1));
		if(mobs[i].type == 'G')attron(COLOR_PAIR(2));
		if(mobs[i].room == st->room)mvaddch(mobs[i].posX,mobs[i].posY,mobs[i].type | A_BOLD);
	}
	attroff(COLOR_PAIR(1));
	attroff(COLOR_PAIR(2));
	
	for (int i = 0; i < *nmobs; i++)
	{
		if(mobs[i].health > 0){
			if(!mobs[i].asleep  && mobs[i].room == st->room){
				double d = (int) distance(mobs[i].posX,mobs[i].posY,st->playerX,st->playerY);
				if(d != 0.0 && d <= mobs[i].vision){
					mvaddch(mobs[i].posX , mobs[i].posY, mobs[i].type | A_BOLD);
					attron(COLOR_PAIR(1));
					mvprintw(LINES,COLS,"\nWATCH OUT!! A %c AS SPOTTED YOU\n",mobs[i].type);
					attroff(COLOR_PAIR(1));
					int dx = (st->playerX - mobs[i].posX) / d;
					int dy = (st->playerY - mobs[i].posY) / d;

					if((mobs[i].posX + (dx*mobs[i].walk) != st->playerX || mobs[i].posY + (dy * mobs[i].walk) != st->playerY)){
						if(mvinch(mobs[i].posX + (dx*mobs[i].walk) , mobs[i].posY + (dy * mobs[i].walk)) == '.'){
							mvaddch(mobs[i].posX, mobs[i].posY, '.');	
							mobs[i].posX += dx * mobs[i].walk;
							mobs[i].posY += dy * mobs[i].walk;
							mvaddch(mobs[i].posX , mobs[i].posY, mobs[i].type | A_BOLD);
						}
					}

					if(d <= mobs[i].range){
						st->health -= mobs[i].damage;
						attron(COLOR_PAIR(1));
						mvprintw(LINES,COLS,"\nA %c ATTACKED YOU -%d  \n",mobs[i].type,mobs[i].damage);
						attroff(COLOR_PAIR(3));
					}
				}
			}
		}
	}
	draw_health(*st);


}

void do_movement_action(STATE *st, int dx, int dy,MOB* mobs, int *nmobs, int upwall, int downwall,int roomChars[][COLS+2]) {
	//test char
	// mvprintw(LINES/2,COLS/2,"%d",mvinch(st->playerX+dx,st->playerY+dy));

	// going out of the garden
	if(mvinch(st->playerX+dx,st->playerY+dy) == '.' && st->hidden){
		mvaddch(st->playerX, st->playerY, 546);
		st->hidden = false;
		st->playerX += dx;
		st->playerY += dy;
		mvprintw(LINES,COLS,"\n%d MOBS ALIVE | SCORE: %d\n",*nmobs,st->score);	
		neardoor(*st);
		nearfountain(*st);
		do_movement_mob(st,mobs,nmobs);
	}
	//walkable area
	else if(mvinch(st->playerX+dx,st->playerY+dy) == '.'){
		mvaddch(st->playerX, st->playerY, '.');
		st->hidden = false;
		st->playerX += dx;
		st->playerY += dy;
		mvprintw(LINES,COLS,"\n%d MOBS ALIVE | SCORE: %d\n",*nmobs,st->score);	
		neardoor(*st);
		nearfountain(*st);
		do_movement_mob(st,mobs,nmobs);
	}
	//gardens 
	else if(mvinch(st->playerX+dx,st->playerY+dy) == 546){
		mvaddch(st->playerX, st->playerY, 546 | COLOR_PAIR(2));
		st->hidden = true;
		st->playerX += dx;
		st->playerY += dy;
		vision(st,upwall,downwall,roomChars);
	}
}

void do_damage_mob(MOB* mobs, int *numMobs, STATE* state) {

    int i = 0;
    while (i < *numMobs) {
        MOB* mob = &mobs[i];
        int distanceSquared = distance(state->playerX,state->playerY,mob->posX,mob->posY);

        if (distanceSquared <= state->range && !mobs[i].asleep) {
			attron(COLOR_PAIR(6));
			mvprintw(LINES,COLS,"\nYou dealt %dhp to %c \n",state->damage,mobs[i].type);
			attroff(COLOR_PAIR(6));
            mob->health -= state->damage;
			if(mob->health <= 0){
				attron(COLOR_PAIR(2));
				mvprintw(LINES,COLS,"\nYou killed a %c\n",mobs[i].type);
				state->score+=mobs[i].score;
				attroff(COLOR_PAIR(2));
				mvaddch(mobs[i].posX,mobs[i].posY,'.');
				for (int j = i; j < *numMobs - 1; j++) {
					mobs[j] = mobs[j + 1];
				}
				(*numMobs)--;
			}
        }
		
        i++;
    }
}


void update(STATE *st, MOB* mobs, int *nmobs,int upwall,int downwall,int roomChars[][COLS+2]) {
	
	int key = getch();
	
	switch(key) {
		case KEY_A1:
		case '7': 
			do_movement_action(st, -1, -1,mobs,nmobs,upwall,downwall,roomChars);
		 break;
		case KEY_UP:
		case '8':
			do_movement_action(st, -1, +0,mobs,nmobs,upwall,downwall,roomChars);
		 break;
		case KEY_A3:
		case '9':
			do_movement_action(st, -1, +1,mobs,nmobs,upwall,downwall,roomChars);
		break;
		case KEY_LEFT:
		case '4':
			do_movement_action(st, +0, -1,mobs,nmobs,upwall,downwall,roomChars);
		break;
		case KEY_B2:
		case '5': break;
		case KEY_RIGHT:
		case '6':
			do_movement_action(st, +0, +1,mobs,nmobs,upwall,downwall,roomChars);
		break;
		case KEY_C1:
		case '1': 
			do_movement_action(st, +1, -1,mobs,nmobs,upwall,downwall,roomChars);
		break;
		case KEY_DOWN:
		case '2':
			do_movement_action(st, +1, +0,mobs,nmobs,upwall,downwall,roomChars);
		break;
		case KEY_C3:
		case '3': 
			do_movement_action(st, +1, +1,mobs,nmobs,upwall,downwall,roomChars);
		break;
		//attack
		case 'z':
			do_movement_mob(st,mobs,nmobs);
			do_damage_mob(mobs,nmobs,st);
		break;
		//open door
		case 'e':
			// _ | in different colors
			if(mvinch(st->playerX,st->playerY+1) == 892){
				mvaddch(st->playerX,st->playerY,'.');
				st->playerY+=2;
				updateRoom(st,upwall,downwall);
				vision(st,upwall,downwall,roomChars);
				do_movement_mob(st,mobs,nmobs);
			}else if(mvinch(st->playerX,st->playerY-1) == 892){
				mvaddch(st->playerX,st->playerY,'.');
				st->playerY-=2;
				updateRoom(st,upwall,downwall);
				vision(st,upwall,downwall,roomChars);
				do_movement_mob(st,mobs,nmobs);
			}else if(mvinch(st->playerX+1,st->playerY) == 863){
				mvaddch(st->playerX,st->playerY,'.');
				st->playerX+=2;
				updateRoom(st,upwall,downwall);
				vision(st,upwall,downwall,roomChars);
				do_movement_mob(st,mobs,nmobs);
			}else if(mvinch(st->playerX-1,st->playerY) == 863){
				mvaddch(st->playerX,st->playerY,'.');
				st->playerX-=2;
				updateRoom(st,upwall,downwall);
				vision(st,upwall,downwall,roomChars);
				do_movement_mob(st,mobs,nmobs);
			}

		break;
		//heal 
		case 'd':
		if(nearfountain(*st)){
			heal(st);
			do_movement_mob(st,mobs,nmobs);
		}
		break;
		case 'q':  endwin(); exit(0);break;
		default:
		
		break;
	}
	
}
int main() {

	initscr();
    WINDOW* wnd = newwin(LINES - 2, COLS - 2, 0, 0);
	box(wnd, 0, 0);
	getmaxyx(wnd,LINES,COLS);
	srand48(time(NULL));
	
	start_color();

	cbreak();
	noecho();
	nonl();

	intrflush(stdscr, false); 
	keypad(stdscr, true);

	//COLORS
	init_pair(0, COLOR_BLACK, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);

 
	//menu
	char opt;
	int score = 0;

	do{
	
	clear();
	menu_draw();
	refresh();
	opt = getch();

	//play
	if(opt == '1') {

	STATE st = {20,20,100,false,2,40,score,0};
	MOB mobs[20];
	
	//map and health bar
	clear();
	int upwall=0,downwall=0;
	gerar(&upwall,&downwall);
	attroff(COLOR_PAIR(3));
	draw_health(st);
	

	//spawn garden
	int k = -1;
	int grnd = (rand() % 5) +1;
	srand(time(NULL));
	while(k++ < grnd){
		int tam = (rand() % 6) +4;
		int randX = rand() % (COLS - 1 - tam) + 1;
		int randY = rand() % (LINES - 2 - tam) + 1;
		spawn_square(randX, randY, tam);
	}

	//spawn mobs
	int nmobs = 0;
	randomize_spawn_mb(mobs,&nmobs,upwall,downwall);		
	do_movement_mob(&st,mobs,&nmobs);

	//dots filling
	for (int y = 0; y < LINES; y++) {
		for (int x = 0; x < COLS+1; x++) {
			if (!(y == 0 || y == LINES - 1 || x == 0 || x == COLS+1)&&mvinch(y,x)==' '){
				mvaddch(y, x, '.');
			}
		}
	
	}

	//fountain
	int y =0,x=0;
	while(mvinch(y,x)!='.'){
		y= (rand() % (LINES -2))+1;
		x = rand() % (COLS);
	}
	mvaddch(y, x, 'F' | A_BOLD | COLOR_PAIR(6));

	//st pos
	srand(time(NULL));
	do {
		st.playerY = rand() % (COLS);
		st.playerX = (rand() % (LINES -2))+1;
	}while (mvinch(st.playerX,st.playerY)!='.');

	//clone first map
	int roomChars[LINES+1][COLS+2];
	for (int y = 0; y < LINES+1; y++)
	{
		for (int x = 0; x < COLS+2; x++)
		{
			roomChars[y][x] = mvinch(y,x);
		}
	}
	//update 1st time st room
	updateRoom(&st,upwall,downwall);
	//show 1st time st room
	vision(&st,upwall,downwall,roomChars);

	mvprintw(LINES,COLS,"\n %d MOBS ALIVE | SCORE: %d\n",nmobs,st.score);
	//show 1st time mobs 
	do_movement_mob(&st,mobs,&nmobs);

	while(1) {
		
		wrefresh(wnd);
		move(LINES +1, 0);
		getmaxyx(wnd,LINES,COLS);

		//bushes
		if(st.hidden){
			attron(COLOR_PAIR(2));
			mvprintw(LINES,COLS,"\nYou are now hidden in the bushes!\n");
			attroff(COLOR_PAIR(2));
		}

		//died
		if(st.health <= 0){
			clear();
			attron(COLOR_PAIR(3));
			mvprintw(LINES -(LINES/2)-3, COLS - (COLS/2)-8, "YOU DIED, BUT YOU DID WELL");
			mvprintw(LINES -(LINES/2)-2, COLS - (COLS/2)-8,"SCORE : %d",st.score);
			mvprintw(LINES -(LINES/2)-1, COLS - (COLS/2)-8, "Press any key to continue...");
			score = 0;
			attroff(COLOR_PAIR(3));
			getch();
			break;
		}
		//stage clear
		
		if(nmobs == 0){
			clear();
			attron(COLOR_PAIR(3));
			mvprintw(LINES -(LINES/2)-3, COLS - (COLS/2)-12, "CONGRATS YOU CLEARED THIS ROOM!!");
			mvprintw(LINES -(LINES/2)-2, COLS - (COLS/2)-12,   "SCORE : %d",st.score);
			mvprintw(LINES -(LINES/2)-1, COLS - (COLS/2)-12, "Press any key to continue...");
			score = st.score;
			attroff(COLOR_PAIR(3));
			getch();
			break;
		}

		//player movement
		mvaddch(st.playerX, st.playerY, '@' | A_BOLD | COLOR_PAIR(COLOR_MAGENTA));
		move(st.playerX, st.playerY);
		update(&st,mobs,&nmobs,upwall,downwall,roomChars);
	}
	}
	//keybindings
	else if(opt == '2'){
		clear();
		menu_draw2();
		getch();
	}
	} while ((opt != 'q'));
	//quit
	clear();endwin(); exit(0);
	return 0;
}

