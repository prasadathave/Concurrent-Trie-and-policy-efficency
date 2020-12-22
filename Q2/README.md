# Assignment 2 Question 2

In this question, complete individual files and implement in C and compare the various policies for caching. 

**Do not change or remove the already defined functions and the defined functions should behave according to the given instructions.**

You will be implementing: 

Policies: LRU (exact and approx), FIFO, Random
Workloads: 80-20, looping, random

1. Add required header files in each of the files and mention why they are required.
2. The makefile given this time is empty. Complete it!
3. Read the instructions given in each file.
4. If you add any extra function, do not forget to mention it in definitions header file.
5. Add comments to describe what is going on in each function.
6. The work in workload corresponds to a the sequence of pages where each page is represented by an integer.

*Note: In the code, 80-20 is mentioned as local.*

For checking, compile your code with checker.c in place of main.c

Make an entry in makfile that will compile with checker file when `make tests` is done.



Note - For running the file and directly seeing the plots just type make command



Performance and analysis of each policy -

1. FIFO- It needs to remember the order of pages entered into the cache. It is highly ineffective in the case of loop data. It takes O(cache_size) space and also the O(n) time in worst case. Where n is the number of pages stored currently.
2. LRU approx - It also takes O(cahce_size) space and also the O(n) time in the worst case. Where n is the number of pages stored currently.
But its performance is way better than the FIFO due to the consideration of frequency of usage.
3. LRU - similar to LRU approx 
4. Random - It is very cheap in terms of memory and time as it takes O(1) space and O(n) time in worst cases. But it has low efficiency.


Here are the images of their performance

![plot](./images/localdata.png)

![plot](./images/loopdata.png)
![plot](./images/randomdata.png)

