#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096

// cp
int mycp(char *origem, char *dest){

    int fd_origem = open(origem,O_RDONLY);
    int fd_destino = open(dest,O_WRONLY|O_CREAT,0600);

    char *buffer[BUFFER_SIZE];


    ssize_t res_read;
    
    while((res_read = read(fd_origem, buffer,BUFFER_SIZE))>0){     

        ssize_t res_write = write(fd_destino, buffer,res_read);    

        if(res_read != res_write) return 1;

    }
        
    close(fd_origem);
    close(fd_destino);


    return 0;
}


int main(int argc, char const *argv[])
{
    
    mycp(argv[1],argv[2]);
    return 0;
}





