#ifndef __MOB_H__
#define __MOB_H__

typedef struct mob {
	char type;
	int posX;
	int posY;
	int health;
	int damage;
	int vision;
	int walk;
	int range;
	bool asleep;
	int room;
	int score;
} MOB;

MOB javali = {'J',0,0,100,15,8,2,1,false,0,10};
MOB goblin = {'G', 0, 0, 50, 4, 12,4,3, false,0,5};
// MOB spider = {'S', 0, 0, 50, 4, 12, 1,2, true,0};

void randomize_spawn_mb(MOB *mobs, int *nmobs,int upwall, int downwall){
	srand(time(NULL));
	*nmobs = (rand() % 4)+8;
	int i = 0;
	srand(time(NULL));
	while (i < *nmobs) {

		int type = rand() %2;
		int x = (rand() % (LINES -2))+1;
		int y = rand() % (COLS)+1;
		if(mvinch(x,y)==' '){
		MOB* mob;
		if(type == 0) mob = &javali;
		else  mob = &goblin;

		mob->posX = x;
		mob->posY = y;

		if(y < upwall  && x < LINES/2 ){
			mob->room = 1;
		}else if(y > upwall && x< LINES/2){
			mob->room = 2;
		}else if(y < downwall  && x > LINES/2){
			mob->room = 3;
		}else{
			mob->room = 4;
		}
		mobs[i] = *mob;
		i++;
		}

    }
	
	
}
#endif