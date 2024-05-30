#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
int main(){

    int infd = open("/etc/passwd",O_RDONLY);
    int outfd = open("saida.txt",O_CREAT | O_TRUNC | O_WRONLY,0666);
    int errfd = open("erros.txt",O_CREAT | O_TRUNC | O_WRONLY,0666);

    
    dup2(infd,0);
    close(infd);

    dup2(outfd,1);
    close(outfd);

    dup2(errfd,2);
    close(errfd);
    

    char buffer[1024];
    int read_res;
    while((read_res = read(0,buffer,1024))>0){
        write(1,buffer,read_res);
        write(2,buffer,read_res);
    }

    printf("terminei\n");
    return 0;
}