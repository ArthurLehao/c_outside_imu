#include "bsp_usart.h"

#include "usart.h"

#include "wt16c.h"

uint8_t usart_rx_buff;

void usart_init(void)
{
    HAL_UART_Receive_IT(&huart1, &usart_rx_buff, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)
    {
				wt16c_data_process(usart_rx_buff);
        HAL_UART_Receive_IT(&huart1, &usart_rx_buff, 1);
    }
}
