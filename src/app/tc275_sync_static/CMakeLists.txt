
set(APP_TARGET           "tc275_sync_static")

set(ALLOCATION_TYPE "static")
set(HAL_TYPE "infineon/tc275")
set(REAL_NUMBER_MATH "fixed_point")
set(COMPILER "tasking")

add_executable(${APP_TARGET})

target_sources(${APP_TARGET}
    PRIVATE
        main.c
        ${ALLOC_DIR}/${ALLOCATION_TYPE}/alloc.c
        ${HAL_DIR}/${HAL_TYPE}/hal.c
)

target_include_directories(${APP_TARGET}
    PUBLIC
        ${ALLOC_DIR}
        ${ASYNC_DIR}
        ${HAL_DIR}
        ${API_DIR}
        ${TEST_DIR}/${REAL_NUMBER_MATH}
)

target_link_libraries(${APP_TARGET} ${ALGOSHIELD_LIBRARY})
