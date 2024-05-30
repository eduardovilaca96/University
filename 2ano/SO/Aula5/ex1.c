#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    
    char *arr[3] = {"ls","-l",NULL};


    //caminho absoluto para o comando | argv[0] | flag -l | NULL (não ha mais nada po exec)
    //int ret = execl("/bin/ls","ls","-l", NULL);
    //int ret3 = execvl("/bin/ls",arr);
    // execlp utiliza o caminha relativo procura no $PATH default 
    //int ret2 = execlp("ls","ls","-l", NULL);
    int ret4 = execvp("ls",arr);
    
    

    if(ret4==-1){
        printf("erro exec");
    }

    printf("%s\n",argv[0]);
    return 0;
}
