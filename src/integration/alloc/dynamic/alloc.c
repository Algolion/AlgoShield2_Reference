#include "alloc.h"
#include "api.h"
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static void *mem_alloc(uint32_t size) { return malloc(size); }

static void mem_free(void *address) { return free(address); }

static void *mem_copy(void *destination, void *source, uint32_t size) {
  return memcpy(destination, source, size);
}

static void *mem_set(void *ptr, uint8_t value, uint32_t num) {
  return memset(ptr, value, num);
}

int alloc_init() {
  algo_status_t status = STATUS_SUCCESS;
  status = algo_mem_manage_register(mem_alloc, mem_free, mem_copy, memset);
  if (status != STATUS_SUCCESS) {
    return -1;
  }
  return 0;
}
