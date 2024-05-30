#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>

void defeitos(char* imagens[], int n, int max){
    int i = 0;
    char *arr[] = {"echo", "entrei", NULL };
    int running = 0;
    while(i < n){
        if(running < max){
            pid_t pid = fork();
            if(pid == 0){
                //Child Process
                int ret = execvp(arr[0], arr);
                perror("execvp");
                exit(1);
            }else if(pid > 0){
                running++;
                i++;
            }
        }else{
            int status;
            wait(&status);
            running--;
        }
    }
}

void conta(char* imagens[], int n) {
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) { 
        close(pipefd[0]);  
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        defeitos(imagens, n, 5);

        close(pipefd[1]);
        exit(0);
    } else {
        wait(NULL);
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        execlp("wc", "wc", "-l", NULL);

        perror("execlp");
        exit(1);
    }
}



int main(int argc, char *argv[]) {
    char *arr[] = { "Geek", "Geeks", "Geekfor" };
    conta(arr,3);
    return 0;
}