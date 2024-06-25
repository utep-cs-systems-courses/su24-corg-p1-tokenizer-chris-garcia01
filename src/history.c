#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"

List* init_history(void){
  List *list = (List *)malloc(sizeof(List));
  if (list == NULL){
    return NULL;
  }
  list->root = NULL;
  return list;
}

void add_history(List *list, char *str) {
    Item *new_item = (Item *)malloc(sizeof(Item));
    if (new_item == NULL) {
        return;
    }

    new_item->id = 1;
    new_item->str = strdup(str);
    new_item->next = NULL;

    if (list->root == NULL) {
        list->root = new_item;
    } else {
        Item *current = list->root;
        while (current->next != NULL) {
            current = current->next;
        }
        new_item->id = current->id + 1;
        current->next = new_item;
    }
}


char *get_history(List *list, int id){
  Item *current = list->root;
  while (current != NULL){
    if(current->id == id){
      return current->str;
    }
    current = current->next;
  }
  return NULL;
}

void print_history(List *list){
  Item *current = list->root;
  while (current != NULL){
    printf("%d: %s\n", current->id, current->str);
    current = current ->next;
  }
}

void free_history(List *list){
  Item *current = list->root;
  while(current != NULL){
    Item *next = current->next;
    free(current->str);
    free(current);
    current = next;
  }
  free(list);
}
