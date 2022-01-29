#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <math.h>
#include "sodium.h"

int cmpfunc (const void * a, const void * b);
bool check_fitness_zero(double populationfitness[30]);

int generation = 0;
int population[30][6] = {0};
int new_population[30][6] = {0};
double populationfitness[30] = {1000000};
int parent_1[30] = {100};
int parent_2[30] = {100};

int main(void)
{

	if(sodium_init() == -1)
	{
		return 1;
	}


	for(int i = 0; i < 30; i++)
	{
		for( int j = 0; j < 6; j++)
		{
			population[i][j] = (randombytes_uniform(100)-50); /*random number b/w -50 and 50*/
		}
	}

	
	for(int i = 0; i < 30; i++)
	{
		populationfitness[i] = (double)(population[i][0]/*a*/ + 30 * pow(population[i][1], 2) * population[i][2]/*30b^2c*/ - 2 * pow(population[i][3],3) * pow(population[i][4],2) /*2de*/ + 2 * population[i][5]/*2f*/ - 2567);
		/* calculate fitness function (a+30b^2c-2d^3e^2+2f) - 2567*/
	}

	bool soln_found = false;
	double best_fitness = 10000000000;
	int best_fitness_index = 31;
	int best_fitness_index_counter = 0;
	int best_fitness_soln[6] = {0};

	while (soln_found == false)
	{
		//calc fitness function
		for(int i = 0; i < 30; i++)
		{
			populationfitness[i] = (double)(population[i][0]/*a*/ + 30 * pow(population[i][1], 2) * population[i][2]/*30b^2c*/ - 2 * pow(population[i][3],3) * pow(population[i][4],2) /*2de*/ + 2 * population[i][5]/*2f*/ - 2567);
			/* calculate fitness function (a+30b^2c-2d^3e^2+2f) - 2567*/
			
			printf("Fitness gen %d row %d: %lf\n", generation, i, populationfitness[i]);
			if(fabs(populationfitness[i]) < fabs(best_fitness))
			{
				best_fitness = populationfitness[i];
				best_fitness_index = i;
				for(int j = 0; j< 6; j++)
				{
					best_fitness_soln[j] = population[i][j];
				}
			}
			else if(populationfitness[i] == best_fitness)
			{
				best_fitness_index_counter++;
				best_fitness_index = i;
			}
		}

		//check if soln found
		if (best_fitness == 0 || best_fitness_index_counter == 10)
		{
			soln_found = true;
		}

		//tournament selection
		for(int i = 0; i < 30; i++)
		{
			int k = randombytes_uniform(30);
			int l = randombytes_uniform(30);
			if(fabs(populationfitness[k]) < fabs(populationfitness[l]))
			{
				parent_1[i] = k;
			}
			else
			{
				parent_1[i] = l;
			}	

			int m = randombytes_uniform(30);
			int n = randombytes_uniform(30);
			if(fabs(populationfitness[m]) < fabs(populationfitness[n]))
			{
				parent_2[i] = m;
			}
			else
			{
				parent_2[i] = n;
			}	
		}
		
		//crossover
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
		
		// mutation
		for(int i = 0; i < 30; i++)
		{
			int random_gene = randombytes_uniform(6);
			int random_mutation = (randombytes_uniform(10) - 5); /*random mutation between -5 and 5*/
			new_population[i][random_gene] += random_mutation;
		}

		for(int i = 0; i < 30; i++)
		{
			for(int j = 0; j < 6; j++)
			{
				population[i][j] = new_population[i][j];
			}
		}

		generation++;

		
	}

	printf("%d\n", best_fitness_index);
	printf("%lf\n", populationfitness[best_fitness_index]);
	printf("generation: %d\n", generation-1);
		
	for(int i = 0; i< 6; i++)
	{
		printf("%d  ", best_fitness_soln[i]);
	}
}

int cmpfunc(const void * a, const void * b) //compare function for qsort
{
	if (fabs(*(double*)a) > fabs(*(double*)b)) return 1;
	else if (fabs(*(double*)a) < fabs(*(double*)b)) return -1;
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

