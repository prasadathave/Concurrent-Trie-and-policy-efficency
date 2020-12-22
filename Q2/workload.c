/*
INSTRUCTIONS:

This file will contain all the functions related to the generation of workload

*/

#include "definitions.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

// Note: The work must be generated for the returned pointer
struct workload * generate_workload(WorkloadsT type, int pages, int size)
{
    struct workload *win  = (struct workload*) malloc(sizeof(struct workload));
    struct workload *wout;

    win->pages = pages;
    win->size = size;

    if(type==LOOP){
        win->type = LOOP;
        wout = generate_loop(win);
        // printf("Workload for Loop");
    }
    else if(type==LOCAL){
        win->type = LOCAL;
        wout = generate_local(win);
        // printf("Worklaod for Local");
    }
    else if(type==RANDOM){
        win->type = RANDOM;
        wout = generate_random(win);
        // printf("Workload for Random");
    }
    else{
        // printf("Input is not proper");
    }
    
    return wout;
}

struct workload * generate_random(struct workload * w)
{
    w->work = (int *)malloc(w->size*sizeof(int));
    for(int i=0; i<w->size; i++){
        w->work[i] = rand()%(w->pages);
    }

    return w;
}

struct workload * generate_loop(struct workload * w)
{   int p = w->pages/2;
    w->work = (int *)malloc(w->size*sizeof(int));

    for(int i=0; i<w->size; i++){
        w->work[i] = (i%p);
    }
    return w;


}

struct workload* generate_local(struct workload * w)
{

    int a = 0.8*w->pages;
    w->work = (int *)malloc(w->size*sizeof(int));
    int b = w->pages - a;

    for(int i=0;i<w->size;i++){
        if (i< 0.8*w->size)
        {
            w->work[i]=(rand()%(b));
        }
        else{
            w->work[i]=(rand() % (w->pages - b + 1)) + b;
        } 
    }

    return w;


}



