add_library(BSP INTERFACE)

target_sources(BSP INTERFACE
    ./src/bsp_log.c
    ./src/bsp_systick.c
    ./src/bsp_timebase.c
    ./src/bsp_uart.c
)

target_include_directories(BSP INTERFACE
    ./inc
)
