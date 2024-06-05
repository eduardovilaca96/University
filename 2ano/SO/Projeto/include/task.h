#define MAX_BUF_SIZE 1024
//Task Type
typedef struct {
    int id;
    int time;
    char command[256];
    pid_t pid;
    struct timeval start_time;
    struct timeval end_time;
    int status;
    int type;
    long elapsed_time;
} Task; 

//queue manipulation functions
int isQueueEmpty(int front, int rear) {
    return (front == -1 || front > rear);
}

int isQueueFull(int front, int rear, int queueSize) {
    return ((rear + 1) % queueSize == front);
}

void resizeQueue(int front, int rear, int *queueSize, Task *taskQueue) {
    int newSize = (rear + 1) * 2;
    Task *newQueue = (Task*)realloc(taskQueue, newSize * sizeof(Task));
    if (newQueue == NULL) {
        perror("realloc");
        exit(1);
    }
    queueSize = &newSize;
    taskQueue = newQueue;
}
void resizeArray(int *queueSize, Task *taskQueue) {
    int newSize = (*queueSize+1) * 2;
    Task *newQueue = (Task*)realloc(taskQueue, newSize * sizeof(Task));
    if (newQueue == NULL) {
        perror("realloc");
        exit(1);
    }
    queueSize = &newSize;
    taskQueue = newQueue;
}



void enqueue_fcfs(int *front, int *rear, int *queueSize, Task *taskQueue,Task task){
    if (*rear == *queueSize - 1) {  
        resizeQueue(*front,*rear,queueSize,taskQueue);
        return;  
    }  
    if (*front == -1) {  
        *front = 0;  
    }
    (*rear)++;
    taskQueue[*rear] = task;
}

void enqueue_sjf(int *front, int *rear, int *queueSize, Task *taskQueue, Task task) {
    if (*rear == *queueSize - 1) {
        resizeQueue(*front, *rear, queueSize, taskQueue);
        return;
    }
    if (*front == -1) {
        *front = 0;
    }
    
    int i = *rear;
    while (i >= *front && taskQueue[i].time > task.time) {
        taskQueue[i + 1] = taskQueue[i];
        i--;
    }
    taskQueue[i + 1] = task;
    (*rear)++;
}

void enqueue_ljf(int *front, int *rear, int *queueSize, Task *taskQueue, Task task) {
    if (*rear == *queueSize - 1) {
        resizeQueue(*front, *rear, queueSize, taskQueue);
        return;
    }
    if (*front == -1) {
        *front = 0;
    }
    
    int i = *rear;
    while (i >= *front && taskQueue[i].time < task.time) {
        taskQueue[i + 1] = taskQueue[i];
        i--;
    }
    taskQueue[i + 1] = task;
    (*rear)++;
}


Task dequeue(int *front,int rear,Task *taskQueue) {  
    Task element;
    strcpy(element.command,"");
    element.id = -1;
    if (*front == -1 || *front > rear) {  
        printf("Queue is empty");  
        return element;  
    }  
    element = taskQueue[*front];  
    (*front)++;  
    return element;  
}  

//executes
//execute deafult (-u)
int execute_task(Task *task,char *outputFolder) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        
        char *args[10];
        char *token;
        int i = 0;
        token = strtok(task->command, " ");

        while (token != NULL) {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL;

        char output_file[64];
        sprintf(output_file, "%sTASK_%d.out",outputFolder, task->id);
        
        int out = open(output_file, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
        int err = open(output_file, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);

        if(out == -1 || err == -1){
            perror("open"); exit(EXIT_FAILURE);
        } 

        dup2(out, STDOUT_FILENO);
        dup2(err, STDERR_FILENO);

        execvp(args[0], args);
        exit(0);
        
    } else if (pid > 0) {
        // Parent process
        gettimeofday(&task->start_time, NULL);
        int status;
        waitpid(pid, &status, 0);
        gettimeofday(&task->end_time, NULL);
        task->status =2;
        return 0;
    }else {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

//execute pipe handling (-p)
int execute_task2(Task *task,char *outputFolder) {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        char *args[10];
        char *token;
        int i = 0;
        token = strtok(task->command, "|");

        while (token != NULL) {
            args[i] = token;
            token = strtok(NULL, "|");
            i++;
        }
        args[i] = NULL;

        int num_commands = i;
        int pipes[num_commands - 1][2];

        for (int j = 0; j < num_commands - 1; j++) {
            if (pipe(pipes[j]) == -1) {
                perror("pipe");
                exit(1);
            }
        }

        char output_file[64];
        sprintf(output_file, "%sTASK_%d.out",outputFolder, task->id);

        int out = open(output_file, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
        int err = open(output_file, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);

        if (out == -1 || err == -1) {
            perror("open");
            exit(1);
        }

        for (int j = 0; j < num_commands; j++) {
            pid_t command_pid = fork();

            if (command_pid == 0) {
                if (j != 0) {
                    dup2(pipes[j - 1][0], STDIN_FILENO);
                    close(pipes[j - 1][0]);
                    close(pipes[j - 1][1]);
                }

                if (j != num_commands - 1) {
                    dup2(pipes[j][1], STDOUT_FILENO);
                    close(pipes[j][0]);
                    close(pipes[j][1]);
                } else {
                    dup2(out, STDOUT_FILENO);
                    dup2(err, STDERR_FILENO);
                }

                char *command_args[10];
                int k = 0;
                char *command_token = strtok(args[j], " ");

                while (command_token != NULL) {
                    command_args[k] = command_token;
                    command_token = strtok(NULL, " ");
                    k++;
                }
                command_args[k] = NULL;

                execvp(command_args[0], command_args);
                exit(1);
            }
        }

        for (int j = 0; j < num_commands - 1; j++) {
            close(pipes[j][0]);
            close(pipes[j][1]);
        }

        for (int j = 0; j < num_commands; j++) {
            wait(NULL);
        }

        exit(0);
    } else if (pid > 0) {
        // Parent process
        gettimeofday(&task->start_time, NULL);
        int status;
        waitpid(pid, &status, 0);
        gettimeofday(&task->end_time, NULL);
        task->status = 2;
        return 0;
    } else {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

//status handling
int displayStatus(int fc, Task *taskQueue,int front, int rear, int executed, Task *executedArray){
    char statusOutput[6000];
    char executeOutput[1024];
    char scheduledOutput[1024];
    char completedOutput[1024];

    memset(statusOutput,0,6000);
    memset(executeOutput,0,1024);
    memset(scheduledOutput,0,1024); 
    memset(completedOutput,0,1024);


    for (int i = front; i <= rear && front == rear; i++) {
        char taskInfo[300];
        sprintf(taskInfo, "%d %s\n", taskQueue[i].id, taskQueue[i].command);
        if(taskQueue[i].status == 0){
            strcat(scheduledOutput, taskInfo);
        }
    }

    for(int i = 0; i < executed; i++){
        char taskInfo[300];
        if(executedArray[i].status==1){
            sprintf(taskInfo, "%d %s \n", executedArray[i].id, executedArray[i].command);
            strcat(executeOutput, taskInfo);
        }else{
            sprintf(taskInfo, "%d %s %ld ms\n", executedArray[i].id, executedArray[i].command, executedArray[i].elapsed_time);
            strcat(completedOutput, taskInfo);
        }
    }
    
    sprintf(statusOutput,"Executing \n%s\nScheduled \n%s\nCompleted\n%s",executeOutput,scheduledOutput,completedOutput);
    write(fc,statusOutput,strlen(statusOutput));
    close(fc);
    return 0;

}