#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>
#include<string.h>
#include "trie.h"

// Here _trie_node_t is the node itself
// trie_node_t is a pointer to _trie_node_t

//_trie_t is basically encapsulating the trie_node_t(pointer to actual node) in it.
                                        
// trie_t is basically the pointer to _trie_t 


// trie_node_t creat_node(){
//     trie_node_t t1 = (trie_node_t)malloc(sizeof(_trie_node_t));
//     t1->is_end = false;
//     t1->value = -101;
//     for(int i=0; i<26; i++){
//         t1->children[i] = NULL;
//     }
//     pthread_mutex_init(&t1->node_lock,NULL);
//     return t1;

// }


#ifdef _S_LOCK_TRIE
#ifdef _NO_HOH_LOCK_TRIE
// For the S_lock

trie_t init_trie(void){
    printf("\n\n\n\nEntered into the s_lock\n\n\n\n");
    // Write your code here
    // Here we will just return the root node

    // defining the inner contents 
   
    trie_node_t t1 = (trie_node_t)malloc(sizeof(_trie_node_t));
    t1->is_end = false;
    t1->value =-101;
    for(int i=0; i<26; i++){
        t1->children[i] = NULL;
    }
    
    // pthread_mutex_init(&t1->node_lock,NULL);


    trie_t t2 = (trie_t)malloc(sizeof(_trie_t));
    pthread_mutex_init(&t2->total_lock,NULL); 

    t2->head = t1;    
   
    return t2;
} 


void insert(trie_t trie, char* key, int value){
    // Write your code here
    
    pthread_mutex_lock(&trie->total_lock);
    
    trie_node_t head = trie->head;
    // insert_helper(head,key,value);
    trie_node_t temp = head;
    
    for(int i=0; i<strlen(key); i++){
        int index = key[i] - 'a';
        if(temp->children[index]==NULL){
            temp->children[index] = (trie_node_t)malloc(sizeof(_trie_node_t));
            temp->children[index]->is_end = false;
            temp->children[index]->value = -101;
            for(int j=0; j<26; j++){
                temp->children[index]->children[j] = NULL;
            }
        }
        temp = temp->children[index];
        
    }

    temp->is_end = true;
    temp->value = value;
    pthread_mutex_unlock(&trie->total_lock);
}

int find(trie_t trie,char* key, int* val_ptr){
    // Write your code here
    pthread_mutex_lock(&trie->total_lock);
    trie_node_t t1 = trie->head;
    trie_node_t temp = t1;

    for(int i=0; i<strlen(key);i++){
        int index = key[i] -'a';
        if(temp->children[index]==NULL){
            pthread_mutex_unlock(&trie->total_lock);
            return -1;
        }
        else{
            temp = temp->children[index];
        }
    }

    if(temp->value!=-101){
    *val_ptr = temp->value;
    pthread_mutex_unlock(&trie->total_lock);
    return 0;
    }

    pthread_mutex_unlock(&trie->total_lock);
    return -1;
    
} 

void delete_kv(trie_t trie, char* key){
    // Write your code here
pthread_mutex_lock(&trie->total_lock);
    trie_node_t t1 = trie->head;
    trie_node_t temp = t1;


    for(int i=0; i<strlen(key);i++){
        int index = key[i] -'a';
        if(temp->children[index]==NULL){
            pthread_mutex_unlock(&trie->total_lock);
            return;
        }
        else{
            temp = temp->children[index];
        }
    }

    temp->is_end = false;

pthread_mutex_unlock(&trie->total_lock);


}

void add_word(char *word, int pos, char ***list, int *ind){
    (*list)[*ind] = (char *)malloc((pos+1)*sizeof(char));
    for(int i=0; i<pos; i++){
        (*list)[*ind][i] = word[i];
    }
    (*list)[*ind][pos] = '\0';
    (*ind)++;
    
}

void all_word_iterate(trie_node_t root, char *word, int pos,char ***list,int *ind){
    if(root==NULL)
        return;
    if(root->is_end==true){
        add_word(word,pos,list,ind);
    }
    for(int i=0; i<26; i++){
        if(root->children[i]!=NULL){
            char c = i+ 'a';
            word[pos] = c;
            all_word_iterate(root->children[i],word,pos+1,list,ind);
        }
    }

}

