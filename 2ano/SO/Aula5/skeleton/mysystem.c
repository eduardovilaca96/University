#include "mysystem.h"
// recebe um comando por argumento
// returna -1 se o fork falhar
// caso contrario retorna o valor do comando executado
int mysystem (const char* command) {

	int res = -1;

	// Estamos a assumir numero maximo de argumentos
	// isto teria de ser melhorado com realloc por exemplo
	// "ls -a -l -r" -> 


	char *exec_args[20];
	char *string, *cmd, *tofree;
	int i=0;
	tofree = cmd = strdup(command);
	while((string = strsep(&cmd," "))!=NULL){
	   exec_args[i]=string;
	   i++;
	}

	//["ls","-a","-l","-r",NULL]
	exec_args[i]=NULL;

	int ret2 = res = execv(exec_args);
	_exit(ret2);

	free(tofree);

	return res;
}