#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"

int mkfifo(const char *pathname, mode_t mode);


int main (int argc, char * argv[]){

	if (argc < 2) {
		printf("Missing argument.\n");
		_exit(1);
	}

	//TODO
	Msg m;
	m.needle = atoi(argv[1]);
	m.pid = getpid();
	m.occurrences = 0;

	char fifoc__name[30];
	sprintf(fifoc__name,CLIENT "%d",m.pid);
	if(mkfifo(fifoc__name,0666) == -1){
		perror("mkfifo client");
		return -1;
	}

	write(fds,&m,sizeof(m)));
	close(fds);
	int fdc = open(fifoc__name,m.pid,O_RDONLY);
	int fds =open(SERVER,O_WRONLY);
	read(fds,)
	close(fds);

	printf("number of occurences %d\n",m.occurrences);
	close(fdc);

	unlink(fifoc__name);
	
	return 0;
}

