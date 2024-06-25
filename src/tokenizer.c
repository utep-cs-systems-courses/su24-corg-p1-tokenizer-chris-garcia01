#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

int space_char(char c){
  return c == ' ' || c == '\t';
}

int non_space_char(char c){
  return c != ' ' && c != '\t' && c != '\0';
}

char *token_start(char *s){
  while (*s != '\0'){
    if (non_space_char(*s)){
      return s;
    }
    s++;
  }
  return NULL;
}

char *token_terminator(char *token){
  while (*token != '\0' && non_space_char(*token)){
    token++;
  }
  return token;
}

int count_tokens(char *s){
  int count = 0;
  char *token = token_start(s);

  while (token != NULL){
    count++;
    s = token_terminator(token);
    token = token_start(s);
  }
  return count;
}

char *copy_str(char *inStr, short len){
  char *copy = (char*)malloc((len + 1) * sizeof(char));
  if (copy == NULL){
    return NULL;
  }

  for (short i = 0; i < len; i++){
    copy[i] = inStr[i];
  }
  copy[len] = '\0';

  return copy;
}

char **tokenize(char *str){
  int num_tokens = count_tokens(str);
  char **tokens = (char **)malloc((num_tokens + 1) * sizeof(char *));
  if (tokens == NULL){
    return NULL;
  }

  char *token = token_start(str);
  int index = 0;

  while (token != NULL){
    char *terminator = token_terminator(token);
    int len = terminator - token;
    tokens[index] = copy_str(token, len);
    if (tokens[index] == NULL){
      //Freeing allocated tokens before it returns to NULL
      for (int i = 0; i < index; i++){
	free(tokens[i]);
      }
      free(tokens);
      return NULL;
    }
    index++;
    str = terminator;
    token = token_start(str);
  }
  tokens[index] = NULL;
  return tokens;
}

void print_tokens(char **tokens){
  for (int i = 0; tokens[i] != NULL; i++){
    printf("Token %d: %s\n", i + 1, tokens[i]);
  }
}

void free_tokens(char **tokens){
  for (int i = 0; tokens[i] != NULL; i++){
    free(tokens[i]);
  }
  free(tokens);
}
