#include <stdio.h>
#include <stdlib.h> /*srand, rand*/
#include <time.h>
#include <math.h>
#include <stdbool.h>

double double_rand_range(double a, double b);
double int_rand_range(double a, double b);
int cmpfunc (const void * a, const void * b);
bool check_fitness_zero(double populationfitness[30]);


int generation = 0;
double population[30][6] = {0};
double populationfitness[30] = {1};
double new_population[30][6] = {0};


int main(void)
{
	int generation = 0;
	double population[30][6] = {0};
	double populationfitness[30] = {1};
	int parent_1[30] = {31};
	int parent_2[30] = {31};

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

	while (check_fitness_zero(populationfitness) == false)
	{
		//calc fitness function
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

		//tournament selection
		
		
		for(int i = 0; i < 30; i++)
		{
			int k = int_rand_range(29,0);
			int l = int_rand_range(29,0);
			if(populationfitness[k] < populationfitness[l])
			{
				parent_1[i] = populationfitness[k];
			}
			else
			{
				parent_1[i] = populationfitness[l];
			}	

			int m = int_rand_range(29, 0);
			printf("m:%d\n", m);
			int n = int_rand_range(29, 0);
			printf("n:%d\n", n);
			if(populationfitness[m] < populationfitness[n])
			{
				parent_2[i] = populationfitness[m];
			}
			else
			{
				parent_2[i] = populationfitness[n];
			}	
		}

		for(int i =0 ; i< 30;i++)
		{
			printf("%d\n", parent_1[i]);
		}
			printf("parent 1 done");
		for(int i =0 ; i< 30;i++)
		{
			printf("%d\n", parent_2[i]);
		}
		
		//tried to get crossover going dont know if correct
		for(int i = 0; i < 30; i+=2)
		{
			for(int j = 0; j < 3; j++)
			{
				new_population[i][j] = population[parent_1[i]][j]; //1st offspring first 3 genes from 1st parent first 3 genes
				new_population[i][5-j] = population[parent_2[i + 1]][5-j]; //first offspring last 3 genes from 2nd parent last 3 genes
			}

			for(int k = 0; k < 3; k++)
			{
				new_population[i+1][k] = population[parent_2[i + 1]][k]; //second offspring first 3 genes from 2nd parent first 3
				new_population[i+1][5-k] = population[parent_1[i]][5-k]; //2nd offsoring last 3 from 1st parent last 3
			}
		}
		

		for (int i=0;i<30;i++)
		{
			for (int j=0;j<6;j++)
			{
				printf("%lf\n", new_population[i][j]);
			}
		}
		return 0;
	}
}

double double_rand_range(double a, double b)
{
	srand(time(NULL));
	return (((((double)rand()) / ((double)(RAND_MAX))) * (a - b)) + b); /*generates random double between a(upper) and b(lower)*/
}

double int_rand_range(double a, double b)
{
	srand(time(NULL));
	return ((((int)(rand()) / (int)(RAND_MAX)) * (a - b)) + b); /*generates random int between a(upper) and b(lower)*/
}

int cmpfunc(const void * a, const void * b) //compare function for qsort
{
	if (abs(*(double*)a) > abs(*(double*)b)) return 1;
	else if (abs(*(double*)a) < abs(*(double*)b)) return -1;
	else return 0;
}

bool check_fitness_zero(double populationfitness[30])
{
	for(int i = 0; i < 30; i++)
	{
		if(populationfitness[i] == 0)
		{
			return true;
		}
		
	}

	return false;
}

