#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include "sodium.h"


#define POPULATION_SIZE 30// TODO: replace with command line arg
#define CHROMOSOME_LENGTH 6

int calculate_chromosome(int row_size, int row, int col);
bool check_fitness_zero(double population_fitness[30]);


double population_fitness[POPULATION_SIZE] = {DBL_MAX}; // TODO: use pointers to remove global variable?


int main(void)
{
	int generation = 0;
	int population[POPULATION_SIZE * CHROMOSOME_LENGTH] = {0};
	int new_population[POPULATION_SIZE * CHROMOSOME_LENGTH] = {0};
	int parent_1[POPULATION_SIZE] = {POPULATION_SIZE + 1};
	int parent_2[POPULATION_SIZE] = {POPULATION_SIZE + 1};

	if(sodium_init() == -1)
	{
		return 1;
	}


	/* Generate random population*/
	for(int i = 0; i < POPULATION_SIZE; i++)
	{
		for( int j = 0; j < CHROMOSOME_LENGTH; j++)
		{
			population[calculate_chromosome(CHROMOSOME_LENGTH, i, j)] = (randombytes_uniform(100)-50); /*random number b/w -50 and 50*/
		}
	}

	
	for(int i = 0; i < POPULATION_SIZE; i++)
	{
		population_fitness[i] = (double)(population[calculate_chromosome(CHROMOSOME_LENGTH, i, 0)]/*a*/ 
		+ 30 * pow(population[calculate_chromosome(CHROMOSOME_LENGTH, i, 1)], 2) * population[calculate_chromosome(CHROMOSOME_LENGTH, i, 2)]/*+30b^2c*/ 
		- 2 * pow(population[calculate_chromosome(CHROMOSOME_LENGTH, i, 3)],3) * pow(population[calculate_chromosome(CHROMOSOME_LENGTH, i, 4)],2) /*-2de*/
		+ 2 * population[calculate_chromosome(CHROMOSOME_LENGTH, i, 5)]/*2f*/ - 2567);
		/* calculate fitness function (a+30b^2c-2d^3e^2+2f) - 2567*/
	}

	bool soln_found = false;
	double best_fitness = DBL_MAX;
	int best_fitness_index_counter = 0;
	int best_fitness_soln[CHROMOSOME_LENGTH] = {0};

	while (soln_found == false)
	{
		//calc fitness function
		for(int i = 0; i < POPULATION_SIZE; i++)
		{
			population_fitness[i] = (double)(population[calculate_chromosome(CHROMOSOME_LENGTH, i, 0)]/*a*/ 
			+ 30 * pow(population[calculate_chromosome(CHROMOSOME_LENGTH, i, 1)], 2) * population[calculate_chromosome(CHROMOSOME_LENGTH, i, 2)]/*+30b^2c*/ 
			- 2 * pow(population[calculate_chromosome(CHROMOSOME_LENGTH, i, 3)],3) * pow(population[calculate_chromosome(CHROMOSOME_LENGTH, i, 4)],2) /*-2de*/
			+ 2 * population[calculate_chromosome(CHROMOSOME_LENGTH, i, 5)]/*2f*/ - 2567);
			/* calculate fitness function (a+30b^2c-2d^3e^2+2f) - 2567*/
			
			printf("Fitness gen %d row %d: %lf\n", generation, i, population_fitness[i]);
			if(fabs(population_fitness[i]) < fabs(best_fitness))
			{
				best_fitness = population_fitness[i];
				for(int j = 0; j< CHROMOSOME_LENGTH; j++)
				{
					best_fitness_soln[j] = population[i * CHROMOSOME_LENGTH + j];
				}
			}
			else if(population_fitness[i] == best_fitness)
			{
				best_fitness_index_counter++;
			}
		}

		//check if soln found
		if (best_fitness == 0 || best_fitness_index_counter == 10)
		{
			soln_found = true;
		}

		//tournament selection
		for(int i = 0; i < POPULATION_SIZE; i++)
		{
			int k = randombytes_uniform(POPULATION_SIZE);
			int l = randombytes_uniform(POPULATION_SIZE);
			if(fabs(population_fitness[k]) < fabs(population_fitness[l]))
			{
				parent_1[i] = k;
			}
			else
			{
				parent_1[i] = l;
			}	

			int m = randombytes_uniform(POPULATION_SIZE);
			int n = randombytes_uniform(POPULATION_SIZE);
			if(fabs(population_fitness[m]) < fabs(population_fitness[n]))
			{
				parent_2[i] = m;
			}
			else
			{
				parent_2[i] = n;
			}	
		}
		
		//crossover
		for(int i = 0; i < POPULATION_SIZE; i+=2)
		{
			for(int j = 0; j < 3; j++)
			{
				new_population[calculate_chromosome(CHROMOSOME_LENGTH, i, j)] = population[calculate_chromosome(CHROMOSOME_LENGTH, parent_1[i], j)]; //1st offspring first 3 genes from 1st parent first 3 genes
				new_population[calculate_chromosome(CHROMOSOME_LENGTH, i, 5-j)] = population[calculate_chromosome(CHROMOSOME_LENGTH, parent_2[i + 1], (5-j))]; //first offspring last 3 genes from 2nd parent last 3 genes
			}

			for(int k = 0; k < 3; k++)
			{
				new_population[calculate_chromosome(CHROMOSOME_LENGTH, i+1, k)] = population[calculate_chromosome(CHROMOSOME_LENGTH, parent_2[i+1], k)]; //second offspring first 3 genes from 2nd parent first 3
				new_population[calculate_chromosome(CHROMOSOME_LENGTH, i+1, 5-k)] = population[calculate_chromosome(POPULATION_SIZE, parent_1[i+1], 5-k)]; //2nd offsoring last 3 from 1st parent last 3
			}
		}
		
		// mutation
		for(int i = 0; i < POPULATION_SIZE; i++)
		{
			int random_gene = randombytes_uniform(6);
			int random_mutation = (randombytes_uniform(10) - 5); /*random mutation between -5 and 5*/
			new_population[calculate_chromosome(CHROMOSOME_LENGTH, i, random_gene)] += random_mutation;
		}

		for(int i = 0; i < POPULATION_SIZE; i++)
		{
			for(int j = 0; j < 6; j++)
			{
				population[calculate_chromosome(CHROMOSOME_LENGTH, i, j)] = new_population[calculate_chromosome(CHROMOSOME_LENGTH, i, j)];
			}
		}

		generation++;

		
	}
	printf("generation: %d\n", generation);
	printf("solution: a, b, c, d, e, f\n");
	for(int i = 0; i< CHROMOSOME_LENGTH; i++)
	{
		printf("%d  ", best_fitness_soln[i]);
	}
}


bool check_fitness_zero(double population_fitness[30]) // TODO: change to use pointer and add population size arg
{
	for(int i = 0; i < 30; i++)
	{
		if(population_fitness[i] == 0)
		{
			return true;
		}
	}
	return false;
}


int calculate_chromosome(int row_size, int row, int col)
{
	int chromosome = row * row_size + col;
	return chromosome;
}