//Jeremy Chavez 1002264984

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
 
 
/* Node for storing information */
#define HASHTABLESIZE 30

typedef struct StarWars
{
    char *name;
    float height;
    char gender;
    char *affiliation;
    char *weapons;
    int movieEP;
    struct StarWars *next_ptr;

}
STARWARS;
 
/* This function creates an index corresponding to the input key */
int CalculateHashIndex(char *key)
{
	int HashIndex = 0;
	
	for (int i = 0; i < strlen(key); i++)
	{
		HashIndex += key[i];
	}
	
	return HashIndex %= HASHTABLESIZE; 
}

void AddNode(STARWARS *NewNode, STARWARS *Holocron[])
{
	int HashIndex = CalculateHashIndex(NewNode->name);
	
	/* a linked list does not exist for this cell of the array */
	if (Holocron[HashIndex] == NULL) 
	{
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
		Holocron[HashIndex] = NewNode;
	}
	else   /* A Linked List is present at given index of Hash Table */ 
	{
		STARWARS *TempPtr = Holocron[HashIndex];
	
		/* Traverse linked list */
		while (TempPtr->next_ptr != NULL) 
		{
			TempPtr = TempPtr->next_ptr;
		}
		TempPtr->next_ptr = NewNode;
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
	}
}

void FreeDynamicMemory(STARWARS *Holocron[])
{
	STARWARS *TempPtr = NULL, *NextPtr = NULL;
	
	for (int i = 0; i < HASHTABLESIZE; i++)
	{
		TempPtr = Holocron[i];
 
		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL) 
			{
				free(TempPtr->name);
				free(TempPtr->affiliation);
				free(TempPtr->weapons);
				NextPtr = TempPtr->next_ptr;
				free(TempPtr);
				TempPtr = NextPtr;
			}	
		}
	}
}


/* Remove an element from Hash Table */ 
int DeleteNode(STARWARS *Holocron[])
{
	char LookupName[256] = {0};
	int result = 0;
	
	printf("Enter the name of the Character to delete from the Holocron ");
	scanf("%s", LookupName);

	int HashIndex = CalculateHashIndex(LookupName);

	/* Get linked list at key in array */
    STARWARS *TempPtr = Holocron[HashIndex];
	STARWARS *PrevPtr = NULL;
 
	/* This array index does not have a linked list; therefore, no keys */
	if (TempPtr == NULL) 
	{
		printf("\n\nCharacter %s does not exist in the Holocron\n\n", LookupName);
		result = 0;
	}
	else 
	{
		while (TempPtr != NULL) 
		{
			if (strcmp(TempPtr->name, LookupName) == 0)
			{
				/* If the node being deleted is the head node */
				if (TempPtr == Holocron[HashIndex])
				{
					/* The node the head was pointing at is now the head */
					Holocron[HashIndex] = TempPtr->next_ptr;
					printf("\nCharcater %s has been deleted from the Holocron\n\n", TempPtr->name);
					free(TempPtr->name);
					free(TempPtr->affiliation);
					free(TempPtr->weapons);
					free(TempPtr);
					TempPtr = NULL;
				}
				/* Found node to be deleted - node is not the head */
				else
				{
					PrevPtr->next_ptr = TempPtr->next_ptr;
					printf("\nCharacter %s has been deleted from the Holocron\n\n", TempPtr->name);
					free(TempPtr->name);
					free(TempPtr->affiliation);
					free(TempPtr->weapons);
					free(TempPtr);
					TempPtr = NULL;
				}
				result = 1;
			}
			/* this is not the node that needs to be deleted but save */
			/* its info and move to the next node in the linked list  */
			else
			{
				PrevPtr = TempPtr;
				TempPtr = TempPtr->next_ptr;
			}
		}
		if (result == 0)
		{
			printf("\n\nCharacter %s does not exist in the Holocron\n\n", LookupName);
		}
	}
	return result;
}

