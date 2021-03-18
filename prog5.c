/*
NAME Sarah Anderson (SCA2)
CLASS ECE 2220.001
PROJECT Strings-Editor Functions
PURPOSE The purpose of this file is to make sure everything in the inout file is spelled correctly and if it is not in the dictionary ask if they want to add it to there personal ictionary or replace the word with another word. Also, to search and replace certain words within the input file and save it into an output file.
ASSUMPTIONS Assuming that the user knows how to run a program and how to read. Known bugs as of 4/5/2019, the spellCheck function will say that moe things are not in the dictionary or spelled incorreclty. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define MAX 1000000

struct TData{
	char **pChar;
};

//Function that inputs the data from the command line arguments (for input file and dictionary file)
int inputData (const char *input, const char *dict, struct TData *pInput, struct TData *pDictionary);
//Checks the spelling of the words in the input file
int checkSpelling(struct TData *pInput, struct TData *pDictionary);
//Searches for a certain string that a user inputs and if it si found t asks to see if the user wants to repalce it
int searchReplace(const char *input, const char *dict, struct TData *pInput, struct TData *pDictionary);
//Saves the output to the output file
int save(const char *input, const char *output, struct TData *pInput);
//replaces the old word with the new one inputed
void combineText(char *wordtoreplace, char *replacementword, char *tempstring2);

int main (int argc, char **argv){
	struct TData input, dictionary;
	int choice = 0;

	if(argc != 4){
		printf("Not enough input arguments in the command line.\n");
		exit(1);
	}
	//inputs the data into the struct
	printf("This may take a few seconds...\n");
	inputData(argv[1], argv[3], &input, &dictionary);

	do{
		printf("Menu\n");
		printf("1. Check the spelling for the file using the dictionary.\n");
		printf("2. Search and replace a given string in the inputed file.\n");
		printf("3. Save the modified file to the output file.\n");
		printf("4. Exit the program.\n");
		scanf("%d", &choice);

		switch(choice){
			case 1: 
				//Checks the spelling of the input file
				checkSpelling(&input, &dictionary);
				break;
			case 2:
				//Searches and replaces certain words within the input file
				searchReplace(argv[1], argv[3], &input, &dictionary);
				break;
			case 3:
				//Saves the edits to an output file
				save(argv[1], argv[2], &input);
				break;
			case 4:
				//exits the menu and program
				choice = 4;
				break;
			default: 
				printf("Input is invalid");
				break;
		}
	}while (choice != 4);
return 0;
}

//Inputs the data from the input files into the structs (for both the dictionary and the input file)
int inputData(const char *input, const char *dicto, struct TData *pInput, struct TData *pDictionary){

	FILE *inputFile;
	FILE *dictFile;
	int charCount = 400, rowCount = 50000, dictChar = 25, i = 0, j = 0;

        printf("Opening the inputed file...\n");
        if((inputFile = fopen(input, "rt")) == NULL){
                printf("Cannot open file\n");
                exit(1);
        }

        printf("Opening the dictionary...\n");
        if((dictFile = fopen(dicto, "rt")) == NULL){
                printf("Cannot open dictionary\n");
                exit(1);
        }

	//Allocating enough space for the rows and characters in each line (must use two malloc statements)
        pInput->pChar = (char **)malloc((rowCount + 1) * sizeof(char *));
        for(i = 0; i < rowCount; i++){
                pInput->pChar[i] = (char *)malloc(charCount * sizeof(char));
        }

	//Inputing the input file into the struct so that it is much easier to use later
        i = 0, j = 0;
        for(i = 0; i < rowCount; i++){
                for(j = 0; j < charCount; j++){
                        fscanf(inputFile, "%c", &pInput->pChar[i][j]);
                }
//                printf("%s", pInput->pChar[i]);
        }

        j = 0, i = 0;
        //Reading in the dictionary file line by line using dynamic memory allocation
        pDictionary->pChar = (char **)malloc((rowCount + 1) * sizeof(char *));
        for(i = 0; i < rowCount; i++){
                pDictionary->pChar[i] = (char *)malloc(dictChar * sizeof(char));
        }

	//Inputs the data into the struct for the dictionary
        i = 0;
        for(i = 0; i < rowCount; i++){
                for(j = 0; j < dictChar; j++){
                      fscanf(dictFile, "%c", &pDictionary->pChar[i][j]);
                }
//              printf("%s", pDictionary->pChar[i]);
        }

	//Closes both files
        fclose(inputFile);
        fclose(dictFile);

return 0;
}

//Checks the spelling of the input file against the dictionary file
int checkSpelling(struct TData *pInput, struct TData *pDictionary){

	FILE *userdictionary;
	FILE *writetouserdict;
	int i = 0, j = 0, k = 0, l = 0, wordCheck = 0, userselect = 0, userdictexists = 0, replaced = 0, selectc = 0;
	char templine[2000], templine2[2000], word[50], tempword[50], userdictword[50], userdictname[50];
	int rowCount = 50000;

        for(i = 0; i < rowCount; i++){
		printf("The inital string is: %s\n", pInput->pChar[i]);
		j = 0;
		replaced = 0;
		//Clears out templine and templine2
		memset(templine, 0, strlen(templine));
		memset(templine2, 0, strlen(templine2));
		//Copies in the first row from the input array that is dynamically stored
		strcpy(templine2, pInput->pChar[i]);
		
		//Does this while loop until the character equals a newline or null or EOF
		while(pInput->pChar[i][j] != '\n' && pInput->pChar[i][j] != '\0' && pInput->pChar[i][j] != EOF){
			k = 0;
			//Clears out arrays word and tempword
			memset(word, 0, strlen(word));
			memset(tempword, 0, strlen(tempword));
			//Does this loop while the character is equal to the ASCII of any lower or upper case letter
			while((pInput->pChar[i][j] > 96 && pInput->pChar[i][j] < 123) || (pInput->pChar[i][j] > 64 && pInput->pChar[i][j] < 91)){
				//Stores the pulled out word in word and converts it to lower case
				word[k] = pInput->pChar[i][j];
			//	printf("The value of k is %d\n", k);
				j++;
				k++;
			}
//			printf("The word you are comparing is: %s\n", word);
			j++;
			//Checks to make sure that there is information in the array called word
			if(strlen(word) > 1){
				wordCheck = 0;
				for(l = 0; l < rowCount; l++){
		//			printf("The string you are comparing the word to is %s\n", pDictionary->pChar[l]);
					//Compares the word pulled out of the input file to the word extracted from dictionary
					if(!strncmp(word, pDictionary->pChar[l], strlen(word))){
						wordCheck = 1;
					}
				}
				//If the user selects to add the word to the personal dictionary it does this
				if(userdictexists == 1){
					//Opens up a file such that it is created/saved
					userdictionary = fopen(userdictname, "r");
					
					while(!feof(userdictionary)){
						//brings one line out of the user dictionary to make sure it is in there and if it isnt then it adds it 
						fscanf(userdictionary, " %s", userdictword);
						if(!strcmp(word, userdictword)){
							wordCheck = 1;
						}
					}
					fclose(userdictionary);
				}
				//word not found in the dicitonary or the user dictionary
				if(wordCheck == 0){
					printf("\n%s isnt in the dictionary\n", word);
					selectc = 0;
					do{
						if(selectc > 0){
							printf("Not a valid selection\n");
						}
						//User selection to see what they want to do
						printf("Do you wish to: \n1. Replace the word \n2. Add word to personal dictionary\n");
						//takes in the user selection
						scanf("%d", &userselect);
						selectc++;
					}while(userselect != 1 && userselect != 2); //make sure the selection is a 1 or 2
					//if statement if the user selects to replace the extracted word
					if(userselect == 1){
						replaced = 1;
						//Gets the word that you want to replace the extracted word with
						printf("\nEnter the word you want to replace the miss spelled word with: ");
						scanf(" %s", tempword);					
						//Function that takes out the old word and prints in the new word ***SEG FAULT
						combineText(word, tempword, templine2);
					}
		
					//This part only goes one time during the selection. Allows the user to create the file name of the personal dict
					if(userselect == 2){
						if(userdictexists == 0){
							printf("Enter the name for your personal dictionary without the .txt: ");
							scanf(" %s", userdictname);
							userdictexists = 1;
							//adds on the .txt to the end of the personal dictionary name inputed
							strcat(userdictname, ".txt");
							//Opens the personal dictionary such that the file is created
							userdictionary = fopen(userdictname, "w");
							fclose(userdictionary);
						}
						//Writes the data to the user's personal dictionary (and appends to the end of the file)
						writetouserdict = fopen(userdictname, "a+");
						fprintf(writetouserdict, "%s\n", word);
						fclose(writetouserdict);
					}
				}
			}
		}
		if(replaced){
			//clears out the row in RAM so that it can be rewritten back
			memset(pInput->pChar[i], 0, strlen(pInput->pChar[i]));
			//Copies in the string from templine2 string to the input array
			strcpy(pInput->pChar[i], templine2);
			memset(templine2, 0, strlen(templine2));
		}
//		printf("Final string is: \n\n%s\n\n", pInput->pChar[i]);
	
	}
			
	printf("\n");
return 0;
}

void combineText(char *wordtoreplace, char *replaceword, char *tempstring2){
	char *ptr, tempstring3[2000], tempstring[2000];
	int i = 0, j = 0;
	
	//clears out the tempstring
	memset(tempstring, 0, strlen(tempstring));
	memset(tempstring3, 0, strlen(tempstring3));
	//Finds where the word to replace is in the inital string
	ptr = strstr(tempstring2, wordtoreplace);
	//Copies in tempstring2 into tempstring2 into tempstring but only for a certain number of spaces
	strncpy(tempstring, tempstring2, (ptr - tempstring2));
	//copies the word that is replacing the other word into tempstring
 	strcat(tempstring, replaceword);
	i = ptr - tempstring2 + strlen(wordtoreplace);
//	printf("i is %d\n", i);
	j = 0;
	//puts the rest of the input line into a temp such that it can be added on to the end of the string
	for(i = i; i < 2000; i++){
		tempstring3[j] = tempstring2[i];
		j++;
	}
//	printf("Tempstring3 is %s\n", tempstring3);
	strcat(tempstring, tempstring3);
	//Copies the file over to tempstring2 because that is the thing that is used in the save function
	memset(tempstring2, 0, strlen(tempstring2));
	strcpy(tempstring2, tempstring);
	//Check to make sure that the function preformed properly
	printf("String after implementing the new word is: \n%s\n", tempstring2);
}

//This function has a user input a word and it searches for that word in the file input
int searchReplace(const char *input, const char *dict, struct TData *pInput, struct TData *pDictionary){
	FILE *inputFile;
	int j = 0, i = 0, k = 0, userselect = 0, replaced = 0, goon = 0;
	char wordSearch[25], word[25], tempword[25], templine[1500], templine2[150];
	int rowCount = 5000;

	printf("Enter the word that you want to search for...");
	scanf(" %s", wordSearch);

	if((inputFile = fopen(input, "rt")) == NULL){
		printf("Unable to open input file\n");
	}

	i = 0;
	//Does it for each line of the input file
	for(i = 0; i < rowCount; i++){
		j = 0;
		replaced = 0;
		//Clears out templine and templine2
		memset(templine, 0, strlen(templine));
		memset(templine2, 0, strlen(templine2));
		//Copies the first line from the struct to a templine2
		strcpy(templine2, pInput->pChar[i]);
		
		//Checks to make sure that it is not a new line character or the end of the file
		while(pInput->pChar[i][j] != '\n' && pInput->pChar[i][j] != '\0' && pInput->pChar[i][j] != EOF){
			k = 0;
			memset(tempword, 0, strlen(tempword));
			memset(word, 0, strlen(word));
			//Gets one word at a time, checks to make sure that the character is between the ASCII value
			while((pInput->pChar[i][j] > 96 && pInput->pChar[i][j] < 123) || (pInput->pChar[i][j] > 64 && pInput->pChar[i][j] < 91)){
				word[k] = pInput->pChar[i][j];
				k++;
				j++;
			}
			j++;
			goon = 0;
			//Comapres the word inputed and the word extracted and if they are the same then it moves on
			if(!strcmp(word, wordSearch)){
				goon = 1;
				if(goon == 1){
					printf("%s was found at line %d\n", wordSearch, (i + 1));
					printf("Would you like to replace it?\n1. Yes\n2. No\n");
					scanf(" %d", &userselect);
					if(userselect == 1){
						replaced = 1;
						printf("What would you like to replace %s with?\n", word);
						scanf(" %s", tempword);
						//replaces the old word with the new pne that was inputed 
						combineText(word, tempword, templine2);
					}
				}
			}	
			if(replaced){
				//Clears the old line and replaces it with the new line that was edited 
				memset(pInput->pChar[i], 0, strlen(pInput->pChar[i]));
				strcpy(pInput->pChar[i], templine2);
			}
		}
					
	}	
	
return 0;
}

//Moves the data from the input file into the output file and saves it
int save(const char *input, const char *output, struct TData *pInput){
	FILE *outputFile;
	int i = 0, rowCount = 5000;

	if((outputFile = fopen(output, "w"))== NULL){
		printf("Unable to open output file.\n");
		exit(1);
	}

	printf("Moving data from input to an output file\n");

	//For each line in the inputfile, print it into the output file
	for(i = 0; i < rowCount; i++){
		fprintf(outputFile, "%s\n", pInput->pChar[i]);
	}

	//Close the output file
	fclose (outputFile);
	printf("Done\n");
return 0;
}
