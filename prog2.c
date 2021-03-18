//Sarah Anderson (CU username: Sca2)
//ECE 2220.001
//Project 2: Data Types 
//Purpose: The purpose of this program is to input various things about a politician and print them out.
//Assumptions: An assumption to be made when running this program is that when it asks for an input of 
//characters the user will input characters not an integer and when the program asks for a number that 
//the user will input a number not a character.  Known bugs in the program are when choosing the 
//state if you choose outside the range it doesnt input anything into the state. The same thing for 
//the party input. I have tried multiple different things and none of them have worked.  

#include "defs.h"// includes the librarys of functions used in this program
#define MAX_CHAR 32

//Prototypes for the functions shown below the main function
int nameInput(char firstName[MAX_CHAR + 1], char lastName[MAX_CHAR + 1], char suffix[4]);
int printName(char firstName[MAX_CHAR + 1], char middleInt, char lastName[MAX_CHAR + 1], char suffix[4]);
char inputMid(void);
char printMid(char middleInt);
void emptyStdin(void);
int inputAge(int min, int max);
char inputSex(void);
int printAge(int age);
char printSex(char sex);
int office(char officeHeld[MAX_CHAR + 1]);
int printOffice(char officeHeld[MAX_CHAR + 1], int years);
int partyInput(void); 
char *printParty(int party);
char stateInput(void);
int printState(int state);
char phoneInput(char phone[11]);
char printPhone(char phone[11]);
int inputTwitter(char twitter[16]);
int printTwitter(char twitter[16]);

