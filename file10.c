//Functions to Read and Save to Files

//Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "lab10.h"

//Reads from given File
void read_from_file(char fileName[], int key)
{
    //Open file in Reading Mode
    FILE* file = fopen(fileName, "r");
    if (file == NULL)
    {
        perror("Error");
        return;
    }

    char line[500];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        struct contact *newNode = (struct contact*)malloc(sizeof(struct contact));
        for (int i = 0; i < strlen(line); i++)
        {
            line[i] = line[i] ^ key;
        }
        strcpy(newNode->firstName, strtok(line, " "));
        strcpy(newNode->lastName, strtok(NULL, " "));
        strcpy(newNode->phoneNumber, strtok(NULL, " "));
        newNode->infoFlag = atoi(strtok(NULL, " "));
        if (newNode->infoFlag == 0)
        {
            newNode->options.bday[0] = atoi(strtok(NULL, " "));
            newNode->options.bday[1] = atoi(strtok(NULL, " "));
        }
        else if (newNode->infoFlag == 1)
        {
            strcpy(newNode->options.ophone, strtok(NULL, " "));
        }
        newNode->next = NULL;
        insert(newNode, find_index(newNode->lastName));
    }
    fclose(file);
}

//Saves from Linked List
void save_to_file(char fileName[], int key)
{
    //Make New File called "output" in Write Mode
    FILE* file = fopen(fileName, "w");
    if (file == NULL)
    {
        perror("Error");
        return;
    }

    char buffer[500];
    //Look through all three phonebook index
    for (int i = 0; i < 3; i++)
    {
        struct contact* p = phonebook[i];
        //Looks through all nodes in index
        while (p != NULL)
        {
            // fprintf(file, "%s %s %s %d", p->firstName, p->lastName, p->phoneNumber, p->infoFlag);
            if (p->infoFlag == 0)
            {
                sprintf(buffer, "%s %s %s %d %d %d", p->firstName, p->lastName, p->phoneNumber, p->infoFlag, p->options.bday[0], p->options.bday[1]);
                for (int i = 0; i < strlen(buffer); i++)
                {
                    buffer[i] = buffer[i] ^ key;
                }
                fprintf(file, "%s\n", buffer);
            }
            else if (p->infoFlag == 1)
            {
                sprintf(buffer, "%s %s %s %d %s", p->firstName, p->lastName, p->phoneNumber, p->infoFlag, p->options.ophone);
                for (int i = 0; i < strlen(buffer); i++)
                {
                    buffer[i] = buffer[i] ^ key;
                }
                fprintf(file, " %s\n", buffer);
            }
            else
            {
                sprintf(buffer, "%s %s %s", p->firstName, p->lastName, p->phoneNumber);
                for (int i = 0; i < strlen(buffer); i++)
                {
                    buffer[i] = buffer[i] ^ key;
                }
                fprintf(file, " %s\n", buffer);
            }
            struct contact* temp = p;
            p = p->next;
        }
    }
    fclose(file);
}


    // //Temp Variables
    // char tempFName[11];
    // char tempLName[11];
    // char tempNumber[11];
    // int tempInfoFlag;
    // int tempBDayD;
    // int tempBDayM;
    // char tempOphone[20];

    // //Copies Files to newNode
    // while (fscanf(file, "%s %s %s %d", tempFName, tempLName, tempNumber, &tempInfoFlag) != EOF)
    // {
    //     //First Name, Last Name, Phone Number, etc.
    //     struct contact* newNode = (struct contact*)malloc(sizeof(struct contact));
    //     strcpy(newNode->firstName, tempFName);
    //     strcpy(newNode->lastName, tempLName);
    //     strcpy(newNode->phoneNumber, tempNumber);
    //     newNode->infoFlag = tempInfoFlag;
    //     if (tempInfoFlag == 0)
    //     {
    //         fscanf(file, "%d/%d", &tempBDayD, &tempBDayM);
    //         newNode->options.bday[0] = tempBDayD;
    //         newNode->options.bday[1] = tempBDayM;
    //     }
    //     else if (tempInfoFlag == 1)
    //     {
    //         fscanf(file, "%s", tempOphone);
    //         strcpy(newNode->options.ophone, tempOphone);
    //     }
        // char *token = strtok(line, " ");
        // char decFN[12], decLN[12], decPN[12], decOP[21];
        // xorDecrypt(token, decFN, key);
        // token = strtok(NULL, " ");
        // xorDecrypt(token, decLN, key);
        // token = strtok(NULL, " ");
        // xorDecrypt(token, decPN, key);
        // token = strtok(NULL, " ");
        // xorDecrypt(token, decOP, key);
        // struct contact *newNode = (struct contact*)malloc(sizeof(struct contact));
        // strcpy(newNode->firstName, decFN);
        // strcpy(newNode->lastName, decLN);
        // strcpy(newNode->phoneNumber, decPN);
        // token = strtok(NULL, " ");
        // newNode->infoFlag = atoi(token);
        // if (newNode->infoFlag == 0)
        // {
        //     fscanf(file, "%d/%d", &newNode->options.bday[0], &newNode->options.bday[1]);
        // }
        // else if (newNode->infoFlag == 1)
        // {
        //     fscanf(file, "%s", newNode->options.ophone);
        // }