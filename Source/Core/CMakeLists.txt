target_sources(${EXECUTABLE_NAME} PRIVATE
    ./freertos.c
    ./gd32f3x0_it.c
    ./main.c
)

target_include_directories(${EXECUTABLE_NAME} PUBLIC
    ./
)
