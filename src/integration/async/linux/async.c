#include "async.h"
#include "api.h"
#include <mqueue.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define QUEUE_PERMISSIONS 0660

static pthread_t thread;
static pthread_mutex_t mutex;
static mqd_t queue;

static algo_status_t async_thread_create(char *name, u32_t stack_size,
                                         thread_entry_t entry) {
  int status = 0;
  char *unused = name;
  status = pthread_create(&thread, NULL, entry, NULL);
  return STATUS_SUCCESS;
}

static algo_status_t async_thread_delete(char *name) {
  char *unused = name;
  pthread_exit(thread);
  return STATUS_SUCCESS;
}

static algo_status_t async_queue_create(char *name, u32_t msg_size,
                                        u32_t msg_count) {
  struct mq_attr attr;

  attr.mq_flags = 0;
  attr.mq_maxmsg = msg_count;
  attr.mq_msgsize = msg_size;
  attr.mq_curmsgs = 0;

  queue = mq_open(name, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr);
  if (queue != 0) {
    return STATUS_NOT_AVAILABLE;
  }
  return STATUS_SUCCESS;
}

static algo_status_t async_queue_delete(char *name) {
  int status = 0;
  status = mq_close(queue);
  if (status != 0) {
    return STATUS_NOT_AVAILABLE;
  }
  return STATUS_SUCCESS;
}

static algo_status_t async_queue_push(char *name, void *msg, u32_t msg_size) {
  int status = 0;
  status = mq_send(queue, msg, msg_size, NULL);
  if (status != 0) {
    return STATUS_NOT_AVAILABLE;
  }
  return STATUS_SUCCESS;
}

static algo_status_t async_queue_pull(char *name, void *msg, u32_t msg_size) {
  int status = 0;
  status = mq_receive(queue, msg, msg_size, NULL);
  if (status != 0) {
    return STATUS_NOT_AVAILABLE;
  }
  return STATUS_SUCCESS;
}

static algo_status_t async_lock_create(char *name) {
  int status = 0;
  char *unused = name;
  status = pthread_mutex_init(&mutex, NULL);
  if (status != 0) {
    return STATUS_NOT_AVAILABLE;
  }
  return STATUS_SUCCESS;
}

static algo_status_t async_lock_delete(char *name) {
  char *unused = name;
  pthread_mutex_destroy(&mutex);
  return STATUS_SUCCESS;
}

static algo_status_t async_lock_obtain(char *name) {
  char *unused = name;
  pthread_mutex_unlock(&mutex);
  return STATUS_SUCCESS;
}

static algo_status_t async_lock_release(char *name) {
  char *unused = name;
  pthread_mutex_unlock(&mutex);
  return STATUS_SUCCESS;
}

int async_init() {
  algo_status_t status = STATUS_SUCCESS;
  status = algo_async_thread_register(async_thread_create, async_thread_delete);
  if (status != STATUS_SUCCESS) {
    return -1;
  }
  status = algo_async_queue_register(async_queue_create, async_queue_delete,
                                     async_queue_push, async_queue_pull);
  if (status != STATUS_SUCCESS) {
    return -1;
  }
  status = algo_async_lock_register(async_lock_create, async_lock_delete,
                                    async_lock_obtain, async_lock_release);
  if (status != STATUS_SUCCESS) {
    return -1;
  }
  return 0;
}
