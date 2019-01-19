#include <stdlib.h>
#include <stdio.h>
#include "dllist.h"

typedef struct dnode {
  struct dnode* prev;
  struct dnode* next;
  void* data;
} node;

static node* create_node(void* data);

static node* create_node(void* data) {
  node* new_node = malloc(sizeof(node));
  if (new_node == NULL) return NULL;
  new_node->data = data;
  new_node->prev = NULL;
  new_node->next = NULL;
  return new_node;
}

dllist* create_dllist(void) {
  dllist* new_list = malloc(sizeof(dllist));
  if (new_list == NULL) return NULL;
  new_list->head = NULL;
  new_list->tail = NULL;
  new_list->size = 0;
  return new_list;
}

void push_front(dllist *d, void *data) {
  node* new_node = create_node(data);
  if (d->head == NULL) {
    d->tail = new_node;
  } else {
    new_node->next = d->head;
    d->head->prev = new_node;
  }
  d->head = new_node;   
  d->size++;
}

void push_back(dllist *d, void *data) {
  node* new_node = create_node(data);
  if (d->head == NULL) {
    d->head = new_node;
  } else {
    new_node->prev = d->tail;
    d->tail->next = new_node;
  }
  d->tail = new_node;
  d->size++;
}

void *front(dllist *d) {
  if (d == NULL) return NULL;
  if (d->size == 0) return NULL;
  return d->head->data;
}

void *back(dllist *d) {
  if (d == NULL) return NULL;
  if (d->size == 0) return NULL;
  return d->tail->data;
}

void *get(dllist *d, int index) {
  if (d == NULL) return NULL;
  if (index < 0 || index > d->size -1) return NULL;
  int i = 0;
  node* cur = d->head;
  while (i < index) {
    cur = cur->next;
    i++;
  }
  return cur->data;
}

bool add(dllist *d, void* data, int index) {
  if (d == NULL) return false;
  if (index < 0 || index > d->size) {
    return false;
  } else if (index == 0) {
    push_front(d, data);
  } else if (index == d->size) {
    push_back(d, data);
  } else {
    node* new_node = create_node(data);
    int i = 0;
    node* cur = d->head;
    while (i < index) {
      cur = cur->next;
      i++;
    }
    new_node->prev = cur->prev;
    new_node->next = cur;
    cur->prev->next = new_node;
    cur->prev = new_node;
    d->size++;
  }
  printf("size: %d, index: %d \n", d->size, index);
  return true;
}

void *contains(dllist *d, void *data, dllist_eq eq_func) {
  if (d == NULL) return NULL;
  node* cur = d->head;
  while (cur != NULL) {
    if (eq_func(cur->data, data) == 0) return cur->data;
    cur = cur->next;
  }
  return NULL;
}

void *pop_front(dllist *d) {
  if (d == NULL || d->size == 0) {
    return NULL;
  } else {
    node* temp = d->head;
    void* data = temp->data;
    if (d->size == 1) {
      d->head = NULL;
      d->tail = NULL;
    } else {
      d->head = d->head->next;
      temp->next = NULL;
      d->head->prev = NULL;
    }
    free(temp);
    d->size--;
    return data;
  }
}

void *pop_back(dllist *d) {
  if (d == NULL || d->size == 0) {
    return NULL;
  } else {
    node* temp = d->tail;
    void* data = temp->data;
    if (d->size == 1) {
      d->head = NULL;
      d->tail = NULL;
    } else {
      d->tail = d->tail->prev;
      temp->prev = NULL;
      d->tail->next = NULL;
    } 
    free(temp);
    d->size--;
    return data;
  }
}

dllist* copy_dllist(dllist *d, dllist_copy copy_func) {
  if (d == NULL) {
    return NULL;
  } else {
    dllist* new_list = create_dllist();
    node* cur = d->head;
    while (cur != NULL) {
      push_back(new_list, copy_func(cur->data));
      cur = cur->next;
    }
    return new_list;
  }
}

int size(dllist *d) {
  if (d == NULL) return 0;
  return d->size;
}

bool is_empty(dllist *d) {
  if (d == NULL) return false;
  return d->size == 0;
}

void empty_dllist(dllist *d, dllist_op free_func) {
  node* cur = d->head;
  while (cur != NULL) {
    node* temp = cur;
    cur = cur->next;
    free_func(temp->data);
    free(temp);
  }
  d->head = NULL;
  d->tail = NULL;
  d->size = 0;
}

void traverse(dllist *d, dllist_op do_func) {
  node* cur = d->head;
  while (cur != NULL) {
    do_func(cur->data);
    cur = cur->next;
  }
}

void reverse(dllist *d) {
  node* cur = d->head;
  while (cur != NULL) {
    node* next = cur->next;
    cur->next = cur->prev;
    cur->prev = next;
    cur = next;
  }
  node* temp_head = d->head;
  d->head = d->tail;
  d->tail = temp_head;
}
