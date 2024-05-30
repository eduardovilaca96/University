#include "person.h"


int add_person(char* name, int age){
	Person p;
	p.age = age;
	strcpy(p.name,name);
	int fd = open(FILENAME, O_CREAT | O_WRONLY | O_APPEND,0600);
	write(fd,&p,sizeof(p));

	char msg[15];
	int s = sprintf(msg,"Registo:%d\n",fd);
	write(1,msg,s);

	close(fd);

	return 0;
}

int list_persons(int nr){
	Person p;

	int fd = open(FILENAME,O_RDONLY);

	for (int i = 0; i < nr && read(fd,&p,sizeof(p))>0; ++i)
	{
		char msg[200];
		int s = sprintf(msg,"Registo: %s %d\n",p.name,p.age);
		write(1,msg,s);

	}

	close(fd);
	return 0;
}

int change_agev1(char* name, int newage){
	Person p;

	int fd = open(FILENAME,O_RDWR);

	while(read(fd,&p,sizeof(p))>0){
		if(strcmp(name,p.name)==0){
			p.age = newage;
			lseek(fd,-sizeof(p), SEEK_CUR);
			write(fd,&p,sizeof(p));
			close(fd);
			return 1;
		}
	}
	return 0;
}

int change_agev2(int reg,int newage){
	Person p;

	int fd = open(FILENAME,O_RDWR);

	/*while(read(fd,&p,sizeof(p))>0){
		if(strcmp(name,p.name)==0){
			p.age = newage;
			lseek(fd,-sizeof(p), SEEK_CUR);
			write(fd,&p,sizeof(p));
			close(fd);
			return 1;
		}
	}*/
	return 0;
}
