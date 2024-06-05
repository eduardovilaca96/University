#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>
#include "../include/task.h"

#define FIFO_PATH "../tmp/fifo_server"
#define FIFO_PATH_STATUS "../tmp/fifo_status"
 
int main(int argc, char *argv[]) {


    if (argc == 4) {

        int fd,fc,fo;
        int taskNumber = 0;
        int executed = 0;
        int parallelTasks = 0;
        int queueSize = 100,executedSize = 100;
        int front = -1;  
        int rear = -1;      

        char buf[MAX_BUF_SIZE];
        char msg[MAX_BUF_SIZE+30];
        char endedBuff[MAX_BUF_SIZE];
        char fifo_client[MAX_BUF_SIZE];
        char b[32];
        char c[32];

        char outputFolder[256];
        memset(outputFolder,0,256);
        strcpy(outputFolder,argv[1]);

        Task *taskQueue = (Task*)malloc(queueSize * sizeof(Task));
        Task *executedArray = (Task*)malloc(executedSize * sizeof(Task));

        while (1) {

            for (int i = 0; i < executed; i++) {
                if(executedArray[i].status == 1){
                    memset(b, 0, 32);
                    sprintf(b, "../tmp/%d_completed", executedArray[i].id);
                    fo = open(b, O_RDONLY);
                    if (fo != -1) {
                        memset(c, 0, 32);
                        if (read(fo, c, 32) > 0) {
                            parallelTasks--;
                            executedArray[i].status = 2;
                            executedArray[i].elapsed_time = strtol(c,NULL,10);
                            close(fo);
                            unlink(b);
                        }
                    }
                }else{
                    continue;
                }
            }
            
            fd = open(FIFO_PATH, O_RDONLY);
            if (fd != -1) {

                if (read(fd, buf, MAX_BUF_SIZE) > 0) {

                    memset(msg, 0, MAX_BUF_SIZE+30);
                    sprintf(msg,"Received message: %s\n",buf);
                    write(1,msg,strlen(msg));

                    int currentPid = atoi(strtok(buf,"_"));                    
                    memset(fifo_client, 0, MAX_BUF_SIZE);
                    sprintf(fifo_client,"../tmp/fifo_%d",currentPid);                
                    fc = open(fifo_client,O_WRONLY);
                    
                    
                    while(1){
                        if (fc != -1) {
                            if(strcmp(strtok(NULL,"_"),"status")==0){
                                displayStatus(fc,taskQueue,front,rear,executed,executedArray);
                                break;
                            }else{
                                memset(msg, 0, MAX_BUF_SIZE);
                                taskNumber++;
                                sprintf(msg, "TASK %d RECEIVED", taskNumber);
                                write(fc, msg, strlen(msg));
                                close(fc);
                                Task task;
                                task.id = taskNumber;
                                task.time = atoi(strtok(NULL, "_"));
                                task.pid = currentPid;
                                task.status = 0; 
                                memset(task.command,0,256);
                                strcpy(task.command, strtok(NULL, "_"));
                                task.type = atoi(strtok(NULL, ""));
                                memset(buf, 0, MAX_BUF_SIZE);                    

                                if(strcmp(argv[3],"sjf")==0){
                                    enqueue_sjf(&front,&rear,&queueSize,taskQueue,task);
                                }else if(strcmp(argv[3],"ljf")==0){
                                    enqueue_ljf(&front,&rear,&queueSize,taskQueue,task);
                                }else{
                                    enqueue_fcfs(&front,&rear,&queueSize,taskQueue,task);
                                }
                                break;
                            }
                        } else{
                            fc = open(fifo_client,O_WRONLY);
                        }
                    }
                    
                }
            close(fd);
            }

            while (parallelTasks < atoi(argv[2]) && !isQueueEmpty(front, rear)) {
                executedArray[executed] = dequeue(&front,rear,taskQueue);
                executedArray[executed].status = 1;
                if(executedArray[executed].id != -1){
                    pid_t pid = fork();
                    if (pid == 0) {
                        if(executedArray[executed].type == 1){
                            execute_task(&(executedArray[executed]),outputFolder);
                        } 
                        else {
                            execute_task2(&(executedArray[executed]),outputFolder);
                        }
                        memset(endedBuff,0,MAX_BUF_SIZE);
                        sprintf(endedBuff,"../tmp/%d_completed",executedArray[executed].id);

                        long elapsedTime = (executedArray[executed].end_time.tv_sec - executedArray[executed].start_time.tv_sec) * 1000 + (executedArray[executed].end_time.tv_usec - executedArray[executed].start_time.tv_usec) / 1000;
                        char b[sizeof(long)];
                        snprintf(b,sizeof(long),"%ld",elapsedTime);

                        mkfifo(endedBuff,0666);
                        
                        int fe = open(endedBuff, 0666);
                        write(fe,b,strlen(b));
                        close(fe);
                        exit(0);
                    } else if (pid > 0) {
                        parallelTasks++;
                        executed++;
                        if(executed == executedSize){
                            resizeArray(&executedSize,executedArray);
                        }
                    }

                }
            }
    }
    }else{
        write(1,"usage: ./orchestrator [output_folder] [parallel-tasks] [sched-policy] \n",72);
        return 1;
    }
    return 0;
}
