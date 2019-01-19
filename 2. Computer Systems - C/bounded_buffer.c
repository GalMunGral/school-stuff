#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "bounded_buffer.h"

typedef struct node {
  int data;
  struct node *next;
} node_t;

typedef struct linked_list {
  node_t *head;
  node_t *tail;
  int curr_size;
  int max_size;
} linked_list_t;

typedef struct array {
  int *items;
  int size;
} array_t;

linked_list_t* buffer;
pthread_cond_t* notEmpty;
pthread_cond_t* notFull;
pthread_mutex_t* lock;
pthread_mutex_t* arr_lock;
array_t* is_being_processed;
pthread_cond_t* done_processing;

/**************************************************************************\
 *                                                                        *
 * void buffer_init(void)                                                 *
 *                                                                        *
 *      buffer_init() is called by main() at the beginning of time to     *
 *      perform any required initialization.  I.e. initialize the buffer, *
 *      any mutex/condition variables, etc.                               *
 *                                                                        *
\**************************************************************************/
void buffer_init() {
  buffer = malloc(sizeof(linked_list_t));
  buffer->curr_size = 0;
  buffer->max_size = BUFFER_MAX_SIZE;
  notEmpty = malloc(sizeof(pthread_cond_t));
  notFull = malloc(sizeof(pthread_cond_t));
  lock = malloc(sizeof(pthread_mutex_t));
  arr_lock = malloc(sizeof(pthread_mutex_t));
  is_being_processed = malloc(sizeof(array_t));
  is_being_processed->size = 10;
  is_being_processed->items = malloc(sizeof(int) * 10);
  done_processing = malloc(sizeof(pthread_cond_t)*10);
  for (int i = 0; i < 10; i++) {
    pthread_cond_init(&done_processing[i], NULL);
  }
  pthread_cond_init(notEmpty, NULL);
  pthread_cond_init(notFull, NULL);
  pthread_mutex_init(lock, NULL);
  return;
}

/**************************************************************************\
 *                                                                        *
 * void buffer_insert(int number)                                         *
 *                                                                        *
 *      buffer_insert() inserts a number into the next available slot in  *
 *      the buffer.  If no slots are available, the thread should wait    *
 *      (not spin-wait!) for an empty slot to become available.           *
 *                                                                        *
\**************************************************************************/
void buffer_insert(int number) {
  pthread_mutex_lock(lock);
  while (buffer->curr_size == buffer->max_size) {
    pthread_cond_wait(notFull, lock);
  }
  node_t* new_node = malloc(sizeof(node_t));
  new_node->data = number;
  new_node->next = NULL;
  if (buffer->curr_size == 0) {
    buffer->head = new_node;
  } else {
    buffer->tail->next = new_node;
  }
  buffer->tail = new_node;
  buffer->curr_size++;
  pthread_cond_signal(notEmpty);
  pthread_mutex_unlock(lock);
  return;
}

/**************************************************************************\
 *                                                                        *
 * int buffer_extract(void)                                               *
 *                                                                        *
 *      buffer_extract() removes and returns the number in the next       *
 *      available slot.  If no number is available, the thread should     *
 *      wait (not spin-wait!) for a number to become available.  Note     *
 *      that multiple consumers may call buffer_extract() simulaneously.  *
 *                                                                        *
\**************************************************************************/
int buffer_extract(void) {
  int data;
  pthread_mutex_lock(lock);
  while (buffer->curr_size == 0) {
    pthread_cond_wait(notEmpty, lock);
  }
  data = buffer->head->data;
  node_t* old_head = buffer->head;
  buffer->head = old_head->next;
  if (buffer->curr_size == 1) {
    buffer->tail = NULL;
  }
  buffer->curr_size--;
  pthread_cond_signal(notFull);
  pthread_mutex_unlock(lock);

  if (data == 0) return data;

  pthread_mutex_lock(arr_lock);
  while (is_being_processed->items[data-1] == 1) {
    pthread_cond_wait(&done_processing[data-1], arr_lock);
  }
  is_being_processed->items[data-1] = 1;
  pthread_mutex_unlock(arr_lock);

  process(data);

  pthread_mutex_lock(arr_lock);
  is_being_processed->items[data-1] = 0;
  pthread_cond_signal(&done_processing[data-1]);
  pthread_mutex_unlock(arr_lock);

  return data;
}

void process(int number) {
  sleep(number);
}
