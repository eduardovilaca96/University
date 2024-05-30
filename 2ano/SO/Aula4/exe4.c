#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

	for (int i = 1; i < 10; ++i)
	{
		pid_t pid = fork();

		if(pid == 0){
			printf("FILHO: %d\n",i);
			sleep(2);
			_exit(i);
		}


	}
	for (int i = 1; i < 10; ++i)
	{
		int status;
		pid_t wait_pid = wait(&status);

		printf("wait_pid:%d\n",wait_pid);
		if(WIFEXITED(status)){
			printf("Valor exit filho: %d\n",WEXITSTATUS(status));
		}else{
			printf("Erro ao terminar \n");
		}
	}

	return 0;
}