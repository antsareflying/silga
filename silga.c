#include <stdio.h>
#include <stdlib.h> /*srand, rand*/
#include <time.h>
#include <math.h>

double double_rand_range(double a, double b);
double int_rand_range(double a, double b);
int cmpfunc (const void * a, const void * b);

int generation = 0;
double population[30][6] = {0};
double populationfitness[30] = {1};


int main(void)
	{
		int generation = 0;
		double population[30][6] = {0};
		double populationfitness[30] = {1};
		int tournament_winners[15];

		for(int i = 0; i < 30; i++)
		{
			for( int j = 0; j < 6; j++)
			{
				population[i][j] = double_rand_range(5000, -5000); /*random number b/w -5000 and 5000*/
			}
		}
		
		
		for(int i = 0; i < 30; i++)
		{
			populationfitness[i] = (population[i][1]/*a*/ + 30 * pow(population[i][2], 2) * population[i][3]/*30b^2c*/ - 2 * pow(population[i][4], 3) * pow(population[i][5], 2)/*2d^3e^2*/ + 2 * population[i][6]/*2f*/ - 2567);
			/* calculate fitness function (a+30b^2c-2d^3e^2+2f) - 2567*/
		}

		while (populationfitness != 0)
		{
			//calc fitness fuunction
			for(int i = 0; i < 30; i++)
			{
				populationfitness[i] = (population[i][1]/*a*/ + 30 * pow(population[i][2], 2) * population[i][3]/*30b^2c*/ - 2 * pow(population[i][4], 3) * pow(population[i][5], 2)/*2d^3e^2*/ + 2 * population[i][6]/*2f*/ - 2567);
				/* calculate fitness function (a+30b^2c-2d^3e^2+2f) - 2567*/
			}

			//check if soln found
			for(int i = 0; i < 30; i++)
			{
				if (populationfitness[i] == 0)
				{
					return 0;
				}
			}
			
			//qsort(populationfitness, 30, sizeof(double), cmpfunc);
			
			
				for(int i = 0; i < 15; i++)
				{
					if(populationfitness[i*2] < populationfitness[i*2+1])
					{
						tournament_winners[i] = i*2;
					}
					else if(populationfitness[i*2+1] < populationfitness[i*2])
					{
						tournament_winners[i] = i*2+1;
					}
				}
		
			for (int i=0;i<15;i++)
			{
			printf("%d\n", tournament_winners[i]);
			}
			return 0;
		}
		
		
	}

double double_rand_range(double a, double b)
{
	return (((((double)rand()) / ((double)(RAND_MAX))) * (a - b)) + b); /*generates random double between a(upper) and b(lower)*/
}

double int_rand_range(double a, double b)
{
	return (int)((((rand()) / ((RAND_MAX))) * (a - b)) + b); /*generates random int between a(upper) and b(lower)*/
}

int cmpfunc (const void * a, const void * b) //compare function for qsort
{
	if (abs(*(double*)a) > abs(*(double*)b)) return 1;
	else if (abs(*(double*)a) < abs(*(double*)b)) return -1;
	else return 0;
}

