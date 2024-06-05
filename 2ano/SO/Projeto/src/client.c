#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_PATH_SERVER "../tmp/fifo_server"
#define FIFO_PATH_STATUS "../tmp/fifo_status"
#define MAX_BUF_SIZE 1024
#define STATUS_BUF_SIZE 3072

int main(int argc, char *argv[]) {
    int fd,fc,fs;
    char buf[MAX_BUF_SIZE];
    char status[STATUS_BUF_SIZE];
    char fifo_client[MAX_BUF_SIZE];
    int pid = getpid();
    memset(fifo_client, 0, MAX_BUF_SIZE);
    sprintf(fifo_client,"../tmp/fifo_%d",pid);

    if(strcmp(argv[1],"execute")==0 && argc == 5){

        mkfifo(FIFO_PATH_SERVER, 0666);       
        fd = open(FIFO_PATH_SERVER, O_WRONLY);
        if (fd != -1) {
            
            int type = (strcmp(argv[3],"-u")==0) ? 1 : 2;

            memset(buf, 0, MAX_BUF_SIZE);
            sprintf(buf,"%d_execute_%d_%s_%d",pid,atoi(argv[2]),argv[4],type);
            write(fd, buf, strlen(buf)+1);

            close(fd);
            unlink(FIFO_PATH_SERVER);

            mkfifo(fifo_client,0666);
            memset(buf, 0, MAX_BUF_SIZE);
            fc = open(fifo_client,O_RDWR);;
            if(fc == -1){
                perror("open");
                exit(EXIT_FAILURE);
            }
            
            while(1){
                if(read(fc,buf,18)>0){
                    write(1,buf,strlen(buf)+1);
                    write(1,"\n",1);
                    break;
                }
            }
            close(fc);
            unlink(fifo_client);
        }
    }else if(strcmp(argv[1],"status")==0){
        
        mkfifo(FIFO_PATH_SERVER, 0666);  
        fd = open(FIFO_PATH_SERVER, O_WRONLY);
        if (fd != -1) {
            memset(buf, 0, MAX_BUF_SIZE);
            sprintf(buf,"%d_status",pid);
            write(fd, buf, strlen(buf));
        }
        close(fd);
        unlink(FIFO_PATH_SERVER);
        
        mkfifo(fifo_client,0666);
        fs = open(fifo_client,0666);

        if(fs != -1){
            memset(status, 0, STATUS_BUF_SIZE);
            while(1){
                if(read(fs,status,STATUS_BUF_SIZE)>0){
                    write(1,status,strlen(status));
                    break;
                }
            }
            close(fs);
            unlink(fifo_client);
        }else{
            perror("open");
            write(1,"status cannot be run without orchestrator running.\n",52);
            exit(1);
        }
        


    }else{
        write(1,"usage: [execute] [time] [task-type] [command]\n",8);
        return 1;
    }
    

    return 0;
}
