// TO DO
#define FILENAME "file_pessoas"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>

typedef struct person{
	char* name[100];
	int age;
} Person;

int add_person(char* name, int age);

int list_persons(int nr);

int change_agev1(char* name, int newage);// TO DO