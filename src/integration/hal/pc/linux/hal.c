#include "hal.h"
#include "api.h"

static algo_status_t hal_persistent_read(void *buffer, uint32_t size) {
  memcpy(buffer, (uint32_t *)FLASH_ADDR, size);
  return STATUS_SUCCESS;
}

static algo_status_t hal_persistent_write(void *buffer, uint32_t size) {
  flash_erase(FLASH_ADDR, 1);
  flash_wait();

  flash_page_mode();
  flash_wait();

  flash_load((uint32_t *)buffer, size / sizeof(uint32_t));
  flash_write(FLASH_ADDR);
  flash_wait();

  return STATUS_SUCCESS;
}

static uint32_t hal_time_read() {
  uint64_t result;
  uint64_t timer_less = *((uint32_t *)0xF0000010);
  uint64_t timer_more = *((uint32_t *)0xF000002C);

  result = timer_less;
  result |= timer_more << 32;

  return result / 50000000;
}

static algo_status_t hal_id_read(void *buffer, uint32_t size) {
  memcpy(buffer, (uint32_t *)0xAF101000, size);
  return STATUS_SUCCESS;
}

int hal_init() {
  algo_status_t status = STATUS_SUCCESS;
  status =
      algo_hal_persistent_register(hal_persistent_read, hal_persistent_write);
  if (status != STATUS_SUCCESS) {
    return -1;
  }
  status = algo_hal_time_register(hal_time_read);
  if (status != STATUS_SUCCESS) {
    return -1;
  }
  status = algo_hal_id_register(hal_id_read);
  if (status != STATUS_SUCCESS) {
    return -1;
  }
  return 0;
}
