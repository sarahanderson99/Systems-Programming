//**Sarah Anderson (CU username: Sca2)
//**ECE 2220: Spring 2019
//**Project 1: Choosing Lottery Numbers
//**Purpose: The purpose of this program is to have a user input numbers into an array. Then, that array will be 
//randomly switched around. After the switching, the values in the array will be added to the value behind it
//making sure that the total sum is equal or less than 50. A random number generator will then put random 
//numbers into an array that then will be checked to make sure that there are no repeats. Then the two arrays
//will be compared 1 million times to see if your inputed lottery numbers match the randomly generated ones.
//**Assumptions: We are assuming that anything other than 0 is false. We also are summing that srand(time())
//is truly random (this is the most random a random number generator can get in c. I learned that from hours 
//of research. 
//**Known bugs: I dont have any known bugs that I know of as of 1/22/2019 at 2:50 pm

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//Protypes (the actual functions are down at the bottom after main()
int randNums(int min, int max);
void randOrder(int n, int array[n]); 
void printArr(int arrSize, int array[arrSize]);
void sort(int arrSize, int array[arrSize]);

int main (void)
{
	int i = 0, j = 0, k = 0, temp = 0; //ints for loops
	int totSum = 0; //integer for the total value of the inputed numbers
	int arrSize = 6; //I set the array size equal to six because we are inputing 6 numbers for the lottery game
	int choosenNums[arrSize]; //array for inputed numbers to be stored in
	int randArr[arrSize]; //array for the random numbers generated to be stored in
	bool exists = false; //declaring exits equal to false 
	int contin = 0; //integers for comparing the values of the two strings

	//This do while loop has the user input values that are then added to an array. Then they are summed up to
	//make sure that they equal or less than 50.
	do {
	
		printf("Choose one number from 1 to 5 inclusive: ");
		i = 0;
		for(i = 0; i < 1; i++)
		{
			scanf("%d", &choosenNums[i]);
			if (choosenNums[i] < 1 || choosenNums[i] > 5)
			{
				printf("That number isnt in the range. Please try again.\n");
				i--;
			}
		}

		printf("Choose a number from 1 to 10 inclusive: ");
		i = 1;
		for (i = 1; i < 2; i++)
		{
			scanf("%d", &choosenNums[i]);
			if (choosenNums[i] < 1 || choosenNums[i] > 10)
			{
				printf("That number isnt in the range. Please try again. \n");
				i--;
			}
		}


		printf("Choose a number from 1 to 10 inclusive: ");
		i = 2;
		for (i = 2; i < 3; i++)
		{
			scanf("%d", &choosenNums[i]);
			if (choosenNums[i] < 1 || choosenNums[i] > 10)
			{
				printf("That number isnt in the range. Please try again. \n");
				i--;
			}
		}


		printf("Choose one number from 10 to 12 inclusive: ");
		i = 3;
		for (i = 3; i < 4; i++)
		{
			scanf("%d", &choosenNums[i]);
			if(choosenNums[i] < 10 || choosenNums[i] > 12)
			{
				printf("That number isnt in the range. Please try again. \n");
				i--;
			}
		}


		printf("Choose a number from 8 to 15 inclusive: ");
		i = 4;
		for (i = 4; i < 5; i++)
		{
			scanf("%d", &choosenNums[i]);
			if (choosenNums[i] < 8 || choosenNums[i] > 15)
			{
				printf("That number isnt in the range. Please try again. \n");
				i--;
			}
		}


		printf("Choose a number from 8 to 15 inclusive: ");
		i = 5;
		for (i = 5; i < 6; i++)
		{
			scanf("%d", &choosenNums[i]);
			if (choosenNums[i] < 8 || choosenNums[i] > 15)
			{
				printf("That number isnt in the range. Please try again.\n\n");
				i--;
			}
		}
		printf("\n");
		
		//sorts the emtered numbers in order from least to greatest 
		sort(arrSize, choosenNums);


		//prints out the delta numbers
		printf("Your delta numbers are: ");
		printArr(arrSize, choosenNums);	
		printf("\n\n");


		//Summing up all the imputed choosen numbers
		totSum = choosenNums[0] + choosenNums[1] + choosenNums[2] + choosenNums[3] + choosenNums[4] + choosenNums[5];
		printf("The total sum is %d. \n\n", totSum);

	
		//checking to see if the shoosen numbers add up to less than 50
		if (totSum <= 50)
		{
				
			printf("Congrats! Your numbers add up to a value less than or equal to 50.\n\n");
		}
		else
		{
			printf("Your inputed numbers add up to a number greater than 50. Input your numbers again.\n\n\n");
		
		}
		

	} while (totSum > 50);

	
	if (totSum <= 50)
	{
		//randomly order the numbers in the choosenNums[] array and prints it out
		printf("The final delta sequence is: ");
		randOrder(arrSize, choosenNums);
		printArr(arrSize, choosenNums);
		printf("\n\n");


		//Adds the number in the array to the one before it 
		choosenNums[1] += choosenNums[0];
		choosenNums[2] += choosenNums[1];
		choosenNums[3] += choosenNums[2];
		choosenNums[4] += choosenNums[3];
		choosenNums[5] += choosenNums[4];


		//Sorts the inputed numbers once more to make it eaiser later to compare
		sort(arrSize, choosenNums);

		
		//prints out final lottery numbers that then will be compared to the randomly generated ones
		printf("Your lottery numbers are: ");
		printArr(arrSize, choosenNums);
		printf("\n\n");

		srand(time(NULL)); //sets the random number generator value of time equal to NULL
		do
		{
			for (i = 0; i < 1000000;)
			{
				//puts random numbers in an array called randNums
				k = 0;
				for (k = 0; k < arrSize; k++)
				{
					randArr[k] = randNums(1,50);
				}
	

				//checks to make sure there are no duplicates in the random array 
				k = 0, j = 0, temp = 0;
				while (k < arrSize)
				{
					temp = randNums(1,50);
					exists = false;
					for(j = 0; j < k; ++j)
					{
						if (randArr[j] == temp)
							exists = true;
	
					}
					if (exists == false)
						randArr[k++] = temp;
				}
		

				//sorts the lottery numberss so they can be compared easier
				sort(arrSize, randArr);

					
				//prints out the array of winning lottery numbers for every forth of the program
				if (i == 250000 || i == 500000 || i == 750000 || i == 999999)
				{
					printf("When i = %d, the lottery numbers are: ", i);
					printArr(arrSize, randArr);
					printf("\n");
				}
				

				//compares the elements in the arrays to see if they match. If they do then the program is complete,
				//otherwise the number of times it had run counts up and it moves on
				if (randArr[0] == choosenNums[0] && randArr[1] == choosenNums[1] && randArr[2] == choosenNums[2] && 
				randArr[3] == choosenNums[3] && randArr[4] == choosenNums[4] && randArr[5] == choosenNums[5])
				{
					contin = 1;
				}
				else
				{
					i++;
				}
			}
		}while(contin != 0);
	
		if (contin != 0)
		{
			printf("Congrats! You are a winner! I took %d times to match your lottery numbers with the random ones!\n", i);
		}
		else 
		{
			printf("Sorry, you are not a winner!\n");
		}
	}

return (0);	
}

//generates random numbers between the inputed max and min
int randNums(int min, int max)
{
	int result = 0, low = 0, high = 0;
	if (min < max)
	{
		low = min;
		high = max + 1;
	}
	else
	{
		low = max + 1;
		high = min;
	}

	
	result = (rand() % (high - low)) + low;

	return (result);
}

//randomizes the order of the numbers in the inputed array
void randOrder(int n, int *array)
{
	int i = 0;

	srand((unsigned)time(NULL));
	for (i = 0; i < n - 1; i++)
	{
		size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
		int t = array[j];
		array[j] = array[i];
		array[i] = t;
	}
}

//prints out array
void printArr(int arrSize, int array[arrSize])
{
	int i = 0;
	for (i = 0; i < arrSize; i++)
	{
		printf("%d ", array[i]);
	}
}

//sorts the array from least to greatest
void sort(int arrSize, int array[arrSize])
{
	int i = 0, j = 0, temp = 0;
	for (i = 0; i < (arrSize - 1); ++i)
	{
		for (j = i + 1; j < arrSize; ++j)
		{
			if (array[i] > array[j])
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}

}
