set(APP_TARGET           "linux_async_dynamic")

# set configuration
set(ALLOCATION_TYPE     "dynamic")
set(ASYNC_TYPE          "linux")
set(HAL_TYPE            "pc/linux")
set(REAL_NUMBER_MATH    "floating_point")

#set toolchain
set(TOOLCHAIN           "gcc" CACHE STRING "Toolchain for build" FORCE)

add_executable(${APP_TARGET})

target_sources(${APP_TARGET}
    PRIVATE
        main.c
        ${ALLOC_DIR}/${ALLOCATION_TYPE}/alloc.c
        ${ASYNC_DIR}/${ASYNC_TYPE}/async.c
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
