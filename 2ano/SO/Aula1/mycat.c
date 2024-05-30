#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

// cat
int mycat(){

    char *buffer[BUFFER_SIZE];
        ssize_t res_read;
        //stdout 0
        while((res_read = read(0, buffer,BUFFER_SIZE))>0){
            //stdin 1     
            ssize_t res_write =  write(1, buffer,res_read);       
            if(res_read != res_write) return 1;

        }
        //stderr 2
        write(2,"bye\n",5);


    return 0;
}


int main(int argc, char const *argv[])
{
    
    mycat();
    return 0;
}





