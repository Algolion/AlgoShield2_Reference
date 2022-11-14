#ifndef TEST_DATA_H
#define TEST_DATA_H

#include <stdint.h>

#define TEST_MAX_CELLS 2
#define TEST_MAX_SAMPLES 2

typedef struct _test_data_t {
  uint64_t time;
  int32_t voltage_arr_mV[TEST_MAX_CELLS];
  uint16_t voltage_arr_len;
  int32_t current_A;
  int32_t soc;
  bool is_valid;
} test_data_t;

test_data_t test_data[TEST_MAX_SAMPLES] = {
    {1, {1, 1}, TEST_MAX_CELLS, 1, 100, true},
    {2, {2, 2}, TEST_MAX_CELLS, 2, 100, true},
};
#endif /* TEST_DATA_H */
