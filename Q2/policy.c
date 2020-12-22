/* INSTRUCTIONS:

This file will contain all functions related with various policies.
Each policy must return the hit rate

*/

#include "definitions.h"
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>



////////////////Hashmap for the absolute LRU ////////////

typedef struct ashmap{
int *key;
int *value;
int capacity;
int level;

} _Hashmap;


typedef _Hashmap* Hashmap;


Hashmap createHashmap(int capacity){
Hashmap hm = (Hashmap)malloc(sizeof(_Hashmap));
hm->capacity = capacity;
hm->key = (int *)malloc(capacity*sizeof(int));
hm->value = (int *)malloc(capacity*sizeof(int));
hm->level =0;
for(int i=0; i<capacity; i++){
	hm->key[i] = -11;
	hm->value[i] = -11;
}

return hm;

}

int isHEmpty(Hashmap mp){
if(mp->level==0){
	return 1;
}
else{
	return 0;
}

}

int isHFull(Hashmap hm){
	if(hm->level==hm->capacity)
	{
		return 1;
	}
	return 0;
}

int insert(Hashmap hm,float total,int key){
	
	for(int i=0; i<hm->capacity; i++){
		if(hm->key[i]==key){
			// hm->value[i]++;
			int x = (int) total;
			hm->value[i] = x;
			// printf("\n x here is %d\n",x);
			return 1;
		}
	}


	for(int i=0; i<hm->capacity; i++){
		if(hm->key[i]==-11){
			hm->key[i] = key;
			int x = (int) total;
			hm->value[i] = x;
			hm->level++;
	
			return 0;
		}
	}
	return -1;
}


void removemin(Hashmap mp){
	int min =INT_MAX;
	int mini =0;
	for(int i=0; i<mp->capacity; i++){
		if(mp->value[i]!=-11 &&  mp->value[i]<min){
			min = mp->value[i];
			mini = i;
		}
	}
	// printf("\nremoved %d\n",mini);
	mp->key[mini] = -11;
	mp->value[mini] = -11;
	mp->level--;
}



/////////////////////////////////////////////////




//// Queue for the FIFO /////////////////////////////////////
typedef struct qq{
	int front, rear,size;
	int capacity;
	int *arr;
} _Queue;

typedef _Queue* Queue;

Queue createQueue(int capacity) 
{ 
    Queue queue = (Queue)malloc( 
        sizeof(_Queue)); 
    queue->capacity = capacity; 
    queue->front = queue->size = 0; 
  
    // This is important, see the enqueue 
    queue->rear = capacity - 1; 
    queue->arr = (int*)malloc( 
        queue->capacity * sizeof(int)); 
    return queue; 
} 
int isFull(Queue queue) 
{ 
    return (queue->size == queue->capacity); 
} 
int isthere(Queue queue, int x){
	for(int i=queue->rear; i<=queue->front; i++){
		if(queue->arr[i]==x){
			return 1;
		}
	}

	for(int i=queue->front; i<=queue->rear; i++){
		if(queue->arr[i]==x){
			return 1;
		}
	}
	return 0;

}

int isEmpty(Queue queue) 
{ 
    return (queue->size == 0); 
} 

void enqueue(Queue queue, int item) 
{ 
    if (isFull(queue)) 
        return; 
    queue->rear = (queue->rear + 1) 
                  % queue->capacity; 
    queue->arr[queue->rear] = item; 
    queue->size = queue->size + 1; 
    
} 
  
int dequeue(Queue queue) 
{ 
    if (isEmpty(queue)) 
        return -1000; 
    int item = queue->arr[queue->front]; 
    queue->front = (queue->front + 1) % queue->capacity; 
    queue->size = queue->size - 1; 
    return item; 
} 
 


/////////////////////////////////////////////////////////////



float policy_FIFO(struct workload* w, int cache_size)
{
	float hit_rate = 0;
	/* fill this */
	int miss=0;
	int hit =0;

	Queue q = createQueue(cache_size);
	for(int i=0; i<w->size; i++){
		if(isEmpty(q)){
			miss++;
			enqueue(q,w->work[i]);
		}
		else if(isthere(q,w->work[i])){
			hit++;
		}
		else if(isFull(q)){
			int l = dequeue(q);
			enqueue(q,w->work[i]);
			miss++;
		}
		else{
			enqueue(q,w->work[i]);
			miss++;
		}
	}
    // printf("\nHello world\n");
    float a = (float)hit;
    float b = (float)miss;
	hit_rate = a/(a+b);
    // printf("a :%f\nb: %f\n Hit rate: %f\n",a,b,hit_rate);

	return hit_rate;
}

float policy_LRU(struct workload * w, int cache_size)
{
	float hit_rate = 0;
	float total = 0;
	/* fill this */

	Hashmap mp = createHashmap(cache_size);

	for(int i=0; i<w->size; i++){
	if(isHFull(mp)==1){
		int l = insert(mp,total,w->work[i]);
		if(l==1){
			hit_rate++;
		}
		else if(l==-1){
			removemin(mp);
			int a = insert(mp,total,w->work[i]);
		}
	}
	else{
		if(insert(mp,total,w->work[i])==1){
			hit_rate++;
		}
	}
	
	total++;
}
	hit_rate = hit_rate/total;

    
	return hit_rate;
}

float policy_LRUapprox(struct workload * w, int cache_size)
{
	float hit_rate = 0;
	/* fill this */
	float total =0;
	int size =0;
	int arr[cache_size];
	int front =0;
	int rear =0;
	int clock =0;
	int tag[cache_size];
	for(int i=0; i<cache_size; i++){
		arr[i] = 0;
		tag[i] =0;
	}

	for(int i=0; i<w->size; i++){
		if(size==cache_size){
			int flg =0;
			for(int j=0; j<cache_size; j++){
				if(arr[j]==w->work[i]){
					tag[j]=1;
					flg =1;
					hit_rate++;
					break;
				}
			}

		if(flg == 0){
			while(tag[clock]!=0){
				tag[clock] =0;
				clock = (clock+1)%cache_size;
			}
			arr[clock] = w->work[i];
			tag[clock]=1;
			clock=(clock+1)%cache_size;			
		}
	}

	else{

		int x =0;
		for(int l=0; l<size; l++){
			if(arr[l]==w->work[i]){
				hit_rate++;
				x =1;
				break;
			}
		}
		if(x==0){
			arr[size] = w->work[i];
			tag[size] = 0;
			size++;
		}
	
	}
	total++;	
	}
	hit_rate = hit_rate/total;
	
	return hit_rate;
}



float policy_RANDOM(struct workload * w, int cache_size)
{
	float hit_rate = 0;
	float total =0;
	
	/* fill this */
	int arr[cache_size];
	for(int i=0; i<cache_size; i++){
		arr[i] = -11;
	}

	for(int i=0;i<w->size; i++){
		int flg =0;
		for(int j=0;j<cache_size; j++){
			if(arr[j] == w->work[i]){
				hit_rate++;
				flg =1;
				break;
			}
		}

		if(flg==0){
			int x =0;

			for(int l=0; l<cache_size; l++){
				if(arr[l]==-11){
					arr[l]=w->work[i];
					x=1;
					break;
				}
			}

			if(x==0){
				int r = rand()%cache_size;
				arr[r] = w->work[i];
			}

		}
		total++;
	}
	 
	hit_rate = hit_rate/total;

	return hit_rate;
}
