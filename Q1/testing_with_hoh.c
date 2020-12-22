#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include "trie.c"

trie_t trie;

void* insert_task(){
    // printf("\nstarted insert\n");
 
    char key[15];
    char *ins_file_name = "work.txt";
    FILE* ins_file = fopen(ins_file_name,"r");
    while(fgets(key,15, ins_file)) {
        // printf("inserting -%s\n",key);
        insert(trie,key,rand()%1000);
    }

    fclose(ins_file);
    // printf("Done insert");
    // pthread_exit(NULL);
    return NULL;
}


void* find_task(){
    // printf("\nStarted find\n");
    char key[15];
    char *find_test_name = "firstinsert.txt";
    FILE* find_test = fopen(find_test_name,"r");

   while(fgets(key,15, find_test)) {
    // printf("%s\n", key);
    int l = rand()%1000;
    int x = find(trie,key,&l);
    }
    fclose(find_test);
//    printf("\nend the find\n");
// pthread_exit(NULL);
    return NULL;
}



int main(){
    printf("\nentered the main\n");
    FILE* file;FILE *file2;
    char *word = NULL;
    size_t len = 15;
    ssize_t read;
    
    clock_t start_rd,end_rd,start_wr,end_wr,start_w,end_w;    
    trie = init_trie();
    int limit1 =40;
    file = fopen("firsinsert.txt","r");
    file2 = fopen("hohlock.csv","w");
    double data[100][3];
for(int no_threads =0; no_threads<=limit1; no_threads++){
    printf("loop started");
    pthread_t arr1[no_threads];
    start_rd = clock();
    // printf("%f",(double)start_rd);
    
    
    ////// write intensive ////
  
    for(int i=0; i<no_threads; i++){
        pthread_create(&arr1[i],NULL,&find_task,NULL);
    }

    for(int i=0; i<no_threads; i++){
        pthread_join(arr1[i],NULL);   
    }


    end_rd = clock();
    data[no_threads][0] = (double)(end_rd-start_rd);
    printf("firstdone");
////////////////////////////////
//////////////////read write ////////////////
    pthread_t arr2[no_threads];
    start_wr = clock();
    for(int i=0; i<no_threads; i++){
        if(i%2==0){
        pthread_create(&arr2[i],NULL,find_task,NULL);
        }
        else{
            pthread_create(&arr2[i],NULL,insert_task,NULL);
        }
    }
    for(int i=0; i<no_threads; i++){
        pthread_join(arr2[i],NULL);    
    }
    end_wr = clock();
    data[no_threads][1] = (double)(end_wr-start_wr);
///////////////////////////////////////////
    printf("second done");
//////////////////// read intensive /////////////////
    pthread_t arr3[no_threads];
    start_w = clock();
    for(int i=0; i<no_threads; i++){
        pthread_create(&arr3[i],NULL,&find_task,NULL);
    }

    for(int i=0; i<no_threads; i++){
        pthread_join(arr3[i],NULL);   
    }

    
    end_w = clock();
   
   data[no_threads][2] = (double)(end_w-start_w); 
    printf("thirddone");
    //////////////////////////////////////////
    fprintf(file2,"%d,%f,%f,%f\n",no_threads,data[no_threads][0],data[no_threads][1],data[no_threads][2]);
    printf("data added");

    printf("%d\n",no_threads);

    if(no_threads==limit1){
       
        pthread_exit(NULL);
    }

}


fclose(file);
fclose(file2);


return EXIT_SUCCESS;
}