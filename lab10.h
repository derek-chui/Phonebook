//Library for All Unions, Structs, and Function

#ifndef LAB10_H
#define LAB10_H

//Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//Unions and Structs
union info
{
    int bday[2];
    char ophone[20];
};

struct contact
{
    char firstName[11];
    char lastName[11];
    char phoneNumber[11];
    int infoFlag;
    union info options;

    struct contact* next;
};

extern struct contact* phonebook[3];
extern pthread_mutex_t lock;

//Functions

//main10.c
void * autosaver_thread(void* arg);
void show_binary_file_contents(char* binaryFileName);
int main (int argc, char *argv[]);

//list10.c
int check_duplicate (char fName[], char LName[]); //HELPER
int find_index(char *lastName); //HELPER
void read_from_keyboard(); //1
void insert (struct contact *newNode, int index); //1
void printContact(struct contact *p); //HELPER
void show_all (); //2
void show_name (); //3
void delete (); //4
void delete_name (); //5
void delete_all_recursive(struct contact *current); //HELPER
void delete_all (); //0

//file10.c
void read_from_file(char fileName[], int key);
void save_to_file(char fileName[], int key);

//binary10.c
void* save_to_file_thread(void* arg);
void read_from_binary_file(char fileName[]);

/*
To Do List:
- Figure out why output & output.bin resets every time you run
*/

#endif