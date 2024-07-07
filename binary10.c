//Threads and Functions to Read and Save to Binary File

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "lab10.h"

//Thread
extern pthread_mutex_t lock;
pthread_t saveToFileThread;

//Save to Binary File Using Threads
void* save_to_file_thread(void* arg)
{
    char* binaryFileName = (char*)arg;
    while (1)
    {
        pthread_mutex_lock(&lock);
        FILE* file = fopen(binaryFileName, "wb");
        if (file == NULL)
        {
            perror("Error opening file");
            pthread_mutex_unlock(&lock);
            return NULL;
        }
        for (int i = 0; i < 3; i++)
        {
            struct contact* p = phonebook[i];
            while (p != NULL)
            {
                fwrite(p, sizeof(struct contact), 1, file);
                p = p->next;
            }
        }
        fclose(file);
        pthread_mutex_unlock(&lock);
        sleep(15);
    }
    return NULL;
}

//Read from Binary File
void read_from_binary_file(char fileName[])
{
    FILE* file = fopen(fileName, "rb");
    if (file == NULL)
    {
        perror("Error");
        return;
    }
    struct contact tempContact;
    while (fread(&tempContact, sizeof(struct contact), 1, file) == 1)
    {
        printf("%s %s %s %d", tempContact.firstName, tempContact.lastName, tempContact.phoneNumber, tempContact.infoFlag);
        if(tempContact.infoFlag == 0)
        {
            printf(" %d/%d\n", tempContact.options.bday[0], tempContact.options.bday[1]);
        }
        else if (tempContact.infoFlag == 1)
        {
            printf(" %s\n", tempContact.options.ophone);
        }
        else
        {
            printf("\n");
        }
    }
    fclose(file);
}