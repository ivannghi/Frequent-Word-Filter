#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashtable.c"
#define BUFFER_SIZE 100

extern int unique_words;
int num_of_top_words = 10;

char * read_word(FILE *file){
	int size, ch, current_char_count = 0, flag = 1;
	unsigned char c;
	char * cptr;

	cptr = (char*)malloc(BUFFER_SIZE * sizeof(char) + 1);
	size = BUFFER_SIZE;

	ch = fgetc(file);
	while(flag){
		if(ch == EOF){
			flag = 0;
			free(cptr);
			return NULL;
		}

		c = (unsigned char) ch;
		c = tolower(c);
		if(current_char_count == size + 1){
			size = size + BUFFER_SIZE;
			cptr = (char*)realloc(cptr, size*sizeof(char) + 1);
		}

		if(isalpha(c)){
			*(cptr + current_char_count) = c;
			current_char_count++;
		} else{
			break;
		}

		ch = fgetc(file);
	}
	*(cptr + current_char_count) = '\0';
	return cptr;
}


int main(int argc, char ** argv){
	int current_arg_file = 1;
	int str_to_long, current_arg_count;
	FILE * fp = stdin;
	char *word;

	if (argc > 1){
		if (!strcmp(argv[1],"-n")){
			current_arg_file = 3;
			if (argc < 3 || (str_to_long = strtol(argv[2], 
							NULL, 10)) == 0){
				printf(
			"usage: fw [-n num] [ file1 [file 2 [...] ] ]\n");
				exit(0);
			} else{
			num_of_top_words = str_to_long;
			}
		}
	
		for (current_arg_count = argc - 1;
		 current_arg_count >= current_arg_file; current_arg_file ++){
			fp = fopen(argv[current_arg_file], "r");
			if (fp != NULL){
				while(1){
					word = read_word(fp);
					if (word == NULL){
						break;
					}
					if(strlen(word) > 0){
						install(word);
					}
					free(word);
				}
				fclose(fp);
			} else {
				perror(argv[current_arg_file]);
			}
		}
	} else {
		while(1){
			word = read_word(fp);
			if (word == NULL){
				break;
			}
			if(strlen(word) > 0){
  				install(word);
 			}
			free(word);
		}
	}



	hash_table_to_array();

	printf("The top %d words (out of %d) are:\n",
 		num_of_top_words, unique_words);
	
	print_array2();
	free_mallocs();		

	return 0;
}

