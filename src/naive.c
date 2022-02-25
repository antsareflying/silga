#include <stdio.h>
#include <float.h>
#include <stdbool.h>
#include <math.h>

#include "sodium.h"

#define POPULATION_SIZE 30// TODO: replace with command line arg
#define CHROMOSOME_LENGTH 6

int calculate_chromosome(int row_size, int row, int col);

int main(void)
{
	int generation = 0;
	int population[POPULATION_SIZE * CHROMOSOME_LENGTH] = {0};
	double population_fitness[POPULATION_SIZE] = {DBL_MAX};
	int best_fitness_soln[POPULATION_SIZE] = {0};


	for(int i = 0; i < POPULATION_SIZE; i++)
	{
		for( int j = 0; j < CHROMOSOME_LENGTH; j++)
		{
			population[calculate_chromosome(CHROMOSOME_LENGTH, i, j)] = (randombytes_uniform(100)-50); /*random number b/w -50 and 50*/
		}
	}


	bool soln_found = false;
	while(soln_found == false)
	{
		generation++;

		for(int i = 0; i < POPULATION_SIZE; i++)
		{
			population_fitness[i] = (double)(population[calculate_chromosome(CHROMOSOME_LENGTH, i, 0)]/*a*/ 
			+ 30 * pow(population[calculate_chromosome(CHROMOSOME_LENGTH, i, 1)], 2) * population[calculate_chromosome(CHROMOSOME_LENGTH, i, 2)]/*+30b^2c*/ 
			- 2 * pow(population[calculate_chromosome(CHROMOSOME_LENGTH, i, 3)],3) * pow(population[calculate_chromosome(CHROMOSOME_LENGTH, i, 4)],2) /*-2de*/
			+ 2 * population[calculate_chromosome(CHROMOSOME_LENGTH, i, 5)]/*2f*/ - 2567);
			/* calculate fitness function (a+30b^2c-2d^3e^2+2f) - 2567*/
		}

		for(int i = 0; i < POPULATION_SIZE; i++)
		{
			if(population_fitness[i] == 0)
			{
				for(int j = 0; j< CHROMOSOME_LENGTH; j++)
				{
					best_fitness_soln[j] = population[i * CHROMOSOME_LENGTH + j];
				}
				soln_found = true;
			}
		}
		printf("Guessing...\n");
	}

	printf("generation: %d\n", generation);
	printf("solution: a, b, c, d, e, f\n");
	for(int i = 0; i< CHROMOSOME_LENGTH; i++)
	{
		printf("%d  ", best_fitness_soln[i]);
	}

	return 0;
}

int calculate_chromosome(int row_size, int row, int col)
{
	int chromosome = row * row_size + col;
	return chromosome;
}