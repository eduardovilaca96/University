#ifndef __MAPA_H__
#define __MAPA_H__
#include "state.h"
#include "math.h"

void spawn_square(int x, int y, int size) {
int i, j;

for (i = x; i < x + size; i++) {
    for (j = y; j < y + size; j++) {
        if(mvinch(j,i) == ' ') mvaddch(j, i, '"' | COLOR_PAIR(2));
    }
}
}

void menu_draw(){
	attron(COLOR_PAIR(3));
	printw("\n");
	printw("                                                  !_\n");
    printw("                                                  |*~=-., _____                                            _____          _   _      \n");
    printw("                                                  |_,-'` |  __ \\                                          / ____|        | | | |     \n");
    printw("                                                  |      | |  | |_   _ _ __   __ _  ___  ___  _ __  ___  | |     __ _ ___| |_| | ___ \n");
    printw("                                                  |      | |  | | | | | '_ \\ / _` |/ _ \\/ _ \\| '_ \\/ __| | |    / _` / __| __| |/ _ \\ \n");
    printw("                                                 /^\\     | |__| | |_| | | | | (_| |  __/ (_) | | | \\__ \\ | |___| (_| \\__ \\ |_| |  __/\n");
    printw("                   !_                           /   \\    |_____/ \\__,_|_| |_|\\__, |\\___|\\___/|_| |_|___/  \\_____\\__,_|___/\\__|_|\\___|\n");
    printw("                   |*`~-.,                     /,    \\                        __/ |                                                  \n");
    printw("                   |.-~^`                     /#\"     \\                      |___/                                                   \n");
    printw("                   |                        _/##_   _  \\_  \n");				
    printw("              _   _|  _   _   _            [ ]_[ ]_[ ]_[ ]      \n");
    printw("             [ ]_[ ]_[ ]_[ ]_[ ]            |_=_-=_ - =_|                  1. Start Game\n");
    printw("           !_ |_=_ =-_-_  = =_|           !_ |=_= -    |                   2. How to Play\n");
    printw("           |*`--,_- _        |            |*`~-.,= []  |                   q. Exit\n");
    printw("           |.-'|=     []     |   !_       |_.-\"`_-     |\n");
    printw("           |   |_=- -        |   |*`~-.,  |  |=_-      |\n");
    printw("          /^\\  |=_= -        |   |_,-~`  /^\\ |_ - =[]  |\n");
    printw("      _  /   \\_|_=- _   _   _|  _|  _   /   \\|=_-      |\n");
    printw("     [ ]/,    \\[ ]_[ ]_[ ]_[ ]_[ ]_[ ]_/,    \\[ ]=-    |\n");
    printw("      |/#\"     \\_=-___=__=__=_ -=_ /#\"     \\| _ []     |\n");
    printw("     _/##_   _  \\_-_ =  _____       _/##_   _  \\_ -    |\\\n");
    printw("    [ ]_[ ]_[ ]_[ ]=_0~{_ _ _}~0   [ ]_[ ]_[ ]_[ ]=-   | \\\n");
    printw("    |_=__-_=-_  =_|-=_ |  ,  |     |_=-___-_ =-__|_    |  \\\n");
    printw("     | _- =-     |-_   | ((* |      |= _=       | -    |___\\\n");
    printw("     |= -_=      |=  _ |  `  |      |_-=_       |=_    |/+||\n");
    printw("     | =_  -     |_ = _ `-.-`       | =_ = =    |=_-   ||+||\n");
    printw("     |-_=- _     |=_   =            |=_= -_     |  =   ||+||\n");
    printw("     |=_- /+\\    | -=               |_=- /+\\    |=_    |^^^|\n");
    printw("     |=_ |+|+|   |= -  -_,--,_      |_= |+|+|   |  -_  |=  |\n");
	printw("     |  -|+|+|   |-_=  / |  | |     |=_ |+|+|   |-=_   |_-/\n");
	printw("     |=_=|+|+|   | =_= | |  | |     |_- |+|+|   |_ =   |=/\n");
	printw("     | _ ^^^^^   |= -  | |  <&>     |=_=^^^^^   |_=-   |/\n");
	printw("     |=_ =       | =_-_| |  | |     |   =_      | -_   |\n");
	printw("     |_=-_       |=_=  | |  | |     |=_=        |=-    |\n");
	printw("^^^`^`^`^`^^^^^`^`^^`^`^`^^^""""""""^`^^``^^`^^`^^`^`^``^`^``^``^^^^\n");
	attroff(COLOR_PAIR(3));
}


