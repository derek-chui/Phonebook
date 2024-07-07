//Functions

//Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "lab10.h"

//Main
int main (int argc, char *argv[]);

//HELPER FUNCTION
//Checks for Duplicates given First Name and Last Name
int check_duplicate (char fName[], char LName[])
{
    for (int i = 0; i < 3; i++)
    {
        struct contact *p = phonebook[i];
        
        while (p != NULL)
        {
            if (strcmp(fName, p->firstName) == 0 && strcmp(LName, p->lastName) == 0)
            {
                return 1;
            }
            p = p->next;
        }
    }
    return 0;
}

//HELPER FUNCTION
//Find Index According to Last Name
int find_index(char *lastName)
{
    char firstLetter = lastName[0];
    if (firstLetter <= 'k')
    {
        return 0;
    }
    else if (firstLetter < 'r')
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

//User Input Contact
void read_from_keyboard ()
{

    //declare variables
    char tempFName[11];
    char tempLName[11];
    char tempNumber[11];
    int tempBDayM;
    int tempBDayD;
    char tempOphone[20];
    int tempInfoFlag;

    // make new node to contain information of person
    struct contact* newNode = (struct contact*)malloc(sizeof(struct contact));

    // user input for names
    printf ("Enter your first name:\n");
    scanf ("%s", tempFName);

    printf ("Enter your last name:\n");
    scanf ("%s", tempLName);
    
	printf ("Enter your phone number:\n");
	scanf ("%s", tempNumber);

	strcpy (newNode->phoneNumber, tempNumber);

    printf ("Enter extra info flag:\n");
    scanf ("%d", &tempInfoFlag);

    switch (tempInfoFlag)
    {
        case 0:
            newNode->infoFlag = 0;
            printf ("Enter Birthday Month:\n");
            scanf ("%d", &tempBDayM);
            printf ("Enter Birthday Day:\n");
            scanf ("%d", &tempBDayD);
            break;

        case 1:
            newNode->infoFlag = 1;
            printf ("Enter Other Phone:\n");
            scanf ("%s", tempOphone);
            break;

        case 2:
            newNode->infoFlag = 2;
            break;

		default:
            printf ("wrong option\n");
            break;
    }

    strcpy (newNode->firstName, tempFName);
    strcpy (newNode->lastName, tempLName);
    strcpy (newNode->phoneNumber, tempNumber);
    if (tempInfoFlag == 0 || tempInfoFlag == 1 || tempInfoFlag == 2)
    {
        newNode->infoFlag = tempInfoFlag;

        if (newNode->infoFlag == 0)
        {
            newNode->options.bday[0] = tempBDayD;
            newNode->options.bday[1] = tempBDayM;
        }
        else if (newNode->infoFlag == 1)
        {
            strcpy (newNode->options.ophone, tempOphone);
        }
    }

    char firstLetter = newNode->lastName[0];
    int index;
    if (firstLetter <= 'k')
    {
        index = 0;
    }
    else if (firstLetter < 'r')
    {
        index = 1;
    }
    else
    {
        index = 2;
    }

    insert(newNode, find_index(newNode->lastName));
}

//Inserts Node to Linked List given newNode and Index
void insert(struct contact* newNode, int index)
{

    // pointers to move nodes around
    struct contact* current = phonebook[index];
    struct contact* prev = NULL;
    struct contact* traverse = NULL;

    // checks if name is a duplicate
    if (check_duplicate (newNode->firstName, newNode->lastName) == 1)
    {
        printf ("Duplicate name\n");
        return;
    }

    // place node in alphabetical order (last name, if last name is the same then first name)

    // if there isn't anything
    if (phonebook[index] == NULL)
    {
        newNode->next = NULL;
        phonebook[index] = newNode;
        return;
    }
    //add before phonebook[i]
    if (strcmp(phonebook[index]->lastName, newNode->lastName) > 0 || (strcmp(phonebook[index]->lastName, newNode->lastName) == 0 && strcmp(phonebook[index]->firstName, newNode->firstName) > 0))
    {
        newNode->next = phonebook[index];
        phonebook[index] = newNode;
        return;
    }

    current = phonebook[index];
    prev = phonebook[index];
    traverse = phonebook[index];

    //everything else
    while (traverse != NULL && (strcmp(newNode->lastName, traverse->lastName) > 0 || (strcmp(newNode->lastName, traverse->lastName) == 0 && strcmp(newNode->firstName, traverse->firstName) > 0)))
    {
        prev = traverse;
        traverse = traverse->next;
    }
    prev->next = newNode;
    newNode->next = traverse;
}

//HELPER FUNCTION
//Prints Contact given Node
void printContact(struct contact *p)
{
    printf("%s %s, %s", p->firstName, p->lastName, p->phoneNumber);
    if (p->infoFlag == 0)
    {
        if (p->options.bday > 0)
        {
            printf (", %d/%d", p->options.bday[0], p->options.bday[1]); 
        }
    }
    else if (p->infoFlag == 1)
    {
        printf (", %s", p->options.ophone);
    }
    printf ("\n");
}

//Shows Everything
void show_all ()
{
    int i;
    for (int i = 0; i < 3; i++)
    {
        struct contact* p = phonebook[i];
        while (p != NULL)
        {
            printContact(p);
            p = p->next;
        }
    }
}

//Shows Everyone with Given Last Name
void show_name ()
{
	char tName[11];
	
	printf ("Enter last name:\n");
	scanf ("%s", tName);

    int index = find_index(tName);
    struct contact *p = phonebook[index];
    int found = 0;

    while (p != NULL)
    {
        if (strcmp(tName, p->lastName) == 0)
        {
            printContact(p);
            found++;
        }
        p = p->next;
    }

    if (found == 0)
	{
        printf("%s not found\n", tName);
    }
}

//Delete Specific Contact
void delete ()
{
    char tFName[11];
    char tLName[11];

    printf("First Name to delete:\n");
    scanf ("%s", tFName);

    printf("Last Name to delete:\n");
    scanf ("%s", tLName);

    int index = find_index(tLName);
    struct contact* p = phonebook[index];
    struct contact* prev = NULL;

    //empty
    if (p == NULL)
    {
        printf("Nothing to Delete\n");
        return;
    }

    //only one
    if (phonebook[index]->next == NULL)
    {
        if (strcmp(tFName, p->firstName) == 0 && strcmp(tLName, p->lastName) == 0)
        {
            free(phonebook[index]);
            phonebook[index] = NULL;
            return;
        }
        printf("Nothing to Delete\n");
        return;
    }

    //everything else
    while (p != NULL)
    {
        if (strcmp(tFName, p->firstName) == 0 && strcmp(tLName, p->lastName) == 0)
        {
            // if first with others after
            if (p == phonebook[index])
            {
                struct contact* temp = phonebook[index];
                phonebook[index] = phonebook[index]->next;
                free(temp);
                return;
            }
            prev->next = p->next;
            free(p);
            p = prev;
        }
        prev = p;
        p = p->next;
    }
}

//Delete Everyone with Given Name
void delete_name ()
{
    char tName[11];
    
    printf("Name to Delete:\n");
    scanf ("%s", tName);

    int index = find_index(tName);
    struct contact* p = phonebook[index];
    struct contact* prev = NULL;

    if (phonebook[index] == NULL)
    {
        printf("Nothing to Delete\n");
        return;
    }

    if (phonebook[index]->next == NULL)
    {
        if (strcmp(tName, p->firstName) == 0)
        {
            free(phonebook[index]);
            phonebook[index] = NULL;
            return;
        }
        printf("Nothing to Delete\n");
        return;
    }

    while (p != NULL)
    {
        if (strcmp(tName, p->firstName) == 0)
        {
            if (p == phonebook[index])
            {
                struct contact* temp = phonebook[index];
                phonebook[index] = phonebook[index]->next;
                p = p->next;
                free(temp);
            }
            else
            {
                prev->next = p->next;
                free(p);
                p = prev;
                p = p->next;
            }
        }
        else
        {
            prev = p;
            p = p->next;
        }
    }
}

//HELPER FUNCTION
//Deletes Everything Recursively
void delete_all_recursive(struct contact *current)
{
    if (current == NULL)
    {
        return;
    }
    struct contact *temp = current;
    current = current->next;
    free(temp);
    delete_all_recursive(current);
}

//Initiates delete_all_recursive
void delete_all()
{
    int i;
    for (i = 0; i < 3; i++)
    {
        delete_all_recursive(phonebook[i]);
        phonebook[i] = NULL;
    }
}