char** keys_with_prefix(trie_t trie, char* prefix){
    // Write your code here
    pthread_mutex_lock(&trie->total_lock);

    char** list = malloc(1000*sizeof(char*));
    // list[0]
    for(int i=0; i<1000; i++){
        list[i] = NULL;
    }

    trie_node_t temp = trie->head;
    

    for(int i=0; i<strlen(prefix); i++){
        int index = prefix[i] -'a';
        if(temp->children[index]==NULL){
            pthread_mutex_unlock(&trie->total_lock);
            return list;
        }
        else{
            temp = temp->children[index];
        }
    
    }
    char *word = malloc(50*sizeof(char));
    strcpy(word,prefix);
    int ind =0;
    all_word_iterate(temp,word,strlen(prefix),&list,&ind);


    free(word);
    pthread_mutex_unlock(&trie->total_lock);
    return list;
    // return NULL;
}

void delete_helper(trie_node_t temp){
    for(int i=0; i<26; i++){
        if(temp->children[i]!=NULL){
            delete_helper(temp->children[i]);
        }
    }
    free(temp);
}
void delete_trie(trie_t trie){
    // Write your code here
    // pthread_mutex_lock(&trie->total_lock);
    trie_node_t temp = trie->head; 
    delete_helper(temp);
    // pthread_mutex_unlock(&trie->total_lock);
    trie->head = NULL;
    free(trie);
}
#endif
#endif

#ifdef _NO_HOH_LOCK_TRIE
#ifndef _S_LOCK_TRIE
// For the rw_lock
trie_t init_trie(void){
    printf("\n\n\n\nEntered into the rw_lock\n\n\n\n");
    // Write your code here
    // Here we will just return the root node

    // defining the inner contents 
   
    trie_node_t t1 = (trie_node_t)malloc(sizeof(_trie_node_t));
    t1->is_end = false;
    t1->value =-101;
    for(int i=0; i<26; i++){
        t1->children[i] = NULL;
    }
    
    // pthread_mutex_init(&t1->node_lock,NULL);


    trie_t t2 = (trie_t)malloc(sizeof(_trie_t));
    // pthread_mutex_init(&t2->total_lock,NULL); 
    pthread_rwlock_init(&t2->total_lock,NULL);

    t2->head = t1;    
   
    return t2;
} 


void insert(trie_t trie, char* key, int value){
    // Write your code here
    
    pthread_rwlock_wrlock(&trie->total_lock);
    
    trie_node_t head = trie->head;
    // insert_helper(head,key,value);
    trie_node_t temp = head;
    
    for(int i=0; i<strlen(key); i++){
        int index = key[i] - 'a';
        if(temp->children[index]==NULL){
            temp->children[index] = (trie_node_t)malloc(sizeof(_trie_node_t));
            temp->children[index]->is_end = false;
            temp->children[index]->value = -101;
            for(int j=0; j<26; j++){
                temp->children[index]->children[j] = NULL;
            }
        }
        temp = temp->children[index];
        
    }

    temp->is_end = true;
    temp->value = value;
    pthread_rwlock_unlock(&trie->total_lock);
}

int find(trie_t trie,char* key, int* val_ptr){
    // Write your code here
    pthread_rwlock_rdlock(&trie->total_lock);
    trie_node_t t1 = trie->head;
    trie_node_t temp = t1;

    for(int i=0; i<strlen(key);i++){
        int index = key[i] -'a';
        if(temp->children[index]==NULL){
            pthread_rwlock_unlock(&trie->total_lock);
            return -1;
        }
        else{
            temp = temp->children[index];
        }
    }

    if(temp->value!=-101){
    *val_ptr = temp->value;
    pthread_rwlock_unlock(&trie->total_lock);
    return 0;
    }

    pthread_rwlock_unlock(&trie->total_lock);
    return -1;
    
} 

void delete_kv(trie_t trie, char* key){
    // Write your code here
    pthread_rwlock_wrlock(&trie->total_lock);
    trie_node_t t1 = trie->head;
    trie_node_t temp = t1;


    for(int i=0; i<strlen(key);i++){
        int index = key[i] -'a';
        if(temp->children[index]==NULL){
            pthread_rwlock_unlock(&trie->total_lock);
            return;
        }
        else{
            temp = temp->children[index];
        }
    }

    temp->is_end = false;

pthread_rwlock_unlock(&trie->total_lock);


}

