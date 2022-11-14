/*----------------------------------------------------------------------------------------------------------
 * Name:			algo_status.h
 * Purpose:		The AlgoShield-2 status
 * Rev.:		1.0
 * Author:		Andrii K.
 * Copyright:	(C) 2022 Algolion LTD. All rights reserved.
 *----------------------------------------------------------------------------------------------------------*/
#ifndef ALGO_STATUS_H
#define ALGO_STATUS_H

typedef enum algo_status_e {
  STATUS_SUCCESS = 0,
  STATUS_INTERNAL,
  STATUS_INVALID_PARAM,
  STATUS_INVALID_CONFIG,
  STATUS_UNINITIALIZED,
  STATUS_OUT_OF_MEMORY,
  STATUS_NOT_SUPPORTED,
  STATUS_NOT_AVAILABLE,
  STATUS_ALREADY_INITIALIZED,
  STATUS_EXPIRED,
} algo_status_t;

typedef enum algo_module_status_e {
  MODULE_STATUS_OK = 0,
  MODULE_STATUS_INVALID_SAMPLES,
} algo_module_status_t;

#endif /* ALGO_STATUS_H */
