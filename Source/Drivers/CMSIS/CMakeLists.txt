# 添加静态库 启动文件与启动函数
add_library(CMSIS INTERFACE
)

target_sources(CMSIS INTERFACE
	GD/GD32F3x0/Source/GNU/startup_gd32f3x0.s
	GD/GD32F3x0/Source/system_gd32f3x0.c
)

target_include_directories(CMSIS INTERFACE
	./GD/GD32F3x0/Include
	./
)
