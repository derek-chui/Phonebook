// Global Variables and Main

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "lab10.h"

//Global Variable
struct contact contacts[10];
struct contact* phonebook[3];

//Locks and Threads
pthread_mutex_t lock;
pthread_t autosaverThread;
pthread_t saveToFileThread;

void * autosaver_thread(void* arg)
{
	char* binaryFileName = (char*)arg;
	int key = *((int*)arg);
	while (1)
	{
		pthread_mutex_lock(&lock);
		save_to_file(binaryFileName, key);
		pthread_mutex_unlock(&lock);
		sleep(15);
	}
	return NULL;
}

void show_binary_file_contents(char* binaryFileName)
{
	pthread_mutex_lock(&lock);
	read_from_binary_file(binaryFileName);
	pthread_mutex_unlock(&lock);
}

//Main
int main (int argc, char *argv[])
{
	if (argc != 4)
	{
		printf ("missing arguments\n");
		return 1;
	}
	int key = atoi(argv[3]);

	if (key < 0 || key > 255)
	{
		printf("0 to 255 only");
		return 1;
	}
	pthread_mutex_init(&lock, NULL);
	if (pthread_create(&autosaverThread, NULL, autosaver_thread, (void*)argv[2]) != 0)
	{
		perror("pthread_create");
		return 1;
	}
	if (pthread_create(&saveToFileThread, NULL, save_to_file_thread, (void*)argv[2]) != 0)
	{
		perror("pthread_create");
		return 1;
	}
	if (pthread_create(&saveToFileThread, NULL, autosaver_thread, (void*)&key) != 0)
	{
		perror("pthread_create");
		return 1;
	}
	//Make phonebook NULL
	for (int i = 0; i < 3; i++)
	{
		phonebook[i] = NULL;
	}
	//Read from output if it exists
	read_from_file(argv[1], key);
	//Cases
	int option;
	while (1)
	{
		printf ("enter option\n");
		if (scanf ("%d", &option) != 1)
		{
			printf ("error\n");
			return 0;
		}
		switch (option)
		{
			case 1:
				read_from_keyboard();
				break;
			case 2:
				show_all();
				break;
            case 3:
            	show_name();
                break;
            case 4:
                delete();
                break;
            case 5:
                delete_name();
                break;
			case 6:
				show_binary_file_contents(argv[2]);
				break;
			case 0:
				if (pthread_cancel(autosaverThread) != 0)
				{
					perror("pthread_cancel");
					return 1;
				}
				if (pthread_cancel(saveToFileThread) != 0)
				{
					perror("pthread_cancel");
					return 1;
				}
				save_to_file(argv[1], key);
				delete_all();
				printf ("exit\n");
				return 0;
			default:
				printf ("wrong option\n");
		} 
	}
	if(pthread_join(autosaverThread, NULL) != 0)
	{
		perror("pthread_join");
		return 1;
	}
	if(pthread_join(saveToFileThread, NULL) != 0)
	{
		perror("pthread_join");
		return 1;
	}
	pthread_mutex_destroy(&lock);
	return 0;
}