void add_word(char *word, int pos, char ***list, int *ind){
    (*list)[*ind] = (char *)malloc((pos+1)*sizeof(char));
    for(int i=0; i<pos; i++){
        (*list)[*ind][i] = word[i];
    }
    (*list)[*ind][pos] = '\0';
    (*ind)++;
    
}

void all_word_iterate(trie_node_t root, char *word, int pos,char ***list,int *ind){
    if(root==NULL)
        return;
    if(root->is_end==true){
        add_word(word,pos,list,ind);
    }
    for(int i=0; i<26; i++){
        if(root->children[i]!=NULL){
            char c = i+ 'a';
            word[pos] = c;
            all_word_iterate(root->children[i],word,pos+1,list,ind);
        }
    }

}

char** keys_with_prefix(trie_t trie, char* prefix){
    // Write your code here
    pthread_rwlock_rdlock(&trie->total_lock);
    char** list = malloc(1000*sizeof(char*));
    // list[0]
    for(int i=0; i<1000; i++){
        list[i] = NULL;
    }

    trie_node_t temp = trie->head;
    

    for(int i=0; i<strlen(prefix); i++){
        int index = prefix[i] -'a';
        if(temp->children[index]==NULL){
            pthread_rwlock_unlock(&trie->total_lock);
            return list;
        }
        else{
            temp = temp->children[index];
        }
    
    }
    char *word = malloc(50*sizeof(char));
    strcpy(word,prefix);
    int ind =0;
    all_word_iterate(temp,word,strlen(prefix),&list,&ind);


    free(word);
    pthread_rwlock_unlock(&trie->total_lock);
    return list;
    // return NULL;
}

void delete_helper(trie_node_t temp){
    for(int i=0; i<26; i++){
        if(temp->children[i]!=NULL){
            delete_helper(temp->children[i]);
        }
    }
    free(temp);
}
void delete_trie(trie_t trie){
    // Write your code here
    // pthread_mutex_lock(&trie->total_lock);
    trie_node_t temp = trie->head; 
    delete_helper(temp);
    // pthread_mutex_unlock(&trie->total_lock);
    trie->head = NULL;
    free(trie);
}

#endif
#endif



#ifndef _NO_HOH_LOCK_TRIE
//For the HOH lock

trie_t init_trie(void){
    printf("\n\n\n\nEntered into the hoh_lock\n\n\n\n");
    // Write your code here
    // Here we will just return the root node

    // defining the inner contents 
    trie_node_t t1 = (trie_node_t)malloc(sizeof(_trie_node_t));
   
    t1->is_end = false;
    t1->value =-101;
    pthread_mutex_init(&t1->node_lock,NULL);
    for(int i=0; i<26; i++){
        t1->children[i] = NULL;
    }
    
    // pthread_mutex_init(&t1->node_lock,NULL);


    trie_t t2 = (trie_t)malloc(sizeof(_trie_t));

    t2->head = t1;    
    
    return t2;
} 


void insert(trie_t trie, char* key, int value){
    // Write your code here
    // pthread_mutex_lock(&p1);
    trie_node_t t1;

    pthread_mutex_lock(&trie->head->node_lock);    
    trie_node_t head = trie->head;
    // insert_helper(head,key,value);
    trie_node_t temp = head;
    pthread_mutex_unlock(&trie->head->node_lock);

    pthread_mutex_lock(&temp->node_lock);
    for(int i=0; i<strlen(key); i++){
        t1 = temp;
        int index = key[i] - 'a';
        if(temp->children[index]==NULL){
            temp->children[index] = (trie_node_t)malloc(sizeof(_trie_node_t));
            
            pthread_mutex_init(&temp->children[index]->node_lock,NULL);
            pthread_mutex_lock(&temp->children[index]->node_lock);
            temp->children[index]->is_end = false;
            temp->children[index]->value = -101;
            
            for(int j=0; j<26; j++){
                temp->children[index]->children[j] = NULL;
            }
        }
        else{
           
            pthread_mutex_lock(&temp->children[index]->node_lock);
        }
 
        temp = temp->children[index];
        pthread_mutex_unlock(&t1->node_lock);
      
    }
    temp->is_end = true;
    temp->value = value;
    pthread_mutex_unlock(&temp->node_lock);
    
}

