#include "list.h"
#include <stdio.h>
#include <stdlib.h>

LIST *create_list() {
  LIST* new = malloc(sizeof(LIST*));
  if (new == NULL) return NULL;
  new->head = NULL;
  new->size = 0;
  return new;
}

NODE *create_node(void* data) {
  if (data == NULL) return NULL;
  NODE* new = malloc(sizeof(NODE*));
  if (new == NULL) return NULL;
  new->next = NULL;
  new->data = data;
  return new;
}

void push_front(LIST *llist, void* data) {
  if (llist == NULL || data == NULL) return;
  NODE* new_node = create_node(data);
  new_node->next = llist->head;
  llist->head = new_node;
  llist->size++;
  return;
}

void* pop_front(LIST *llist) {
  if (llist == NULL || llist->size == 0) return NULL;
  NODE* temp = llist->head;
  llist->head = llist->head->next;
  void* data = temp->data;
  free(temp);
  llist->size--;
  return data;
}

void destroy(LIST *llist, list_op free_func) {
  if (llist == NULL) return;
  NODE* cur = llist->head;
  NODE* next;
  while (cur != NULL) {
    free_func(cur->data);
    next = cur->next;
    free(cur);
    cur = next;
  }
  free(llist);
}

void* to_array(LIST *llist, size_t struct_size) {
  if (llist == NULL || llist->size == 0) return NULL;
  char* arr = malloc(llist->size * struct_size);
  char* cur_data = arr;
  char* src;
  NODE* cur_node = llist->head;
  while (cur_node != NULL) {
    src = (char*) cur_node->data;
    for (unsigned int i = 0; i < struct_size; i++) {
      cur_data[i] = src[i];
    }
    cur_data += struct_size;
    cur_node = cur_node->next;
  }
  return arr;
}
