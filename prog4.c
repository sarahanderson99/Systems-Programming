/*
NAME Sarah Anderson (CU Username: sca2)
CLASS ECE 2220.001 (Spring 2019)
PROJECT Convolution - Array's and Pointers
PURPOSE The purpose of this program is to have two inputed files with data and convolute them to create a 
	output file. 
ASSUMPTIONS Assumptions made are that people understand how to run this program and if they dont input
	the correct number of inputs the program will not run. No known bugs as of 3-11-2019. 
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//Inistalizing the structure outside of main such that you can refer to it in main THIS IS NOT A GLOBAL VARIBLE
struct TData {
	int MinIndex, MaxIndex, Points;
	float *pValue;
};
//Protypes for the functions used in this program
int inputValues(const char *input, int i, struct TData *pInput);
int moveData(struct TData *pInput1, struct TData *pInput2, struct TData *pOutput);
int insertData(const char *output, struct TData *pOuput);

int main (int argc, char **argv){
	//initalizing the structure's elements
	struct TData Input[2], Output;
	
	//Checks to make sure there were three things inputd in the command line arguments
	if(argc != 4){
		printf("Not enough input arguments in the command line. Must have 3. Two input and an output.\n");
		exit(1);
	}
	//Passes in the file inputed and the address of the structure that the values will be inputed into
	inputValues(argv[1], 0, &Input[0]);	//inputting the values for the first inputed file
	inputValues(argv[2], 1, &Input[1]);	//inputting the values for the second inputed file
	
	//finds the value of maxIndex, minIndex and points for the output file, also does the convolution
	moveData(&Input[0], &Input[1], &Output);
	//Inserts the data into the output.txt file
	insertData(argv[3], &Output);

	//Frees the pointers that point to the values in the structures
	free(Input[0].pValue + Input[0].MinIndex);
	free(Input[1].pValue + Input[1].MinIndex);

return 0;
}
 
//This function inputs data from the files to the structures for the different structures 
//for the inputed structures
int inputValues(const char *input, int i, struct TData *pInput){
	int j = 0, inttemp = 0;
	float floattemp = 0;

	FILE *inputFile;
	
	printf("Opening input file #%d...\n", i+1);
	//This if statement checks to make sure that the file was able to be opened
	if((inputFile = fopen(input, "rt")) == NULL){
		printf("Cannot open file");
		exit(1);
	}
	
	//initalizing the pointer of the input file that points to the value of points in the struct
	pInput->Points = 0;

	//Does the while loop until the inoutFile doesnt equal EOF (end of file)	
	while(!feof(inputFile)){
		fscanf(inputFile, "%d %f", &inttemp, &floattemp);//scans in the data from inputFile and put in stdin
//		printf("%d	%f\n", inttemp, floattemp);//Checks to make sure that the data is correct 
		if (pInput->Points == 0){	//Creates the minIndex of the fileInput
			pInput->MinIndex = inttemp;
		}
		pInput->Points += 1;	//Moves to the next "point"
	}
	pInput->Points -= 1;
	//Creates the maxIndex by adding the number of points to the minIndex
	pInput->MaxIndex = pInput->MinIndex + pInput->Points - 1;	
	//Prints these things out such that we can check to make sure they are right
	printf("Min Index = %d\tMax Index = %d \n", pInput->MinIndex, pInput->MaxIndex);
	rewind(inputFile);//Starts the file at the beginning again
	
	//Mallocing enoght space for the inputed file
	pInput->pValue = (float *)malloc(pInput->Points * sizeof(float)) - pInput->MinIndex;

	printf("Storing the values from the inputed file...\n");
	
	//This for loop stores the values in to the structure
	for (j = pInput->MinIndex; j < pInput->MinIndex + pInput->Points; j++){
		fscanf(inputFile, "%i %f\n", &inttemp, &pInput->pValue[j]);
		printf("Value[%d] = %f\n", j, pInput->pValue[j]);
	}
	printf("\n");
	//Closes the inputFile such that we can open another one
	fclose(inputFile);
return 0;
}

int moveData(struct TData *pInput1, struct TData *pInput2, struct TData *pOutput){
	int i = 0, j = 0;

	pOutput->MinIndex = pInput1->MinIndex + pInput2->MinIndex;//To get the output MinIndex you add both of the inputed files minIndexes together
	pOutput->MaxIndex = pInput1->MaxIndex + pInput2->MaxIndex;//To get the MaxIndex of the output you add together both of the inputed files
	//To get the amount fo points you will have you need to do output MAxIndex minus the output MinIndex and then add 1
	pOutput->Points = pOutput->MaxIndex - pOutput->MinIndex + 1;
	
	printf("Output File...\n");

	//Prints out such that we can check the values of the output (MinIndex, MaxIndex and Points)
	printf("Output MinIndex = %d \t Output MaxIndex = %d \t Output Number of Points = %d \n", pOutput->MinIndex, pOutput->MaxIndex, pOutput->Points);

	//Allocating space in memory for the output struct 	
	pOutput->pValue = (float *)malloc(pOutput->Points * sizeof(float));
	pOutput->pValue = pOutput->pValue - pOutput->MinIndex; //Moves the pointer to the right place
	
	//This for loop it reverses the seconf input file and stores the values in the output file. Also,
	//it preforms the math for the convolution such that we get the output file.
	for(j = pOutput->MinIndex; j <= pOutput->MaxIndex; j++){
		pOutput->pValue[j] = 0; //initalizes the value to 0
		for(i = pInput1->MinIndex; i <= pInput1->MaxIndex; i++){
			if(((j - i) >= pInput2->MinIndex) && ((j - i) <= pInput2->MaxIndex)){
				pOutput->pValue[j] += pInput1->pValue[i] * pInput2->pValue[j - i];
			}
		}
		//prints out the output of the program such that we can check to make sure that it works
		printf("pOutput->pValue[%d] = %f \n", j, pOutput->pValue[j]);
	}
return 0;
}

//This function moves the data from the utput struct and stores it into the txt file that was inputted in the 
//command line arguments (the last one in the command line)
int insertData(const char *output, struct TData *pOutput){
	int i = 0;
	FILE *fOutput;

	printf("Writing Data to output file entered...\n");
	
	//Checks to make sure that the output file can be opened
	if((fOutput = fopen(output, "w")) == NULL){
		printf("Cannot open output file");
		exit(1);
	}	
	
	//inouts the data from the struct to the output file
	for(i = pOutput->MinIndex; i <= pOutput->MaxIndex; i++){
//		printf("%d	%f\n", i, pOutput->pValue[i]);
		fprintf(fOutput, "%d\t%f\n", i, pOutput->pValue[i]);
	}

	//closes the file such that we dont waste memory
	fclose(fOutput);

	printf("Done with the program :)\n");//indicates the user that the program has finsihed
return 0;
} 
