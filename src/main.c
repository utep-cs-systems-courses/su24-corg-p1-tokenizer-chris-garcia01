#include <stdio.h>
#include <string.h>
#include <string.h>
#include "tokenizer.h"
#include "history.h"

int is_digit(char c){
  return c >= '0' && c <= '9';
}

int aatoi(char *str){
  int result = 0;
  while(*str){
    if (*str >= '0' && *str <= '9'){
      result = result * 10 + (*str - '0');
    }else{
      break;
    }
    str++;
  }
  return result;
}

int main(void){
  char input[100];
  List *history = init_history();
  if(history == NULL){
    printf("Initialization of history failed.\n");
    return 1;
  }
  printf("Enter the string you want to tokenize.\n");
  printf("To view history, enter !followed by the history number (Example: !1).\n");
  
  while(1){
    printf("$ ");
    if (fgets(input, sizeof(input), stdin) != NULL){
      //Remove newline character from the end of the input
      input[strcspn(input, "\n")] = '\0';

      //checks if input calling for the history.
      if (input[0] == '!' && is_digit(input[1])){
	int id = aatoi(&input[1]);
	char *history_str = get_history(history, id);
	if (history_str != NULL){
	  printf("History [%d]: %s\n", id, history_str);
	  char **tokens = tokenize(history_str);
	  if(tokens != NULL){
	    print_tokens(tokens);
	    free_tokens(tokens);
	  }else{
	    printf("Tokenization of string failed.\n");
	  }
	} else{
	  printf("No history with id given %d\n", id);
	}

      } else{
	//Adds thei input to history
	add_history(history, input);

	//Tokenize the input
	char **tokens = tokenize(input);
	if(tokens != NULL){
	  print_tokens(tokens);
	  free_tokens(tokens);
	} else{
	  printf("Failed to tokenize string.\n");
	}
      }
    }else {
      //Exits the loop
      break;
    }
  }

  //Print and frees the history before exiting
  print_history(history);
  free_history(history);

  return 0;
}
