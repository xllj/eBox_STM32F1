/**
  ******************************************************************************
  * @file    core.h
  * @author  shentq
  * @version V1.2
  * @date    2016/08/14
  * @brief   此文件为ebox核心文件,提供了诸多非常重要的接口,可以被标准的c文件调用。
  ******************************************************************************
  * @attention
  *
  * No part of this software may be used for any commercial activities by any form 
  * or means, without the prior written consent of shentq. This specification is 
  * preliminary and is subject to change at any time without notice. shentq assumes
  * no responsibility for any errors contained herein.
  * <h2><center>&copy; Copyright 2015 shentq. All Rights Reserved.</center></h2>
  ******************************************************************************
  */
/**
 * Modification History:
 * -shentq                  -version 1.2(2016/08/17)
 *      *修复了芯片主频只能限制为72Mhz的限制，支持任意主频
 *      *增加了cpu的信息获取，包括各个总线时钟，芯片容量，芯片计算加加的能力
 */


/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __CORE_H
#define __CORE_H


#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f10x.h"
#include "ebox_type.h"
#include "mcu_config.h"

#define interrupts() 		__enable_irq()//允许所有中断
#define no_interrupts() 	__disable_irq()//禁止所有中断
	




/*!< 2 bits for pre-emption priority
2 bits for subpriority */
#define NVIC_GROUP_CONFIG NVIC_PriorityGroup_2//以后NVIC_PriorityGroupConfig()函数不需要再被调用。更不能再以非NVIC_GROUP_CONFIG值填充调用


typedef void (*callback_fun_type)(void);

///////全局变量、函数///////////////////////////////////////////////
extern __IO uint64_t millis_seconds;//提供一个mills()等效的全局变量。降低cpu调用开销

void mcu_init(void); //ebox系统初始化
void mcu_reset(void);
uint32_t get_cpu_calculate_per_sec(void);//获取cpu在不跑操作系统的情况下的计算能力。用于统计cpu绝对使用率

uint64_t mcu_micros(void);//获取系统当前运行了多长时间。单位：us
uint64_t mcu_millis(void);//获取系统当前运行了多长时间。单位：ms
void mcu_delay_ms(uint64_t ms);//延时n毫秒。可在任意情况下使用，包括禁止所有中断的情况。精度正负1us。
void mcu_delay_us(uint64_t us);//延时n微秒。可在任意情况下使用，包括禁止所有中断的情况。精度正负1us。
void set_systick_user_event_per_sec(u16 frq);//设定用户中断事件的相应频率。frq[1,1000],frq最好是2的倍数
void attach_systick_user_event(void (*callback_fun)(void));//绑定systick中断调用函数，调用频率由用户决定，频率为1hz-1000hz



#ifdef __cplusplus
}
#endif
#endif
