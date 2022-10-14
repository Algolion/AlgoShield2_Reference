#include "hal.h"
#include "api.h"

#define FLASH_ADDR (0x70101F80)

static void flash_erase(uint32_t address, uint8_t num_of_sectors) {
  volatile uint32_t *addr1 = (volatile uint32_t *)(0xaf000000 | 0xaa50);
  volatile uint32_t *addr2 = (volatile uint32_t *)(0xaf000000 | 0xaa58);
  volatile uint32_t *addr3 = (volatile uint32_t *)(0xaf000000 | 0xaaa8);
  volatile uint32_t *addr4 = (volatile uint32_t *)(0xaf000000 | 0xaaa8);

  *addr1 = address;
  *addr2 = num_of_sectors;
  *addr3 = 0x80;
  *addr4 = 0x50;
}

static void flash_wait() {
  volatile uint32_t *addr1 = (volatile uint32_t *)(0xF8002010);

  while (*addr1 & (1 << 1)) {
  }
}

static void flash_load(uint32_t *buffer, uint32_t words) {
  volatile uint32_t *addr1 = (volatile uint32_t *)(0xaf000000 | 0x55f0);

  for (uint32_t i = 0; i < words; i++) {
    *addr1 = buffer[i];
    addr1++;
  }
}

static void flash_write(uint32_t address) {
  volatile uint32_t *addr1 = (volatile uint32_t *)(0xaf000000 | 0xaa50);
  volatile uint32_t *addr2 = (volatile uint32_t *)(0xaf000000 | 0xaa58);
  volatile uint32_t *addr3 = (volatile uint32_t *)(0xaf000000 | 0xaaa8);
  volatile uint32_t *addr4 = (volatile uint32_t *)(0xaf000000 | 0xaaa8);

  *addr1 = address;
  *addr2 = 0x00;
  *addr3 = 0xa0;
  *addr4 = 0xaa;
}

static void flash_page_mode() {
  volatile uint32_t *addr1 = (volatile uint32_t *)(0xaf000000 | 0x5554);
  *addr1 = 0x5D;
}

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
