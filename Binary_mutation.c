// using C language 
// OpenMP header 
#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

/* Write an openmp code in c for binary mutation of 10 binary chromosomes (each of length 10 bits).  */
int random_no(int lower,int upper)
{
	int num = (rand() % (upper - lower + 1)) + lower; 
	return num;
}

int main(int argc, char* argv[]) 
{ 
	int no_chromosomes = 10;
	int bits_chromosomes = 10;
	int chromosomes[no_chromosomes][bits_chromosomes];
	
	/* Parellism mainly focused in two regions one is initializing 
	and mutation in generation 
	*/
	// Beginning of parallel region 
	#pragma omp parallel num_threads(8)shared (chromosomes) firstprivate(no_chromosomes,bits_chromosomes)
	{ 
	
	#pragma omp for  schedule(dynamic,bits_chromosomes) //  dynamicly scheduling for loop with a chunk size of bits_chromosomes
	for (int i = 0;i<no_chromosomes;i++)
	{
		for (int j=0;j<bits_chromosomes;j++)
		{
		
		chromosomes[i][j] = random_no(0,1);
		
		}	
	}		
	#pragma omp for  schedule(dynamic,10) //  dynamicly scheduling for loop with a chunk size of 100
	for(int g =0;g<10;g++)
	{
		
		for (int i = 0;i<no_chromosomes;i++)
	{
		
		int j = random_no(0,10); // Randomly choosing two bits for mutation
		int k = random_no(0,10);
		// Mutation operation
		if(chromosomes[i][j] ==0)
			
			chromosomes[i][j] = 1;
		else
			chromosomes[i][0]=0;
		
		if(chromosomes[i][k] ==1)
			chromosomes[i][k] = 0;
		else
			chromosomes[i][k]=1;
			
	}
	int best=0;
	int sum =0;
	int index_i;
	
	for(int i=0;i<no_chromosomes;i++)
	{
		for(int j = 0;j<bits_chromosomes;j++)
		{
			
			sum = sum + chromosomes[i][j];			
		}
		if(sum >best )
		{
			best = sum;
			index_i = i;
			
		}
	}
	
	printf("\n%d th generation best chromosome: ",g+1);
	for(int j = 0;j<bits_chromosomes;++j)
		printf("%d",chromosomes[index_i][j]);
	}
	}
	// Ending of parallel region 
	
		
} 
