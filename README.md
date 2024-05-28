# GD32+FreeRTOS 工程模板

## 概述

该模板包含CMake和Keil两种构建方式，在```Project/Keil``` 目录下有Keil的工程文件，根目录```GD32_FreeRTOS_templete.code-workspace```使vsCode的工作区文件，里面有推荐的插件。

关于用GCC和CMake构建GD32工程以前在[GD32_CMake_Example](https://github.com/Huffer342-WSH/GD32_CMake_Example)记录过，之后应该会都合并到这个工程里。

### 版本
- 单片机型号 GD32F310F8P6
- 固件库版本 [GD32F3x0 Firmware Library](https://www.gd32mcu.com/data/documents/toolSoftware/GD32F3x0_Firmware_Library_V2.3.0.7z)
- FreeRTOS版本 [FreeRTOS v202210.01-LTS](https://github.com/FreeRTOS/FreeRTOS-LTS/releases/download/202210.01-LTS/FreeRTOSv202210.01-LTS.zip)
- GCC编译器版本 [arm-gnu-toolchain-13.2.rel1-mingw-w64-i686-arm-none-eabi](https://developer.arm.com/-/media/Files/downloads/gnu/13.2.rel1/binrel/arm-gnu-toolchain-13.2.rel1-mingw-w64-i686-arm-none-eabi.zip?rev=93fda279901c4c0299e03e5c4899b51f&hash=A3C5FF788BE90810E121091C873E3532336C8D46)
- Keil编译器版本 AC6.21(ArmClang)

### 工程结构：
```
├─.vscode
├─bin
│  └─Debug
├─CMake
├─Doc
│  └─assets
├─Project
│  └─Keil
├─Scripts
│  └─openocd
├─Source
│  ├─BSP
│  │  ├─inc
│  │  └─src
│  ├─Config
│  ├─Core
│  ├─Drivers
│  │  ├─CMSIS
│  │  │  └─GD
│  │  │      └─GD32F3x0
│  │  │          ├─Include
│  │  │          └─Source
│  │  │              ├─ARM
│  │  │              ├─GNU
│  │  │              └─IAR
│  │  ├─GD32F3x0_standard_peripheral
│  │  │  ├─Include
│  │  │  └─Source
│  │  └─RTT
│  ├─Functions
│  ├─Middlewares
│  │  └─FreeRTOS
│  │      └─Source
│  │          ├─include
│  │          └─portable
│  │              ├─GCC
│  │              │  └─ARM_CM4F
│  │              ├─MemMang
│  │              └─RVDS
│  │                  └─ARM_CM4F
│  └─Retarget
│      ├─inc
│      └─src
└─Utilities
```

## 从零搭建这个工程

用GCC编译需要单独准备启动文件和链接脚本，GD官方的固件库里没有提供。
>STM32的库里什么都有有，STM32Cube已经支持CMake了。

### 1.下载GD32固件库和FreeRTOS

[FreeRTOS v202210.01-LTS](https://github.com/FreeRTOS/FreeRTOS-LTS/releases/download/202210.01-LTS/FreeRTOSv202210.01-LTS.zip)

[GD32 资料下载](https://www.gd32mcu.com/cn/download/)

### 2.移植固件库

下载下来的GD32固件库解压后目录结构如下：
```
├─Docs
├─Examples
├─Firmware
│  ├─CMSIS
│  ├─GD32F3x0_standard_peripheral
│  └─GD32F3x0_usbfs_library
├─Template
└─Utilities
```

我们只需要用到`Firmware`目录下的文件（该工程没用```GD32F3x0_usbfs_library```），粘贴到自己工程的目录里就行，我放在```Source/Drivers```下。

> 写一个GCC风格的启动文件[startup_gd32f3x0.s](https://github.com/Huffer342-WSH/GD32_FreeRTOS_templete/blob/main/Source/Drivers/CMSIS/GD/GD32F3x0/Source/GNU/startup_gd32f3x0.s)
> 
> 启动文件startup_gd32f3x0.s中，包含了复位服务函数Reset_Handler以及中断向量表。中断向量表存的就是中断处理函数的入口，这些函数的顺序使硬件设计决定的，数据手册有说明。我们写GCC风格的启动文件时一定要严格按照官方提供的ARM风格的启动文件来写，否则中断处理函数会乱掉。


### 3.移植FreeRTOS-Kernel

官方教程[创建一个新的 FreeRTOS 项目](https://www.freertos.org/zh-cn-cmn-s/Creating-a-new-FreeRTOS-project.html)
这个东西官方讲的很详细，Cortex-M等常见的架构的只要从官提供的文件中选择正确架构的文件就行了

除了```portable```需要挑选，其他全部复制
```portable```中需要选择```MemMang```和```[compiler]/[architecture]```下的文件，比如我用的GD32F310F8P6时Cortex-M4架构的，编译器是GCC或者ARMClang选择[portable/GCC/ARM_CM4F](https://github.com/FreeRTOS/FreeRTOS-Kernel/tree/main/portable/GCC/ARM_CM4F)下的文件即可。

需要的FreeRTOS-Kernel的文件如下：

```
FreeRTOS
  │  CMakeLists.txt
  │
  └─Source
      │  CMakeLists.txt
      │  croutine.c
      │  event_groups.c
      │  GitHub-FreeRTOS-Kernel-Home.url
      │  History.txt
      │  LICENSE.md
      │  list.c
      │  manifest.yml
      │  queue.c
      │  Quick_Start_Guide.url
      │  README.md
      │  sbom.spdx
      │  stream_buffer.c
      │  tasks.c
      │  timers.c
      │
      ├─include
      │      atomic.h
      │      croutine.h
      │      deprecated_definitions.h
      │      event_groups.h
      │      FreeRTOS.h
      │      list.h
      │      message_buffer.h
      │      mpu_prototypes.h
      │      mpu_wrappers.h
      │      portable.h
      │      projdefs.h
      │      queue.h
      │      semphr.h
      │      StackMacros.h
      │      stack_macros.h
      │      stdint.readme
      │      stream_buffer.h
      │      task.h
      │      timers.h
      │
      └─portable
          │  CMakeLists.txt
          │
          ├─GCC
          │  └─ARM_CM4F
          │          port.c
          │          portmacro.h
          │
          ├─MemMang
          │      heap_4.c
          │
          └─RVDS
              └─ARM_CM4F
                      port.c
                      portmacro.h
```

### 4.准备一个链接脚本（GCC需要的，Keil跳过）

照抄STM32相同架构的链接脚本，然后改一下分区大小就行。


### 5a.编写CMakeLists

套娃一层一层写就行了，FreeRTOS比较独立，可以编译成静态库，其他全都用INTERFACE就行。比如
```cmake
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
```


### 5b.Keil添加源文件，设置宏和路径

添加的宏如下：
```
GD32F310,PRINTF_INCLUDE_CONFIG_H
```
头文件路径如下：

```
..\..\Source\BSP\inc
..\..\Source\Config
..\..\Source\Core
..\..\Source\Drivers\CMSIS
..\..\Source\Drivers\CMSIS\GD\GD32F3x0\Include
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Include
..\..\Source\Drivers\RTT
..\..\Source\Middlewares\FreeRTOS\Source\include
..\..\Source\Middlewares\FreeRTOS\Source\portable\GCC\ARM_CM4F
..\..\Source\Retarget\inc
```
> ```
> ..\..\Source\BSP\inc;..\..\Source\Config;..\..\Source\Core;..\..\Source\Drivers\CMSIS;..\..\Source\Drivers\CMSIS\GD\GD32F3x0\Include;..\..\Source\Drivers\GD32F3x0_standard_peripheral\Include;..\..\Source\Drivers\RTT;..\..\Source\Middlewares\FreeRTOS\Source\include;..\..\Source\Middlewares\FreeRTOS\Source\portable\GCC\ARM_CM4F;..\..\Source\Retarget\inc
>```

用到的源文件如下

```
..\..\Source\Core\freertos.c
..\..\Source\Core\gd32f3x0_it.c
..\..\Source\Core\main.c

..\..\Source\BSP\src\bsp_log.c
..\..\Source\BSP\src\bsp_systick.c
..\..\Source\BSP\src\bsp_timebase.c
..\..\Source\BSP\src\bsp_uart.c

..\..\Source\Drivers\CMSIS\GD\GD32F3x0\Source\ARM\startup_gd32f3x0.s
..\..\Source\Drivers\CMSIS\GD\GD32F3x0\Source\system_gd32f3x0.c

..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_adc.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_cec.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_cmp.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_crc.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_ctc.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_dac.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_dbg.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_dma.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_exti.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_fmc.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_fwdgt.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_gpio.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_i2c.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_misc.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_pmu.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_rcu.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_rtc.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_spi.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_syscfg.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_timer.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_tsi.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_usart.c
..\..\Source\Drivers\GD32F3x0_standard_peripheral\Source\gd32f3x0_wwdgt.c

..\..\Source\Drivers\RTT\SEGGER_RTT.c
..\..\Source\Drivers\RTT\SEGGER_RTT_printf.c

..\..\Source\Middlewares\FreeRTOS\Source\croutine.c
..\..\Source\Middlewares\FreeRTOS\Source\event_groups.c
..\..\Source\Middlewares\FreeRTOS\Source\list.c
..\..\Source\Middlewares\FreeRTOS\Source\queue.c
..\..\Source\Middlewares\FreeRTOS\Source\stream_buffer.c
..\..\Source\Middlewares\FreeRTOS\Source\tasks.c
..\..\Source\Middlewares\FreeRTOS\Source\timers.c
..\..\Source\Middlewares\FreeRTOS\Source\portable\MemMang\heap_4.c
..\..\Source\Middlewares\FreeRTOS\Source\portable\GCC\ARM_CM4F\port.c

..\..\Source\Retarget\src\printf.c
..\..\Source\Retarget\src\scanf.c
```

## 注意事项

FreeRTOS有三个关键的中断函数
- SysTick_Handler： 时钟驱动，用于节拍计数，定时任务调度，延迟等
- SVC_Handler： 用于初始化FreeRTOS并启动第一个任务。
- PendSV_Handler： 用于在任务调度过程中执行任务上下文切换，确保正确的任务在正确的时间运行。

三个函数在```port.c```中分别以```xPortSysTickHandler```、```vPortSVCHandler```、```xPortPendSVHandler```命名。
也就是说这三个函数默认是要手动调用的，但是可以在```FreeRTOSConfig.h```中用宏重命名三个函数，直接用中断向量表中的名字命名，就不需要手动调用了（当然你也可以去改中断向量表）。官方的原文如下 [FreeRTOS常见问题：我的应用程序没有运行，可能出了什么问题？](https://www.freertos.org/zh-cn-cmn-s/FAQHelp.html)

>针对 ARM Cortex-M 用户的特别提示： ARM Cortex-M3、ARM Cortex-M4 和 ARM Cortex-M4F 端口要求 FreeRTOS 处理程序 安装在 SysTick、 PendSV 和 SVCCall 中断向量上。 可以 将 FreeRTOS 定义的 xPortSysTickHandler()， xPortPendSVHandler() 和 vPortSVCHandler() 函数直接填入向量表的对应位置，或者如果 中断向量表与 CMSIS 相容，可以将以下三行 添加到 FreeRTOSConfig.h，用于将 FreeRTOS 函数名称映射到 其对应的 CMSIS 名称。
>
>#define vPortSVCHandler SVC_Handler
>#define xPortPendSVHandler PendSV_Handler
>#define xPortSysTickHandler SysTick_Handler
>	
>以这种方式使用 #defines 的前提是， 您的开发工具提供的默认处理程序 被定义为弱符号。 如果默认处理程序没有被定义为弱符号， 则需要将其注释掉或删除。
