add_library(SEGGER_RTT EXCLUDE_FROM_ALL
	SEGGER_RTT_printf.c
	SEGGER_RTT.c
	SEGGER_RTT_ASM_ARMv7M.S
)

target_include_directories(SEGGER_RTT PUBLIC
	./
)
