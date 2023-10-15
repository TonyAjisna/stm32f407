#include "./BSP/DMA/dma.h"
#include "./SYSTEM/delay/delay.h"


DMA_HandleTypeDef g_dma_handle;             /* DMA��� */

extern UART_HandleTypeDef g_uart1_handle;         /* UART��� */


/* 
    ����TX DMA��ʼ������
    ����Ĵ�����ʽ�ǹ̶��ģ����Ҫ���ݲ�ͬ��������޸�
    �Ӵ洢��-> ����ģʽ/8λ���ݿ��/�洢������ģʽ
*/
void dma_init(DMA_Stream_TypeDef *dma_stream_handle, uint32_t ch)
{
    if ((uint32_t)dma_stream_handle > (uint32_t)DMA2)       /* �õ���ǰstream������DMA1����DMA2 */
    {
        __HAL_RCC_DMA2_CLK_ENABLE();                        /* DMA2ʱ��ʹ�� */
    }
    else
    {
        __HAL_RCC_DMA1_CLK_ENABLE();                        /* DMA1ʱ��ʹ�� */
    }
    
    __HAL_LINKDMA(&g_uart1_handle, hdmatx, g_dma_handle);   /* ��DMA��USART1��ϵ����������DMA�� */

    /* Tx DMA���� */
    g_dma_handle.Instance = dma_stream_handle;                    /* ������ѡ�� */
    g_dma_handle.Init.Channel = ch;                               /* DMAͨ��ѡ�� */
    g_dma_handle.Init.Direction = DMA_MEMORY_TO_PERIPH;           /* �洢�������� */
    g_dma_handle.Init.PeriphInc = DMA_PINC_DISABLE;               /* ���������ģʽ */
    g_dma_handle.Init.MemInc = DMA_MINC_ENABLE;                   /* �洢������ģʽ */
    g_dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;  /* �������ݳ���:8λ */
    g_dma_handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;     /* �洢�����ݳ���:8λ */
    g_dma_handle.Init.Mode = DMA_NORMAL;                          /* ��������ģʽ */
    g_dma_handle.Init.Priority = DMA_PRIORITY_MEDIUM;             /* �е����ȼ� */
    g_dma_handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;            /* �ر�FIFOģʽ */
    g_dma_handle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;    /* FIFO��ֵ���� */
    g_dma_handle.Init.MemBurst = DMA_MBURST_SINGLE;               /* �洢��ͻ�����δ��� */
    g_dma_handle.Init.PeriphBurst = DMA_PBURST_SINGLE;            /* ����ͻ�����δ��� */

    HAL_DMA_DeInit(&g_dma_handle);
    HAL_DMA_Init(&g_dma_handle);
}