int main (void)
{
	//variables for the functions shown below, initiallized the variables/arrays to 0
	//age/sex
	int choice = 0, age = 0, years = 0, party = 0, state = 0; 
	char firstName[MAX_CHAR + 1] = {0}, lastName[MAX_CHAR + 1] = {0}, suffix[4] = {0}, officeHeld[MAX_CHAR + 1] = {0}, twitter[16] = {0};
	char sex = 0, middleInt = 0;
	char phone[11]= {0};
	float income = 0;
	double  lies = 0, ratio = 0;
	int i = 0;
	//the menu is in a do while loop such that it will be printed out after each of the cases are done below
	do 
	{
		//prints out menu for the user to be able to choose an option
		printf("Menu\n");
		printf("1. Name\n");
		printf("2. Enter Years, Party, Office, and State \n");
		printf("3. Enter Age and Sex\n");
		printf("4. Enter Contacts \n");
		printf("5. Enter Contributions and Lies \n");
		printf("6. Display Data \n");
		printf("7. Clear all Data \n");
		printf("8. Quit\n");
		scanf("%d", &choice);

		switch (choice)
		{
			case 1: //inputs the name of the polititcian
				emptyStdin();
				nameInput(firstName, lastName, suffix);
				middleInt = inputMid();
				break;
			case 2: //enters the number of yeears the politician served, the political party, office held and state
				emptyStdin();
				years = office(officeHeld);
				emptyStdin();
				party = partyInput();
				emptyStdin();
				state = stateInput();
				break;
			case 3: //enters the age and sex of the politician
				emptyStdin();
				age = inputAge(21,99);
				emptyStdin();
				sex = inputSex(); 
				break;
			case 4: //inputs the phone number and twitter handle of the politician
				emptyStdin();
				phoneInput(phone); 
				emptyStdin();
				inputTwitter(twitter);
				break;
			case 5: //inputs the amount of dollars recieved and the number of lies told for the politician 
				emptyStdin();
				printf("Enter the amount of dollars receieved [from 0.0 to 1.0e+50]: ");
				do
				{
					scanf("%f", &income);
				}while(income < (pow(1.0, 50)) && income > 0); //we have to use the pow fucntion so that inputed number is in the range

				emptyStdin(); 	
				printf("Enter the numbers of lies told [from 0.0 t0 1.0e+100]: ");
				do 
				{
					scanf("%lf", &lies);
				}while (lies < (pow(1.0, 100)) && lies > 1.0); //use the pow function to make sure that the inputed number is in the range

				break;
			case 6: //prints out the information inputed by the user
				printName(firstName, middleInt, lastName, suffix);
				printAge(age);
				printSex(sex);
				printOffice(officeHeld, years);
				printParty(party);
				printState(state);
				printPhone(phone);
				printTwitter(twitter);
				printf("- US dollars recieved: %.1e", income);
				printf("\n- Number of lies told: %.1le\n", lies);
				ratio = income/lies; //gets the ratio of lies to dollars recieved 
				printf("- Ratio of contribuitions to lies: %.2le [dollars per lie]\n", ratio);
				break;
			case 7: //clears all data fields of evrything inputed
				printf("Clearing all data fields\n");
				for (i = 0; i < 33; i ++)
				{
					firstName[i] = 0;
				}

				i = 0;
				for (i = 0; i < 33; i++)
				{
					lastName[i] = 0;
				}
		
				i = 0;
				for(i = 0; i < 4; i++)
				{
					suffix[i] = 0;
				}
				
				i = 0;
				for (i = 0; i < 33; i++)
				{
					officeHeld[i] = 0;
				}
		
				i = 0;
				for ( i = 0; i < 16; i++)
				{
					twitter[i] = 0;
				}
		
				i = 0;
				for ( i = 0; i < 11; i ++)
				{
					phone[i] = 0;
				}

				choice = 0;
				age = 0;
				years = 0;
				party = 0;
				state = 0;
				sex = 0;
				middleInt = 0;
				income = 0;
				lies = 0;
				ratio = 0;
				break;
			case 8: //closes the program
				emptyStdin();
				choice = 8; 
				break;
			default: //checks to make sure that the inputted number is within the range (1 to 8)
				printf("Input is invalid\n");
				break;
		}
	} while(choice != 8);
	
return (0);	
}
//inputs the middle inital of the politician
char inputMid(void)
{
	char middleInt;

	printf("Type in the politicians middle inital. If none press enter.: ");
	middleInt = getchar();
return middleInt;
}
//function that prints the middle inital of the politician
char printMid(char middleInt)
{
	printf("- Middle inital: ");
	putchar(middleInt);
	
return 0;
}
//inputs the first name, last name and suffix of the politician 
int  nameInput(char firstName[MAX_CHAR + 1], char lastName[MAX_CHAR + 1], char suffix[4])
{
	char input;
	int i = 0;

	printf("Type in the politicians first name (max 32 characters): ");
	scanf("%32s", firstName);
	emptyStdin();

	printf("Type in the politicians last name (max 32 characters): ");
	scanf("%32s", lastName);
	emptyStdin();

	printf("Type in the politicians suffix. If none type press enter. (max 3 characters): ");
	while ((input = getchar()) != '\n' && i < 4)
	{
		suffix[i] = input;
		i++;
	}suffix[i] = '\0';	//adds null character to the end of the array
return 1;
}
//prints the first, middle, last and suffix of the politician
int printName(char firstName[MAX_CHAR + 1], char middleInt, char lastName[MAX_CHAR + 1], char suffix[4])
{
	int i = 0;

	printf("*****Unknown/Not Applicable if the output shows nothing*****\n\n");	
	printf("- Politicians first name: ");
	for (i = 0; i != ('\n' || '\0'); i++)
	{
		printf("%s", &firstName[i]);
	}
	
	printf("\n");
	printMid(middleInt);
	printf("\n");
	
	i = 0;
	printf("- Politicians last name: ");
	for (i = 0; i != ('\n' || '\0'); i++)
	{
		printf("%s", &lastName[i]);
	}
	printf("\n");

	i = 0;
	printf("- Politicians suffix: ");
	if (suffix[i] != 0)
	{
		for (i = 0; i != ('\n' || '\0'); i++)
		{
			printf("%s", &suffix[i]);
		}
	} 
	else;

	printf("\n");

return 1;
}
//this function emptys stdin such that everything is clean for the next input
void emptyStdin(void)
{
	int c = getchar();

	while (c != EOF && c != '\n')
	{
		c = getchar();
	}
}
//this function allows the user to input the politicians age, it also checks to make sure that the number is in the range
int inputAge(int min, int max)
{
	int age = 0, i = 0;
	printf("Enter the age of the politician [Between 21 and 99]: ");

	i = 1;
	for(i = 1; i < 2; i++)
	{
		scanf("%d", &age);
		if (age < min || age > max)
		{
			printf("That number isnt in the range. Please try again. \n");
			i--;
		}
		else
		{
			break;
		}
	}

return age;
}
//this function allows the user to input the sex of the politician, also checks to make sure that it is a M or F
char inputSex(void)
{
	int i = 0;
	char sex;
	
	i = 1;
	printf("Enter the sex of the politician [Choose either M or F]: ");
	for(i = 1; i < 2; i++)
	{
		scanf("%c", &sex);
		if(sex == 'M' || sex == 'F')
		{
			break;
		}
		else
		{
			printf("That is not a vaild input. Please try again.");
			i--;
		}
	}
return sex;
}	
//prints out the age of the politician from the age that was inputted 
int printAge(int age)
{
	printf("- Age: %d\n", age);
return 1;
}
//prints out the sex of the politician
char printSex(char sex)
{
	printf("- Sex: %c\n", sex);
return 1;
}
//theis function allows the user to input the office held and the amount of years served. For the amount of years served
//it checks to make sure it is in the range
int office(char officeHeld[MAX_CHAR + 1])
{
	int i = 0, years = 0;

	printf("Enter the office held [max 32 characters]: ");
	fgets(officeHeld, 33, stdin);

	printf("Enter the amount of years served [0 to 99]: ");
	i = 1;
	for ( i = 1; i < 2; i++)
	{
		scanf("%d", &years);
		if(years < 0 || years > 99)
		{
			printf("That isnt in the range. Please try again.\n");
			i--;
		}
		else
		{
			break;
		}
	}
	
return years;
}
//prints out the office held by the politician and the number of years served by the politician
int printOffice(char officeHeld[MAX_CHAR + 1], int years)
{
	int i = 0;
	
	printf("- Position the politician held is: ");
	for (i = 0; i < ('\n' || '\0'); i++)
	{
		printf("%s", &officeHeld[i]);
	}
	printf("\n");
	
	printf("- Amount of years the politician served: %d\n", years);

return 1;
}
//prints out the party options for the politician and has the user input the number corresponding to the party. Stores 
//that number in an integer called choice.
int partyInput(void)
{
	int choice = 0;

	printf("Pick a number that corresponds to the party below.\n");
	printf("1 - Constitution\n");
	printf("2 - Democrat\n");
	printf("3 - Green\n");
	printf("4 - Libertarian\n");
	printf("5 - Republician\n");
	scanf("%d", &choice);

return choice;
}
//passes in the value for party and prints out the corresponding party.
char* printParty(int party)
{
	char* partyArr = (char*)malloc(sizeof(char) * 15);
	int i = 0;
		
	switch (party)
	{
		case 1:
			strncpy(partyArr, "Constitution", 15);
			break;
		case 2:
			strncpy(partyArr, "Democrat", 15);;
			break;
		case 3: 
			strncpy(partyArr, "Green", 15);
			break;
		case 4:
			strncpy(partyArr,"Libertarian", 15);
			break;
		case 5:
			strncpy(partyArr, "Republican", 15);
			break;
		default:
			break; 
	}

	if (party > 1 || party < 8)
	{
		printf("- Party: ");
		for (i = 0; i != ('\n' || '\0'); i++)
		{
			printf("%s", &partyArr[i]);
		}
		printf("\n");
	}
	else
	{
		printf("- Party: \n");
	}

return 0;
}
//prints out the choices for the states and stores the number corresponding to the state
char stateInput(void)
{
	int choice = 0;

	printf("Choose a state from the list below: ");
	printf("\n 1. AL	2. AK\n");
	printf(" 3. AZ	 4. AR\n");
	printf(" 5. CA	 6. CO\n");
	printf(" 7. CT	 8. DE\n");
	printf(" 9. FL	10. GA\n");
	printf("11. HI	12. ID\n");
	printf("13. IL	14. IN\n");
	printf("15. IA	16. KS\n");
	printf("17. KY	18. LA\n");
	printf("19. ME	20. MD\n");
	printf("21. MA	22. MI\n");
	printf("23. MN	24. MS\n");
	printf("25. MO	26. MT\n");
	printf("27. NE	28. NV\n");
	printf("29. NH	30. NJ\n");
	printf("31. NM	32. NY\n");
	printf("33. NC	34. ND\n");
	printf("35. OH	36. OK\n");
	printf("37. OR	38. PA\n");
	printf("39. RI	40. SC\n");
	printf("41. SD	42. TN\n");
	printf("43. TX	44. UT\n");
	printf("45. VT	46. VA\n");
	printf("47. WA	48. WV\n");
	printf("49. WI	50. WY\n");
	scanf("%d",&choice);

return choice;
}
//brings in the value of the state choosen and prints out the the corresponind state
int printState(int state)
{
	char* stateOutput = (char *)malloc(sizeof(char)*3);
	int i = 0;

		switch (state)
		{
			case 1:
				strncpy(stateOutput,"AL",3);
				break;
			case 2:
				strncpy(stateOutput,"AK",3);
				break;
			case 3:
				strncpy(stateOutput,"AZ",3);
				break;
			case 4:
				strncpy(stateOutput,"AR",3);
				break;
			case 5:
				strncpy(stateOutput,"CA",3);
				break;
			case 6: 
				strncpy(stateOutput,"CO",3);
				break;
			case 7:
				strncpy(stateOutput,"CT",3);
				break;
			case 8:
				strncpy(stateOutput,"DE",3);
				break;
			case 9:
				strncpy(stateOutput,"FL",3);
				break;
			case 10:			
				strncpy(stateOutput,"GA",3);
				break;
			case 11:
				strncpy(stateOutput,"HI",3);
				break;
			case 12:
				strncpy(stateOutput,"ID",3);
				break;
			case 13:
				strncpy(stateOutput,"IL",3);
				break;
			case 14:
				strncpy(stateOutput,"IN",3);
				break;
			case 15:
				strncpy(stateOutput,"IA",3);
				break;
			case 16:
				strncpy(stateOutput,"KS",3);
				break;
			case 17:
				strncpy(stateOutput,"KY",3);
				break;
			case 18:
				strncpy(stateOutput,"LA",3);
				break;
			case 19:
				strncpy(stateOutput,"ME",3);
				break;
			case 20:
				strncpy(stateOutput,"MD",3);
				break;
			case 21:
				strncpy(stateOutput,"MA",3);
				break;
			case 22:
				strncpy(stateOutput,"MI",3);
				break;
			case 23:
				strncpy(stateOutput,"MN",3);
				break;
			case 24:
				strncpy(stateOutput,"MS",3);
				break;
			case 25:
				strncpy(stateOutput,"MO",3);
				break;
			case 26:
				strncpy(stateOutput,"MT",3);
				break;
			case 27:
				strncpy(stateOutput,"NE",3);
				break;
			case 28:
				strncpy(stateOutput,"NV",3);
				break;
			case 29:
				strncpy(stateOutput,"NH",3);
				break;
			case 30:
				strncpy(stateOutput,"NJ",3);
				break;
			case 31:
				strncpy(stateOutput,"NM",3);
				break;
			case 32:
				strncpy(stateOutput,"NY",3);
				break;
			case 33:
				strncpy(stateOutput,"NC",3);
				break;
			case 34:
				strncpy(stateOutput,"ND",3);
				break;
			case 35:
				strncpy(stateOutput,"OH",3);
				break;
			case 36:
				strncpy(stateOutput,"OK",3);
				break;
			case 37:
				strncpy(stateOutput,"OR",3);
				break;
			case 38:
				strncpy(stateOutput,"PA",3);
				break;
			case 39:
				strncpy(stateOutput,"RI",3);
				break;
			case 40:
				strncpy(stateOutput,"SC",3);
				break;
			case 41:
				strncpy(stateOutput,"SD",3);
				break;
			case 42:
				strncpy(stateOutput,"TN",3);
				break;
			case 43:
				strncpy(stateOutput,"TX",3);
				break;
			case 44:
				strncpy(stateOutput,"UT",3);
				break;
			case 45:
				strncpy(stateOutput,"VT",3);
				break;
			case 46:
				strncpy(stateOutput,"VA",3);
				break;
			case 47:
				strncpy(stateOutput,"WA",3);
				break;
			case 48:
				strncpy(stateOutput,"WV",3);
				break;
			case 49:
				strncpy(stateOutput,"WI",3);
				break;
			case 50:
				strncpy(stateOutput,"WY",3);
				break;
			default: 
				break;
		}

	printf("- State: ");
	for (i = 0; i != ('\n' || '\0'); i++)
	{
		printf("%s", &stateOutput[i]);
	}
	printf("\n");
return 0;
}
//asks for the phone number of the politician and stores it in an array called phone
char phoneInput(char phone[11])
{
	printf("Input the politicians phone number with no spaces: ");
	fgets(phone, 11, stdin);
return 1;
}
//prints out the phone number of the politician in the correct format
char  printPhone(char phone[11])
{
	printf("- Phone Number: (%c%c%c)%c%c%c-%c%c%c%c", phone[0], phone[1], phone[2], phone[3], phone[4], phone[5], phone[6], phone[7], phone[8], phone[9]);

return 1;
}
//this function allows the user to input the twitter handle of the poltician 
int inputTwitter(char twitter[16])
{
	printf("Enter the politicians twitter handle with out the @: ");
	fgets(twitter, 16, stdin);
return 0;
}
//prints out the twitter handle for the politician 
int printTwitter( char twitter[16])
{	
	
	printf("\n- Twitter handle: @%s\n", twitter);
return 0;
}	
