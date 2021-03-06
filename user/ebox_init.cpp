#include "ebox.h"
#include "mcu.h"


void ebox_init(void)
{
    #ifdef __CC_ARM
        ebox_heap_init((void*)STM32_SRAM_BEGIN, (void*)STM32_SRAM_END);
    #elif __ICCARM__
        ebox_heap_init(__segment_end("HEAP"), (void*)STM32_SRAM_END);
    #else
        ebox_heap_init((void*)&__bss_end, (void*)STM32_SRAM_END);
    #endif
    delay_ms    = mcu_delay_ms;
    delay_us    = mcu_delay_us;
    micros      = mcu_micros;
    millis      = mcu_millis;
    mcu_init();
    
    ebox_printf_init();
    
    
    
}

void ebox_printf_flush(void)
{
    uint16_t len;
    uint8_t ch;
    while(1)
    {
        len = ebox_fifo_get(uart_fifo_ptr,&ch,1);
        if(len == 1)
        {
            uart1.write(ch);
        }
        else
        {
            break;
        }
    }
}
