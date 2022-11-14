#include "hal.h"
#include "api.h"

static algo_status_t hal_persistent_read(void *buffer, u32_t size) {

  return STATUS_SUCCESS;
}

static algo_status_t hal_persistent_write(void *buffer, u32_t size) {

  return STATUS_SUCCESS;
}

static u32_t hal_time_read() { return 0; }

static algo_status_t hal_id_read(void *buffer, u32_t size) {
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
