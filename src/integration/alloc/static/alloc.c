#include "alloc.h"
#include "api.h"

#define MAX_BUFFER_SIZE (10000)

static u8_t buffer[MAX_BUFFER_SIZE];

static void *mem_copy(void *destination, void *source, u32_t size) {
  for (unsigned int i = 0; i < size; i++) {
    ((char *)destination)[i] = ((char *)source)[i];
  }
  return destination;
}

static void *mem_set(void *ptr, u8_t value, u32_t num) {
  unsigned char *w_ptr = (unsigned char *)ptr;
  while (num > 0) {
    *w_ptr = (unsigned char)value;
    w_ptr++;
    num--;
  }

  return ptr;
}

int alloc_init() {
  algo_status_t status = STATUS_SUCCESS;
  status = algo_mem_set_buffer(buffer);
  if (status != STATUS_SUCCESS) {
    return -1;
  }
  status = algo_mem_manage_register(NULL, NULL, mem_copy, mem_set);
  if (status != STATUS_SUCCESS) {
    return -1;
  }
  return 0;
}