int find(trie_t trie,char* key, int* val_ptr){
    // Write your code here
    

    pthread_mutex_lock(&trie->head->node_lock);    
    trie_node_t head = trie->head;
    // insert_helper(head,key,value);
    trie_node_t temp = head;
    pthread_mutex_unlock(&trie->head->node_lock);

    
    pthread_mutex_lock(&temp->node_lock);
    for(int i=0; i<strlen(key);i++){
        int index = key[i] -'a';
        if(temp->children[index]==NULL){
            pthread_mutex_unlock(&temp->node_lock);
            return -1;
        }
        else{ 
            pthread_mutex_lock(&temp->children[index]->node_lock);
            trie_node_t t11 = temp;
            temp = temp->children[index];
            pthread_mutex_unlock(&t11->node_lock);
        }
    }


    
    if(temp->value!=-101){
    *val_ptr = temp->value;
    pthread_mutex_unlock(&temp->node_lock);
    return 0;
    }

    pthread_mutex_unlock(&temp->node_lock);
    return -1;
    
} 

void delete_kv(trie_t trie, char* key){
    // Write your code here

    trie_node_t t1 = trie->head;
    trie_node_t temp = t1;

    pthread_mutex_lock(&temp->node_lock);
    for(int i=0; i<strlen(key);i++){
        int index = key[i] -'a';
        if(temp->children[index]==NULL){
            pthread_mutex_unlock(&temp->node_lock);
            return;
        }
        else{
            pthread_mutex_lock(&temp->children[index]->node_lock);
            trie_node_t t11 = temp;
            temp = temp->children[index];
            pthread_mutex_unlock(&t11->node_lock);
        }
    }
    
    temp->is_end = false;
    pthread_mutex_unlock(&temp->node_lock);




}

void add_word(char *word, int pos, char ***list, int *ind){
    (*list)[*ind] = (char *)malloc((pos+1)*sizeof(char));
    for(int i=0; i<pos; i++){
        (*list)[*ind][i] = word[i];
    }
    (*list)[*ind][pos] = '\0';
    (*ind)++;
    
}

void all_word_iterate(trie_node_t root, char *word, int pos,char ***list,int *ind){
    if(root==NULL)
        return;

    
    if(root->is_end==true){
        add_word(word,pos,list,ind);
    }
    for(int i=0; i<26; i++){
        if(root->children[i]!=NULL){
            char c = i+ 'a';
            word[pos] = c;
            all_word_iterate(root->children[i],word,pos+1,list,ind);
        }
    }
  

}

char** keys_with_prefix(trie_t trie, char* prefix){
    // Write your code here
 

    char** list = malloc(1000*sizeof(char*));
    // list[0]
    for(int i=0; i<1000; i++){
        list[i] = NULL;
    }

    trie_node_t temp = trie->head;
    

    for(int i=0; i<strlen(prefix); i++){
        int index = prefix[i] -'a';
        
        if(temp->children[index]==NULL){
            pthread_mutex_unlock(&temp->node_lock);
            return list;
        }
        else{
            
            temp = temp->children[index];
            
        }
    
    }
    char *word = malloc(50*sizeof(char));
    strcpy(word,prefix);
    int ind =0;
    all_word_iterate(temp,word,strlen(prefix),&list,&ind);


    free(word);
    
    return list;
    // return NULL;
}



void delete_helper(trie_node_t temp){
    pthread_mutex_lock(&temp->node_lock);
    for(int i=0; i<26; i++){
        if(temp->children[i]!=NULL){
            delete_helper(temp->children[i]);
        }
    }
    pthread_mutex_unlock(&temp->node_lock);
    free(temp);
}


void delete_trie(trie_t trie){
    // Write your code here
    
    trie_node_t temp = trie->head;

    trie->head = NULL;

    free(trie);
    delete_helper(temp);
    
}

#endif