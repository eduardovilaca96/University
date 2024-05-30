#include "matrix.h"


int **createMatrix() {

    // seed random numbers
    srand(time(NULL));

    // Allocate and populate matrix with random numbers.
    printf("Generating numbers from 0 to %d...", MAX_RAND);
    int **matrix = (int **) malloc(sizeof(int*) * ROWS);
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = rand() % MAX_RAND;
        }
    }
    printf("Done.\n");

    return matrix;
}

void printMatrix(int **matrix) {

    for (int i = 0; i < ROWS; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < COLUMNS; j++) {
            printf("%7d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// ex.5
int valueExists(int **matrix, int value) {

    for (int i = 0; i < ROWS; ++i)
	{
		pid_t pid = fork();
        
		if(pid == 0){
            for (int k = 0; k < COLUMNS; k++)
            {
                if(value == matrix[i][k]){
                    
                    _exit(1); 
                } 
            }
            _exit(-1);
		}


	}
    int res = 0;
	for (int i = 1; i < 10; ++i)
	{ 
		int status;
		pid_t wait_pid = wait(&status);
        
		if(WIFEXITED(status)){ 
			if(WEXITSTATUS(status)==1){
                res = 1;
            }
		}else{
            printf("Erro ao terminar\n");
        }
	}

    return res;
}


// ex.6
void linesWithValue(int **matrix, int value) {

    pid_t pids[ROWS];

    for (int i = 0; i < ROWS; ++i)
	{
		pid_t pid = fork();
        
		if(pid == 0){
            for (int k = 0; k < COLUMNS; k++)
            {
                if(value == matrix[i][k]){
                    _exit(1); 
                } 
            }
            _exit(-1);
		}else{
            pids[i] = pid; 
        }


	}
    
	for (int i = 0; i < 10; ++i)
	{ 
		int status;
		pid_t wait_pid = waitpid(pids[i],&status,0);
        
		if(WIFEXITED(status)){ 
			if(WEXITSTATUS(status)==1){
                printf("Encontrei Valor %d na linha %d\n",value,i);
            }else{
                printf("Não encontrei Valor %d na linha %d\n",value,i);
            }
		}else{
            printf("Erro ao terminar\n");
        }
	}
    
}