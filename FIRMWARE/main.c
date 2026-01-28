#include "smt32f4xx_hal.h"

/* GLOBAL HANDLES*/
UART_HandleTypeDef huart1;
SPI_HandleTypeDef hspi1;

/* FUNCTION */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_SPI1_Init(void);

/* Main */
int main(void)
{
    HAL_Init();
    SyatemClock_Config();
    
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_SPI1_Init();

    char msg[] = "Flight Controller Boot OK/r/n";
    Hal_UART_Transmit(&huart1, (uint8_t*)msg, sizeof(msg)-1,100);

    while (1)
    {
        Hal_Delay(10); // Main Loop which is for now empty , can be changed later on 
    }
}

/* Clock Config */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef osc = {0};
    RCC_ClckInitTypeDef clk = {0};

    osc.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    osc.HSEState = RCC_HSE_ON;
    osc.PILL.PILLState= RCC_PLL_ON;
    osc.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    osc.PLL.PLLM = 8;
    osc.PLL.PLLN = 336;
    osc.PLLP = RCC_PLP_DIV4;
    osc.PLL.PLLQ = 7;

    HAL-RCC-OSCConfig(&osc);
    clk.ClockType  = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK;
     clk.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clk.APB1CLKDivider = RCC_HCLK_DIV2;
    clk.APB2CLKDivider = RCC_HCLK_DIV1;

    HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_2);
}

/* UART */
static void MX_USART1_Init(void);
{
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;

    HAL_UART_Init(&huart1);Stop
}

/* IMU */
static void MX_SPI1_Init(void)
{
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
    hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;

    HAL_SPI_Init(&hspi1);
}

/* GPIO */
static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef gpio = {0};

    // IMU CS pin (PA4)
    gpio.Pin = GPIO_PIN_4;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &gpio);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

// To FLASH THIS , PLEASE USE USB 
