add_library(GD32F3x0_standard_peripheral EXCLUDE_FROM_ALL
	Source/gd32f3x0_adc.c
	Source/gd32f3x0_cec.c
	Source/gd32f3x0_cmp.c
	Source/gd32f3x0_crc.c
	Source/gd32f3x0_ctc.c
	Source/gd32f3x0_dac.c
	Source/gd32f3x0_dbg.c
	Source/gd32f3x0_dma.c
	Source/gd32f3x0_exti.c
	Source/gd32f3x0_fmc.c
	Source/gd32f3x0_fwdgt.c
	Source/gd32f3x0_gpio.c
	Source/gd32f3x0_i2c.c
	Source/gd32f3x0_misc.c
	Source/gd32f3x0_pmu.c
	Source/gd32f3x0_rcu.c
	Source/gd32f3x0_rtc.c
	Source/gd32f3x0_spi.c
	Source/gd32f3x0_syscfg.c
	Source/gd32f3x0_timer.c
	Source/gd32f3x0_tsi.c
	Source/gd32f3x0_usart.c
	Source/gd32f3x0_wwdgt.c
)

target_include_directories(GD32F3x0_standard_peripheral PUBLIC
	Include
)
add_dependencies(GD32F3x0_standard_peripheral CMSIS)
target_link_libraries(GD32F3x0_standard_peripheral CMSIS)

target_compile_options(
	GD32F3x0_standard_peripheral
	PRIVATE -Os
)
