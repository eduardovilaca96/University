#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"
#include "vector.h"

#include <sys/types.h>
#include <sys/stat.h>

int mkfifo(const char *pathname, mode_t mode);

//FIFO criado pelo servidor
//Cliente pode receber um sigpipe (concorrência!)

int main (int argc, char * argv[]){

	init_vector();
	print_vector();

	while(1){
		int fds;
		Msg m;

		if(fds = open(SERVER,O_RDONLY) == -1){

		}else{

		}

		int bytes_read;

		while(b)
		//TODO
		mkfifo(SERVER,0666);
		int fds = open(SERVER,1);
		while(read(fds,1024)>0){
			int oc = count_needle(m.needle);
			int fdc = open(m.pid,1);
			write( );
			close(fdc);
		}
		close(fds);
	}
	
	return 0;
}