void menu_draw2(){
    	attron(COLOR_PAIR(3));
		printw("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t~~~~~~~~~~~~~~~CARACTERS~~~~~~~~~~~~~~\n");
		attroff(COLOR_PAIR(3));
		attron(COLOR_PAIR(5));
		printw("\t\t\t\t\t\t @");
		attroff(COLOR_PAIR(5));
		attron(COLOR_PAIR(3));
		printw(" - Hero (DMG-40 HP-100)\n");
		attroff(COLOR_PAIR(3));
		attron(COLOR_PAIR(1));
		printw("\t\t\t\t\t\t J");
		attroff(COLOR_PAIR(1));
		attron(COLOR_PAIR(3));
		printw(" - Javali (DMG-15 HP-100)\n");
		attroff(COLOR_PAIR(3));
		attron(COLOR_PAIR(2));
		printw("\t\t\t\t\t\t G");
		attroff(COLOR_PAIR(2));
		attron(COLOR_PAIR(3));
		printw(" - Goblin (DMG-4 HP-40)\n");
		printw("\t\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printw("\t\t\t\t\t\t~~~~~~~~~~~~~~~~~AREAS~~~~~~~~~~~~~~~~\n");
		attroff(COLOR_PAIR(3));
		attron(COLOR_PAIR(6));
		printw("\t\t\t\t\t\t F");
		attroff(COLOR_PAIR(6));
		attron(COLOR_PAIR(3));
		printw(" - Healing Fountain (+10 HP)\n");
		attroff(COLOR_PAIR(3));
		attron(COLOR_PAIR(2));
		printw("\t\t\t\t\t\t \"");
		attroff(COLOR_PAIR(2));
		attron(COLOR_PAIR(3));
		printw(" - Bushes (enemies dont see you)\n");
		printw("\t\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printw("\t\t\t\t\t\t~~~~~~~~~~~~~~KEY BINDINGS~~~~~~~~~~~~\n");
		printw("\t\t\t\t\t\t d - Heal at fountain\n");
		printw("\t\t\t\t\t\t z - Attack \n");
		printw("\t\t\t\t\t\t e - Open door\n");
		printw("\t\t\t\t\t\t q - Exit game\n");
		printw("\t\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

		attroff(COLOR_PAIR(3));	
}


//walls
void gerar(int *x, int*y){
    attron(COLOR_PAIR(3));
    //horizontal hole
    srand(time(NULL));
    int spacebegin = rand() % (COLS -4)+1;
    
    mvhline(LINES/2, 0, '#', COLS+2);
    
    mvprintw(LINES/2,spacebegin,"_____");

    //upwall
    int wallup = rand() % ((COLS / 2))+35;
    if(spacebegin < wallup && wallup < spacebegin+5){
        wallup+=5;
    }
    int spacebegin2 = (rand() % ((LINES/2)-4))+4;
    
    mvvline(0,wallup,'#',LINES/2);
    
    int i = 0;
    while(i < 3){
        mvprintw(spacebegin2-i,wallup,"|");
        i++;
    }

    //downwall
    int downwall = rand() % ((COLS / 2))+35;
    int spacebegin3 = (rand() % ((LINES-8) - (LINES/2)+3)+(LINES/2)+4);

    if((spacebegin < downwall && downwall < spacebegin+5) ){
        downwall+=5;
    }
    
    mvvline(LINES/2,downwall,'#',LINES/2);
    
    i = 0;
    while(i < 3){
        mvprintw(spacebegin3-i,downwall,"|");
        i++;
    }
    
    mvhline(0, 0, '#', COLS+2);//top
    mvvline(0,0,'#',LINES);//left
    mvvline(0,COLS+1,'#',LINES);//right
    mvhline(LINES-1, 0, '#', COLS+2);//bottom
    attroff(COLOR_PAIR(3));

    *x = wallup;
    *y = downwall;
}
#endif
