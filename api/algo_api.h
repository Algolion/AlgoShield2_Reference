/*----------------------------------------------------------------------------------------------------------
 * Name:		algo_api.h
 * Purpose:		The AlgoShield-2 API
 * Rev.:		1.0
 * Author:		Andrii K.
 * Copyright:	(C) 2022 Algolion LTD. All rights reserved.
 *----------------------------------------------------------------------------------------------------------*/
#ifndef ALGO_API_H
#define ALGO_API_H

#include "algo_status.h"
#include "algo_types.h"

typedef void (*algo_api_callback_error_t)(algo_status_t status);
typedef void (*algo_api_callback_sor_t)(u64_t time, u8_t *cellSOR);

typedef enum algo_api_sor_value_s {
  ALGO_API_SOR_UNKNOWN = 0,
  ALGO_API_SOR_NO_FAULT,
  ALGO_API_SOR_POTENTIAL_FAULT,
  ALGO_API_SOR_FAULT_FOUND,
} algo_api_sor_value_t;

typedef u8_t algo_api_sor_t;

typedef struct algo_api_options_s {
  algo_value_t min_volt_diff;
  algo_value_t max_volt_diff;
  algo_value_t min_current_diff;
  algo_value_t max_current_diff;
  algo_value_t divide_current;
  algo_value_t divide_voltage;
  u16_t min_gap;
  u16_t reg_start;
  u16_t reg_stop;
  u16_t ua_time_shift;

  algo_value_t ab_filter_alpha;
  algo_value_t ab_filter_beta;

  algo_value_t exp_filter_alpha;
  algo_value_t rmsd_filter_alpha;

  algo_value_t slope_k;

  u8_t heaviside_S1;
  u8_t heaviside_S2;
  algo_value_t abs_slope;
  algo_value_t max_RMSD;
  u16_t cell_num;
} algo_api_options_t;

typedef enum algo_api_tp_type_e {
  TP_DETECTION_TP_TYPE_INVALID = 0,
  TP_DETECTION_TP_TYPE_OC_DROP = 1,  /* OC - Discharge */
  TP_DETECTION_TP_TYPE_OC_RAISE = 2, /* OC - Charge */
  TP_DETECTION_TP_TYPE_DROP_OC = 3,  /* Charge - OC */
  TP_DETECTION_TP_TYPE_RAISE_OC = 4, /* Discharge - OC */
} algo_api_tp_type_t;

typedef struct algo_api_tp_info_s {
  u64_t id;
  u64_t detected_time;
  algo_api_tp_type_t type;
  i32_t soc_cp;
  algo_value_t slope;
  algo_value_t Ia;
  algo_value_t Ib;
  algo_value_t Ua[CONFIG_CELL_NUM_MAX];
  algo_value_t Ub[CONFIG_CELL_NUM_MAX];
  algo_value_t Uc[CONFIG_CELL_NUM_MAX];

  algo_value_t ea[CONFIG_CELL_NUM_MAX];
  algo_value_t hc[CONFIG_CELL_NUM_MAX];
  algo_value_t hcs[CONFIG_CELL_NUM_MAX];

  algo_api_sor_t sor[CONFIG_CELL_NUM_MAX];
  algo_api_sor_t sor_ea[CONFIG_CELL_NUM_MAX];
  algo_api_sor_t sor_hc[CONFIG_CELL_NUM_MAX];
  algo_api_sor_t sor_hcs[CONFIG_CELL_NUM_MAX];
} algo_api_tp_info_t;

algo_status_t algo_api_error_callback_register(algo_api_callback_error_t cb);
algo_status_t algo_api_sor_callback_register(algo_api_callback_sor_t cb);

bool algo_api_initialized(void);
algo_status_t algo_api_initialize(void);
algo_status_t algo_api_deinitialize(void);
algo_status_t algo_api_module_status_get(u8_t *module_status);

algo_status_t algo_api_sample(const u64_t time,
                              const algo_value_t *voltage_arr_mV,
                              const u16_t voltage_arr_len,
                              const algo_value_t current_A, const i32_t soc,
                              const bool is_valid);

algo_status_t algo_api_sor_get(algo_api_sor_t *sor);
algo_status_t algo_api_sor_ea_get(algo_api_sor_t *sor_ea);
algo_status_t algo_api_sor_hc_get(algo_api_sor_t *sor_hc);
algo_status_t algo_api_sor_hcs_get(algo_api_sor_t *sor_hcs);

algo_status_t algo_api_ea_get(const algo_value_t **ea);
algo_status_t algo_api_hc_get(const algo_value_t **hc);
algo_status_t algo_api_hcs_get(const algo_value_t **hcs);

algo_status_t algo_api_options_get(const algo_api_options_t **api_options);
algo_status_t algo_api_options_set(algo_api_options_t *api_options);

algo_status_t algo_api_tp_info_get(const algo_api_tp_info_t **tp_info);

#endif /* ALGO_CORE_H */
