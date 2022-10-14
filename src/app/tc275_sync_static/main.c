#include "alloc.h"
#include "api.h"
#include "hal.h"
#include "test_data.h"

static int32_t cell_ea[TEST_MAX_CELLS];
static int32_t cell_hc[TEST_MAX_CELLS];
static int32_t cell_hcs[TEST_MAX_CELLS];
static algo_api_sor_t cell_sor[TEST_MAX_CELLS];
static algo_api_sor_t cell_sor_ea[TEST_MAX_CELLS];
static algo_api_sor_t cell_sor_hc[TEST_MAX_CELLS];
static algo_api_sor_t cell_sor_hcs[TEST_MAX_CELLS];

algo_status_t algo_api_tp_detected_cb(algo_api_tp_info_t *tp_info) {
  // Receive
  for (uint32_t cell_count; cell_count < TEST_MAX_CELLS; cell_count++) {
    cell_ea[cell_count] = tp_info->ea[cell_count];
    cell_hc[cell_count] = tp_info->hc[cell_count];
    cell_hcs[cell_count] = tp_info->hcs[cell_count];
    cell_sor[cell_count] = tp_info->sor[cell_count];
    cell_sor_ea[cell_count] = tp_info->sor_ea[cell_count];
    cell_sor_hc[cell_count] = tp_info->sor_hc[cell_count];
    cell_sor_hcs[cell_count] = tp_info->sor_hcs[cell_count];
  }
}

int integration_init() {
  int status = 0;
  // Init allocator
  status = alloc_init();
  if (int_status != 0) {
    return -1
  }
  // Init HAL
  status = hal_init();
  if (int_status != 0) {
    return -1
  }
  return 0;
}

int main(int argc, char *argv[]) {
  algo_status_t status = STATUS_SUCCESS;
  uint64_t tp_id = 0;
  // Init integration
  if (0 != integration_init(true)) {
    return -1;
  }
  // Init library
  status = algo_api_initialize();
  if (status != STATUS_SUCCESS) {
    return -1;
  }
  // Register callback for TP detection
  algo_api_tp_detected_cb_register(algo_api_tp_detected_cb);
  // Set test data to the library
  for (uint32_t sample_count = 0; sample_count < TEST_MAX_SAMPLES;
       sample_count++) {
    algo_api_tp_info_t tp_info = {0};
    // Set next sample
    status = algo_api_sample(
        test_data[sample_count].time, test_data[sample_count].voltage_arr_mV,
        test_data[sample_count].voltage_arr_len,
        test_data[sample_count].current_A, test_data[sample_count].soc,
        test_data[sample_count].is_valid);
    if (status != STATUS_SUCCESS) {
      break;
    }
    // Check if new TP arrived
    status = algo_api_tp_info_get(&tp_info);
    if (status == STATUS_SUCCESS) {
      if (tp_id != tp_info.id) {
        // Get info
        for (uint32_t cell_count; cell_count < TEST_MAX_CELLS; cell_count++) {
          cell_ea[cell_count] = tp_info.ea[cell_count];
          cell_hc[cell_count] = tp_info.hc[cell_count];
          cell_hcs[cell_count] = tp_info.hcs[cell_count];
          cell_sor[cell_count] = tp_info.sor[cell_count];
          cell_sor_ea[cell_count] = tp_info.sor_ea[cell_count];
          cell_sor_hc[cell_count] = tp_info.sor_hc[cell_count];
          cell_sor_hcs[cell_count] = tp_info.sor_hcs[cell_count];
        }
        tp_id = tp_info.id;
      }
    }
  }

  status = algo_api_deinitialize();
  if (status != STATUS_SUCCESS) {
    return -1;
  }
  return 0;
}
