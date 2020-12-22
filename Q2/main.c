/*
INSTRUCTIONS:
This file must include only the main function
The main function should print out the various cases
and finally print out tables showing the performance
of various policies with the different workloads.
Vary the cache size.

You may include a function or 2 to ease the printing of tables.

*/

#include<stdio.h>
#include "definitions.h"
#include "policy.c"
#include "workload.c"

int main()
{
	int pages = 100;
	int cache_size=1;
	int size = 1000;

	char *local = "local.csv";
	char *random = "random.csv";
	char *loop = "loop.csv";
	
	WorkloadsT type1 = LOCAL;
	WorkloadsT type2 = RANDOM;
	WorkloadsT type3 = LOOP;

	FILE *localf = fopen(local,"w+");
	FILE *randomf = fopen(random,"w+");
	FILE *loopf = fopen(loop,"w+");
	
	fprintf(loopf,"cache_size, hit_rate");
	fprintf(localf,"cache_size, hit_rate");
	fprintf(randomf,"cache_size, hit_rate");

		struct workload *w1 = (struct workload*)malloc(sizeof(struct workload));
		w1->pages =  pages;
		w1->size = size;



float output;

for(int i=1; i<=pages; i++){

///////////// Checking for the FIFO ////////////////////////////
		fprintf(localf,"\n");
		fprintf(loopf,"\n");
		fprintf(randomf,"\n");
		w1->type = LOCAL;
		w1 = generate_workload(w1->type,pages,size);
		output = policy_FIFO(w1,i);
		fprintf(localf,"%d,%f",i,output);

		free(w1->work);
		w1->type = RANDOM;
		w1 = generate_workload(w1->type,pages,size);
		output = policy_FIFO(w1,i);
		fprintf(randomf,"%d,%f",i,output);


		free(w1->work);
		w1->type = LOOP;
		w1 = generate_workload(w1->type,pages,size);
		output = policy_FIFO(w1,i);
		fprintf(loopf,"%d,%f",i,output);

////////////////////////////////////////////////////////////
}


for(int i=1; i<=pages; i++){
////////////////////checking for LRU exact /////////////////////////////
		fprintf(localf,"\n");
		fprintf(loopf,"\n");
		fprintf(randomf,"\n");

		free(w1->work);
		w1->type = LOOP;
		w1 = generate_workload(w1->type,pages,size);
		output = policy_LRU(w1,i);
		fprintf(loopf,"%d,%f",i,output);

		free(w1->work);
		w1->type =RANDOM;
		w1 = generate_workload(w1->type,pages,size);
		output = policy_LRU(w1,i);
		fprintf(randomf,"%d,%f",i,output);
		
		free(w1->work);
		w1->type = LOCAL;
		w1 = generate_workload(w1->type,pages,size);
		output = policy_LRU(w1,i);
		fprintf(localf,"%d,%f",i,output);
////////////////////////////////////////////////////////////////////
}

for(int i=1; i<=pages; i++){
///////////// Checking for the Random ////////////////////////
		fprintf(localf,"\n");
		fprintf(loopf,"\n");
		fprintf(randomf,"\n");
		free(w1->work);
		w1->type = LOOP;
		w1 = generate_workload(w1->type,pages,size);
		output = policy_RANDOM(w1,i);
		fprintf(loopf,"%d,%f",i,output);

		free(w1->work);
		w1->type =RANDOM;
		w1 = generate_workload(w1->type,pages,size);
		output = policy_RANDOM(w1,i);
		fprintf(randomf,"%d,%f",i,output);
		
		free(w1->work);
		w1->type = LOCAL;
		w1 = generate_workload(w1->type,pages,size);
		output = policy_RANDOM(w1,i);
		fprintf(localf,"%d,%f",i,output);


//////////////////////////////////////////////////////////////
}
for(int i=1; i<=pages; i++){
///////////////Checking for the LRUapprox/////////////////////////
		fprintf(localf,"\n");
		fprintf(loopf,"\n");
		fprintf(randomf,"\n");		
		
		free(w1->work);
		w1->type = LOOP;
		w1 = generate_workload(w1->type,pages,size);
		output = policy_LRUapprox(w1,i);
		fprintf(loopf,"%d,%f",i,output);

		free(w1->work);
		w1->type =RANDOM;
		w1 = generate_workload(w1->type,pages,size);
		output = policy_LRUapprox(w1,i);
		fprintf(randomf,"%d,%f",i,output);
		
		free(w1->work);
		w1->type = LOCAL;
		w1 = generate_workload(w1->type,pages,size);
		output = policy_LRUapprox(w1,i);
		fprintf(localf,"%d,%f",i,output);

//////////////////////////////////////////////////////////////

}




























	return 0;
}