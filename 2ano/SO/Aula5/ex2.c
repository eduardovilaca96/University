#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    
    pid_t pid = fork();

    switch (pid)
    {
    case -1:
        printf("erro no fork");
        break;
    
    case 0:
        int ret = execlp("ls","ls","-l", NULL);
        _exit(ret);
        break;
    
    default:
        int status;
        wait(&status);
		if(WIFEXITED(status)){
			printf("%d\n",WEXITSTATUS(status));
		}else{
			printf("Filho Interrompido \n");
		}

        break;
    }

    

    return 0;
}