/* display the contents of the Hash Table */
void DisplayHashTable(STARWARS *Holocron[])
{
	int i;
	STARWARS *TempPtr = NULL;
	
	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Holocron[i];

		printf("\nHolocron[%d]-", i);
		
		if (TempPtr != NULL) 
        {
			while (TempPtr != NULL)
			{
				printf("%s|", TempPtr->name);
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByLetter(STARWARS *Holocron[])
{
	int i;
	STARWARS *TempPtr = NULL;
	char LookupLetter = 'A';

	printf("\n\nEnter a letter of the alphabet ");
	scanf(" %c", &LookupLetter);
	LookupLetter = toupper(LookupLetter);

	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Holocron[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (toupper(TempPtr->name[0]) == LookupLetter)
				{
					printf("%s\n", TempPtr->name);
				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByName(STARWARS *Holocron[])
{
	STARWARS *TempPtr = NULL;
	char LookupName[100] = {0};
	int FoundIt = 0;

    int ch; 
    
    while ((ch = getchar()) != '\n' && ch != EOF) {}
	
	printf("\n\nEnter Characters name: ");
    if (fgets(LookupName, sizeof(LookupName), stdin));
    size_t n = strlen(LookupName);
    if (n && LookupName[n-1] == '\n') LookupName[n-1] = '\0';
	
	#if TIMING
	clock_t start, end;
	start = clock();
	#endif
	for (int i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Holocron[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (strcmp(TempPtr->name, LookupName) == 0)
				{
					#if TIMING
					end = clock();
					printf("\n\nSearch took %ld tics\n\n", end-start);
					#endif

					FoundIt = 1;
					printf("\n\n%s\n", TempPtr->name);
					
					
					if (TempPtr->gender == 'B')
						printf("Gender\t\tM F\n");
					else if (TempPtr->gender == 'U')
						printf("Genger\t\tUnknown\n");
					else
						printf("Gender\t\t%c\n", TempPtr->gender);
					printf("Affiliation\t%s\n", TempPtr->affiliation);
					printf("Weapon\t%s\n", TempPtr->weapons);
					printf("Movie apperance #\t%d\n", TempPtr->movieEP);

				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
	
	if (FoundIt == 0)
		printf("\n\nCharacter %s not found in Holocron\n\n", LookupName);
}

void AddNewCharacter(STARWARS *Holocron[])
{
	int HashIndex = 0;
	STARWARS *NewNode;
	char TempBuffer[100] = {0};

	NewNode = malloc(sizeof(STARWARS));
	NewNode->next_ptr = NULL;

	printf("\n\nEnter new Starwars character name ");
	scanf("%s", TempBuffer);
	NewNode->name = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->name, TempBuffer);

	printf("\n\nEnter %s's height as cm ", NewNode->name);
	scanf("%f", &(NewNode->height));
	
	
	printf("\n\nEnter %s's possible gender (M/F/D) ", NewNode->name);
	scanf(" %c", &(NewNode->gender));
	NewNode->gender = toupper(NewNode->gender);
	
	// Extra fgets to clear stdin
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
	
	printf("\n\nEnter %s's affiliation ", NewNode->name);
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin); 
	TempBuffer[strlen(TempBuffer)-1] = '\0';
	NewNode->affiliation = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->affiliation, TempBuffer);

	printf("\n\nEnter %s's weapon of choice ", NewNode->name);
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
	TempBuffer[strlen(TempBuffer)-1] = '\0';	
	NewNode->weapons = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->weapons, TempBuffer);


	printf("\n\nEnter %s's movie episode ", NewNode->name);
	scanf("%d", &(NewNode->movieEP));

	AddNode(NewNode, Holocron);
}

int ReadFileIntoHashTable(int argc, char *argv[], STARWARS *Holocron[])
{
	FILE *FH = NULL;
	char FileLine[1024] = {0};
	char *token = NULL;
	int counter = 0;
	int HashIndex = 0;
	STARWARS *NewNode;

	if (argc > 1)
	{
		FH = fopen(argv[1], "r");

		if (FH == NULL)
		{
			perror("Exiting ");
			exit(0);

		}
        
        
        while (fgets(FileLine, sizeof(FileLine)-1, FH))
		{
            size_t len = strlen(FileLine);
            while (len && (FileLine[len-1] == '\n' || FileLine[len-1] == '\r'))
            {
                FileLine[--len] = '\0';
            }
            if (len != 0) 
            {
                char *t_name = strtok(FileLine, "|");
                char *t_height = NULL;
                char *t_gender = NULL;
                char *t_aff = NULL;
                char *t_weaps = NULL;
                char *t_movie = NULL;

                if (t_name != NULL)
                {
                    t_height = strtok(NULL, "|");
                    t_gender = strtok(NULL, "|");
                    t_aff = strtok(NULL, "|");
                    t_weaps = strtok(NULL, "|");
                    t_movie = strtok(NULL, "|");

                }

                if (t_name != NULL && t_height != NULL && t_movie != NULL)
                {
                    STARWARS *NewNode = (STARWARS*)malloc(sizeof(STARWARS));
                  
                
                    NewNode-> next_ptr = NULL;

                    NewNode->name = (char*)malloc(strlen(t_name) + 1);
                    strcpy(NewNode->name, t_name);

                    NewNode->height = (float)atof(t_height);
                    NewNode->gender = (t_gender && t_gender[0]) ? (char)toupper((unsigned char)t_gender[0]) : 'U';

                    if (t_aff == NULL) t_aff = "";
                    NewNode->affiliation = (char*)malloc(strlen(t_aff) + 1);
                    strcpy(NewNode->affiliation, t_aff);

                    if (t_weaps == NULL) t_weaps = "";
                    NewNode->weapons = (char*)malloc(strlen(t_weaps) + 1);
                    strcpy(NewNode->weapons, t_weaps);

                    NewNode->movieEP = atoi(t_movie);

                    AddNode(NewNode, Holocron);
                    counter++;
                }





            }

        }
    }
    else
    {
        printf("File must be provided on command line...exiting\n");
		exit(0);
    }
	
	fclose(FH);
	
	return counter;
}

int main(int argc, char *argv[]) 
{
	int MenuChoice = 0;
	int counter = 0;
	STARWARS *Holocron[HASHTABLESIZE] = {0};

	enum Menu {SHOWBYLETTER=1, SHOWBYNAME, COUNT, DISPLAY, ADD, DELETE, EXIT};
 
	counter = ReadFileIntoHashTable(argc, argv, Holocron);
 
	do
	{
		printf("\n\nStar Wars Holocron Menu\n\n"
			   "1. Show all Characters in Holocron for a given letter\n"
			   "2. Look up Characters by name\n"
			   "3. How many Characters are in the Holocron?\n"
			   "4. Display the Holocron\n"
			   "5. Add a new Character\n"
			   "6. Delete a Character from the Holocron\n"
			   "7. Exit\n\n"
			   "Enter menu choice ");
	
		scanf("%d", &MenuChoice);
		printf("\n\n");

		switch (MenuChoice)
		{	
			case SHOWBYLETTER:
				ShowByLetter(Holocron);
				break;
			case SHOWBYNAME:
				ShowByName(Holocron);
				break;
			case COUNT:
				printf("Your Holocron contains %d Characters\n", counter); 
				break;
 			case DISPLAY:
				DisplayHashTable(Holocron);
				break;
			case ADD:
				AddNewCharacter(Holocron);
				counter++;
				break;
			case DELETE:
				if (DeleteNode(Holocron))
				{
					counter--;
				}
				break;
			case EXIT:
				break;
			default : 
				printf("Invalid menu choice\n\n"); 
		}
	}
	while (MenuChoice != EXIT);
	
	FreeDynamicMemory(Holocron);

	return 0;
}
