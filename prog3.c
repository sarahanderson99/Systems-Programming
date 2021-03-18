//Sarah Anderson (CU Username SCA2)
//ECE 2220.001 (Spring 2019)
//Project: Bitwise Ops Project
//Purpose: The purpose of this file is to have the user input two ASCII values and then it produces parity bits for the inputed ASCII variables.
//Assumptions: We are assuming that the user understands what an ASCII value is and they understand what the least and most significant bits are. No known bugs at this time. 

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_1 3
#define MAX_2 21

int converttoBinary(char *input);
int shiftBits(int binary);
int printBinary(int binary);
int calcParity(int binary);

int main (void) {

	char contin = '\0'; //Character that tells the prgram to go again or stop and exit
	char input[MAX_1] = {'\0'};
	int i = 0, binary = 0;

	do{
		contin = '\0'; 
		for (i = 0; i < MAX_1; i++){
			input[i] = '\0';
		}
		//inputs the ASCII charcters such that they can be error detected
		printf("Enter two ASCII characters: ");
		fgets(input, MAX_1, stdin);
		getchar();
		
		//Converts the inputed ASCII values to binary and stores that in an integer 
		binary = converttoBinary(input);

		//shifts the current bits in binary to there final place...leaving space for parity bits
		binary = shiftBits(binary);		

		//calculates the parity bits and places them in the correct position
		binary = calcParity(binary);
		printBinary(binary);
		printf("Or in Hex: 0x%08X", binary);
		printf("\n");
		
		//has user input if they want to continue and input another set or end the program 
		printf("\nDo you wish to enter another input 'y' or 'n'? ");
		scanf("%c", &contin);
		getchar();
	}
	while(contin == 'y' || contin == 'Y');

return 0;
}

//Coverts the hex value for the ASCII value into one binary integer
int converttoBinary(char *input){
	int32_t binary = 0; 

	binary |= (input[1] & 0xFFFF); //ands in all 1's and then ors binary
	binary = binary << 8;//moves the second ascii character inputed over 8 bits
	binary |= (input[0] & 0x00FF); //does the same thing as above but only does it to the last 8 bits (enough room for the first ascii value)
	printf("The output of this will give you the binary representation of the inputed ASCII characters.\n");
	printf("The least significant character is the one that you inputed first.\n");
	printf("The final binary value of %s is:  ", input);
	printBinary(binary); //calls the function to print out the binary number

return binary;
}

//Prints out the binary representation of the two ASCII characters entered
int printBinary(int binary){
	int i = 0;
	
	//This for loop prints out the binary representation for the ASCII characters inputed
	for (i = (MAX_2 - 1); i >= 0; --i){
		putchar((binary & (1 << i)) ? '1' : '0');
		//creates spaces in between 4 bits so easily read
		if (i == 4 || i == 8 || i == 12 || i == 16 || i == 20){
			printf(" ");
		}
	}
	putchar('\n');
return 0;
}

//Shifts bits such that it accounts for parity bits
int shiftBits(int binary){
	int one = 2, two = 0, three= 0, four = 0;

	//and's in a value such that it moves the bits to make room for the parity bits
	one = binary & 0xF800;
	one = one << 5;
	two = binary & 0x7F8;
	two = two << 4;
	three = binary & 0xE;
	three = three << 3;
	four = binary & 0x1;
	four = four << 2;
	
	//adds together all the parts such that we can get one binary value
	binary = one + two + three + four;

	printf("\nBinary number with parity bits spaces added is: ");
	printBinary(binary);
return binary;
}

//Calculates the parity bits for the final outcome of the program
int calcParity(int binary){
	int i = 0, count = 0, result = 0, inttemp = 0;
	int temp[MAX_2 + 1] = {0};

	inttemp = binary;
	//Making an array with the binary number in it such that it is eaiser to compare if there
	//are 1's or 0's in that specifc place
	while (inttemp > 0){
		temp[i + 1] = inttemp % 2;	//must add one such that the number correspond to the binary value
		inttemp = inttemp / 2;
		i++;
	}

	//Calcutating the first parity bit (in position 1)
	for (i = 1; i <= MAX_2; i++){
		//just comapring 1 to the values in the spot in the array and if it is a 1 then it counts up 1
		if(i == 3 || i == 5 || i == 7 || i == 9 || i == 11 || i == 13 || i == 15 || i == 17 || i == 19 || i == 21){
			result = temp[i] & 1;
			if (result != 0){
				count++;
			}
		}
	}
	count = count % 2;	//take mod 2 such that we know if it is even or odd, if odd the parity bit is a 1
	if (count != 0){
		binary = binary | 0x1;
	}

	//Calculating the second parity bit (in position 2) [Follows same way as above for parity bit 1]
	i = 1, count = 0, result = 0;	//reinitalizing the values
	for (i = 1; i <= MAX_2; i++){
		if(i == 2 || i == 3 || i == 6 || i == 7 || i == 10 || i == 11|| i == 14 || i == 15 || i == 18 || i == 19){
			result = temp[i] & 1;
			if (result == 1){
				count++;
			}
		}
	}
	count = count % 2;
	if (count == 1){
		binary = binary | 0x2;
	}

	//Calcuating the third parity bit (in position 4) [Same procedure as above for the forst parity bit]
	i = 1, count = 0, result = 0;
	for (i = 1; i <= MAX_2; i++){
		if (i == 5 || i == 6 || i == 7 || i == 12 || i == 13 || i == 14 || i == 15 || i == 20 || i == 21){
			result = temp[i] & 1;
			if (result == 1){
				count++;
			}
		}
	}
	count = count % 2;
	if(count == 1){
		binary = binary | 0x8;
	}

	//Calculating the parity bit for the forth pairty bit (in position 8)
	i = 1, count = 0, result = 0;
	for(i = 1; i <= MAX_2; i++){
		if(i == 9 || i == 10 || i == 11 || i == 12 || i == 13 || i == 14 || i == 15){
			result = temp[i] & 1;
			if (result == 1){
				count++;
			}
		}
	}
	count = count % 2;
	if (count == 1){
		binary = binary | 0x80;
	}

	//Calcuating the fifth pairty bit (in position 16)
	i = 1, count = 0, result = 0;
	for(i = 1; i <= MAX_2; i++){
		if(i == 17 || i == 18|| i == 19 || i == 20 || i == 21){
			result = temp[i] & 1;
			if (result == 1){
				count++;
			}
		}
	}
	count = count % 2;
	if (count == 1){
		binary = binary | 0x8000;
	}

	printf("\nFinal binary number with parity bits inserted is: ");
	
return binary;
}
