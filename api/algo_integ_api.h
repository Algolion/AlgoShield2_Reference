#ifndef ALGO_INTEG_API_H
#define ALGO_INTEG_API_H

#include "algo_status.h"
#include "algo_types.h"
// HAL
typedef algo_status_t (*algo_persistent_read_cb_t)(void *buffer, u32_t size);
typedef algo_status_t (*algo_persistent_write_cb_t)(void *buffer, u32_t size);
typedef u32_t (*algo_time_read_cb_t)();
typedef algo_status_t (*algo_id_read_cb_t)(void *buffer, u32_t size);

algo_status_t
algo_hal_persistent_register(algo_persistent_read_cb_t read_callback,
                             algo_persistent_write_cb_t write_callback);
algo_status_t algo_hal_time_register(algo_time_read_cb_t read_callback);
algo_status_t algo_hal_id_register(algo_id_read_cb_t read_callback);
// Malloc
typedef void *(*algo_mem_malloc_cb_t)(u32_t size);
typedef void (*algo_mem_free_cb_t)(void *address);
typedef void *(*algo_mem_copy_cb_t)(void *destination, void *source,
                                    u32_t size);
typedef void *(*algo_mem_set_cb_t)(void *ptr, u8_t value, u32_t num);

algo_status_t algo_mem_set_buffer(u32_t address);
algo_status_t algo_mem_manage_register(algo_mem_malloc_cb_t malloc_callback,
                                       algo_mem_free_cb_t free_callback,
                                       algo_mem_copy_cb_t copy_callback,
                                       algo_mem_set_cb_t set_callback);
// Async
typedef void *(*thread_entry_t)(void *ptr);
typedef algo_status_t (*algo_thread_create_cb_t)(char *name, u32_t stack_size,
                                                 thread_entry_t entry);
typedef algo_status_t (*algo_thread_delete_cb_t)(char *name);
typedef algo_status_t (*algo_queue_create_cb_t)(char *name, u32_t msg_size,
                                                u32_t msg_count);
typedef algo_status_t (*algo_queue_delete_cb_t)(char *name);
typedef algo_status_t (*algo_queue_push_cb_t)(char *name, void *msg,
                                              u32_t msg_size);
typedef algo_status_t (*algo_queue_pull_cb_t)(char *name, void *msg,
                                              u32_t msg_size);
typedef algo_status_t (*algo_lock_create_cb_t)(char *name);
typedef algo_status_t (*algo_lock_delete_cb_t)(char *name);
typedef algo_status_t (*algo_lock_obtain_cb_t)(char *name);
typedef algo_status_t (*algo_lock_release_cb_t)(char *name);

algo_status_t
algo_async_thread_register(algo_thread_create_cb_t create_callback,
                           algo_thread_delete_cb_t delete_callback);
algo_status_t algo_async_queue_register(algo_queue_create_cb_t create_callback,
                                        algo_queue_delete_cb_t delete_callback,
                                        algo_queue_push_cb_t push_callback,
                                        algo_queue_pull_cb_t pull_callback);
algo_status_t algo_async_lock_register(algo_lock_create_cb_t create_callback,
                                       algo_lock_delete_cb_t delete_callback,
                                       algo_lock_obtain_cb_t obtain_callback,
                                       algo_lock_release_cb_t release_callback);

#endif /* ALGO_INTEG_API_H */
