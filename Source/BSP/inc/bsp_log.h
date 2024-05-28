#ifndef _BSP_LOG_H_
#define _BSP_LOG_H_

#define USE_SEGGER_RTT 0
#define USE_UART 1

/**
 * @def 日志模式
 * @brief 指定当前日志输出模式（USE_SEGGER_RTT 或 USE_UART）。
 */
#define LOG_MODE USE_SEGGER_RTT

#include <stdio.h>
#if LOG_MODE == USE_SEGGER_RTT
#include "SEGGER_RTT.h"
static inline void Log_Init()
{
	SEGGER_RTT_Init();
}
#elif LOG_MODE == USE_UART
#include "printf.h"
#include "bsp_uart.h"
#endif

/**
 * @defgroup 基础接口 组 基础日志接口
 * @brief 提供一系列基础日志输出宏。
 * @{
 */

/**
 * @brief 向选定的日志接口输出格式化字符串。
 * @param format 格式字符串，后跟可选参数。
 */
#if LOG_MODE == USE_SEGGER_RTT
#define printf(format, ...) SEGGER_RTT_printf(0, format, ##__VA_ARGS__)
#elif LOG_MODE == USE_UART
#define printf(format, ...) printf_(format, ##__VA_ARGS__)
#endif

/**
 * @brief 向日志接口发送字符串。
 * @param string 要发送的字符串。
 */
#if LOG_MODE == USE_SEGGER_RTT
#define puts(string) SEGGER_RTT_WriteString(0, string)
#elif LOG_MODE == USE_UART
#define puts(string) UART_Send((const uint8_t *)string, strlen(string))
#endif

/**
 * @brief 向日志接口发送指定长度的字符串。
 * @param string 要发送的字符串。
 * @param len 字符串长度。
 */
#if LOG_MODE == USE_SEGGER_RTT
#define putsn(string, len) SEGGER_RTT_Write(0, string, len)
#elif LOG_MODE == USE_UART
#define putsn(string, len) UART_Send((const uint8_t *)string, len)
#endif

/**
 * @defgroup DEBUG模式扩展接口 组 DEBUG模式下的扩展日志接口
 * @brief 在DEBUG模式下提供更丰富的日志与断言功能。
 * @{
 */

#ifdef DEBUG

/**
 * @brief 数据传输通用接口。
 * @param pData 待发送的数据指针。
 * @param len 数据长度。
 */
#define TRANSMIT(pData, len) putsn(pData, len)

/**
 * @brief 打印日志信息。
 * @param format 格式字符串，后跟可变参数列表。
 */
#define LOG(format, ...) printf(format "\r\n", ##__VA_ARGS__)

/**
 * @brief 打印信息日志，前缀为[INFO]。
 * @param string 信息字符串。
 */
#define INFO(string) puts("[INFO]:" string "\r\n")

/**
 * @brief 打印错误日志，包含错误位置信息。
 * @param format 错误信息格式字符串，后跟可变参数列表。
 */
#define ERROR(format, ...) printf("\n[ERROR]%s: " format "\r\n", __func__, ##__VA_ARGS__)

/**
 * @brief 断言表达式，失败时打印错误信息。
 * @param expr 需要验证的表达式。
 */
#define ASSERT(expr) ((expr) ? (int)0U : printf("[ASSERT]:%s:%d,%s", __FILE__, __LINE__, #expr))

#else
// 非DEBUG模式下，上述宏定义为空操作，以优化性能
#define TRANSMIT(pData, len)
#define LOG(format, ...)
#define INFO(format, ...)
#define ERROR(format, ...)
#define ASSERT(expr)
#endif /*DEBUG*/

#ifdef __cplusplus
extern "C" {
#endif
void assert_failed(char *file, uint32_t line);

#ifdef __cplusplus
}
#endif
#endif /* _BSP_LOG_H_ */
