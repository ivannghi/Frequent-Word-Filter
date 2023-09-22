#include "hashtable.h"
#define HASHSIZE 1001

static node *hashtable[HASHSIZE]; /* pointer table */
int unique_words;
int num_of_top_words;
static NodePtr *word_array;

char *strdup(char *s){
	char *p;
	
	p = (char *) malloc(strlen(s) + 1);
	if (p != NULL){
		strcpy(p,s);
	}
	return p;
}

unsigned hash(char *str){
	unsigned hashval;
	
	for(hashval = 0; *str != '\0'; str++){
		hashval = *str + 31 * hashval;
	}
	return hashval % HASHSIZE;
}


node *lookup(char *s){
	NodePtr np;
	
	for (np = hashtable[hash(s)]; np != NULL; np = np->next){
		if(!strcmp(s, np->word)){	
			return np;   /*found*/
		}
	}
	return NULL;             /*not found*/
}


node *install(char *word){
	NodePtr np;
	unsigned hashval;

	if ((np = lookup(word)) == NULL){
		np = (NodePtr) malloc(sizeof(node));
		if (np == NULL || (np->word = strdup(word)) == NULL){
			return NULL;
		}
		unique_words++;
		hashval = hash(word);
		np->next = hashtable[hashval];
		np->frequency = 1;
		hashtable[hashval] = np;
		
	} else{
		np->frequency++;
	}
	return np;

}

void hash_table_to_array(){
	int hashtable_index;
	
	NodePtr np;
	int array_index = 0;

	word_array = (NodePtr*) malloc(unique_words * sizeof(node *));  
	
	for(hashtable_index = 0; hashtable_index < HASHSIZE; hashtable_index++){
		if((np = hashtable[hashtable_index]) != NULL){
			while(np->next != NULL){
				*(word_array + array_index) = np;
				array_index++;
				np = np->next;
				
			}
			*(word_array + array_index) = np;
			array_index++;
		}
	}
}

void swap_new(NodePtr v[], int i, int j){
        NodePtr temp;

        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
        return;
}


void qsort_new(NodePtr v[], int left, int right){
        int i, last;

        if(left >= right){
        return;
        }
        swap_new(v, left, (left+right)/2);
        last = left;
        for(i = left+1; i <= right; i++){
                
		if((v[i]->frequency) == (v[left]->frequency)){
			if(strcmp(v[i]->word, v[left]->word) > 0){
				swap_new(v, ++last, i);
			}
		}
		else if((v[i]->frequency) > (v[left]->frequency)){
                        swap_new(v, ++last, i);
                }
        }
        swap_new(v, left, last);
        qsort_new(v, left, last-1);
        qsort_new(v, last+1, right);

        return;
}


void free_mallocs(){
	int i = 0;
	NodePtr np;
	for(i = 0; i < unique_words; i++){
		np = word_array[i];
		free(np->word);
		free(np);
	}
	free(word_array);
}


void print_array2(){
        int array_index = 0;
	NodePtr np;
	qsort_new(word_array, 0, unique_words - 1); 
	if(num_of_top_words > unique_words){
		num_of_top_words = unique_words;
	}
	for (array_index = 0; array_index < num_of_top_words; array_index++){
                np = *(word_array + array_index);
                printf("%9d %s\n", np->frequency, np->word);
        }
}
