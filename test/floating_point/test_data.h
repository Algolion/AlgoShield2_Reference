#ifndef TEST_DATA_H
#define TEST_DATA_H

#include <stdint.h>

#define TEST_MAX_CELLS 2
#define TEST_MAX_SAMPLES 2

typedef struct _test_data_t {
  uint64_t time;
  float voltage_arr_mV[TEST_MAX_CELLS];
  uint16_t voltage_arr_len;
  float current_A;
  int32_t soc;
  bool is_valid;
} test_data_t;

test_data_t test_data[TEST_MAX_SAMPLES] = {
    {1, {1.0, 1.0}, TEST_MAX_CELLS, 1.0, 100, true},
    {2, {2.0, 2.0}, TEST_MAX_CELLS, 2.0, 100, true},
};
#endif /* TEST_DATA_H */
