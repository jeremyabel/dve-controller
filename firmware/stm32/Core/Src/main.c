/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <string.h>

#include "usbd_cdc_if.h"
#include "fifo.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define USE_FULL_ASSERT 1

#define TX_HEADER_SIZE 3
#define TX_PACKET_SIZE 60
#define MIN_PACKET_SIZE 5
#define MAX_PACKET_SIZE 9
#define TX_BUFFER_SIZE 192
#define PC_STATUS_SIZE 5
#define RX_IDLE_WAIT_COUNT 4

#define INACTIVE_BYTE 0x00
#define ACTIVE_BYTE 0x01
#define RECEIVE_OK_BYTE 0x02

#define ERROR_NONE 0x00
#define ERROR_OVERFLOW 0x03
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define SET_ERROR(x) if (currentError != (x)) { currentError = (x); hasErrorChanged = true; }
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_tx;

/* USER CODE BEGIN PV */
volatile uint8_t currentState;
volatile uint8_t currentError;
volatile uint32_t rxIdleCounter;
volatile bool shouldSendPacket;
volatile bool hasErrorChanged;

const uint8_t pcInitPacket[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0x01 };
const uint8_t pcStopPacket[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0x00 };
const uint8_t packetHeader[] = { 0x02, 0x80, 0x86 };

uint8_t txInBuffer[TX_BUFFER_SIZE];
uint8_t txOutBuffer[TX_PACKET_SIZE];
FIFO_Data_Typedef txFifo;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM4_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
bool ReadPCStatusPacket(const uint8_t* targetPacket)
{
	uint8_t dataBuffer[PC_STATUS_SIZE];
	CDC_ReadRxBuffer_FS(dataBuffer, PC_STATUS_SIZE);

	// Compare the buffer with the target packet
	return memcmp(dataBuffer, targetPacket, sizeof(dataBuffer)) == 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	shouldSendPacket = true;
}

void USART1_IRQHandler(void)
{
	// Count the number of idle frames
	if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE))
	{
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
		rxIdleCounter++;
	}

	HAL_UART_IRQHandler(&huart1);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_DEVICE_Init();
  MX_TIM4_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

	rxIdleCounter = 0;
	hasErrorChanged = false;
	shouldSendPacket = false;
	currentState = ConnectionState_Inactive;
	currentError = ERROR_NONE;

	FIFO_Init(&txFifo, txInBuffer, TX_BUFFER_SIZE);

	// Start the 60hz timer
	// TODO: Start this when starting the active state
	HAL_TIM_Base_Start_IT(&htim4);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  hasErrorChanged = false;
	  SET_ERROR(ERROR_NONE);

	  // State: Active
	  if (currentState == ConnectionState_Active)
	  {
		  bool txAvailable = true;
		  uint16_t rxBytesAvailable = CDC_GetRxBufferBytesAvailable_FS();

		  if (rxBytesAvailable)
		  {
			  DEBUGPIN_SET(1);
		  }

		  // Parse any incoming USB packets
		  while (rxBytesAvailable > 0 && txAvailable)
		  {
			  // Check if the PC has sent a status packet
			  if (rxBytesAvailable == PC_STATUS_SIZE)
			  {
				  if (ReadPCStatusPacket(pcStopPacket))
				  {
					  // Reset to the inactive state if the PC quits
					  currentState = ConnectionState_Inactive;

					  // Switch UART1 back to TX-RX mode
					  HAL_UART_DeInit(&huart1);
					  huart1.Init.Mode = UART_MODE_TX_RX;
					  HAL_UART_Init(&huart1);

					  // Disable UART1's IDLE interrupt
					  __HAL_UART_DISABLE_IT(&huart1, UART_IT_IDLE);

					  // Switch the multiplexer over to the DME7000
					  HAL_GPIO_WritePin(Multiplexer_GPIO_Port, Multiplexer_Pin, GPIO_PIN_RESET);

					  // Clear any remaining bytes
					  CDC_FlushRxBuffer_FS();
				  }

				  break;
			  }

			  uint16_t bytesRead = 0;
			  uint8_t dataBuffer[USB_RX_MAX_PACKET_SIZE];
			  if (CDC_ReadRxBufferUntilHeader_FS(dataBuffer, packetHeader, &bytesRead) == USB_CDC_RX_BUFFER_OK)
			  {
				  if (bytesRead == 0)
				  {
					  break;
				  }

				  // Write individual packets into the tx FIFO
				  uint16_t ptr = 0;
				  while (ptr < bytesRead)
				  {
					  // Read and verify the packet size
					  uint8_t packetSize = dataBuffer[ptr] + 1;
					  assert_param(packetSize >= MIN_PACKET_SIZE && packetSize <= MAX_PACKET_SIZE);

					  if (FIFO_WriteAvailable(&txFifo) < packetSize)
					  {
						  SET_ERROR(ERROR_OVERFLOW);
						  txAvailable = false;
						  break;
					  }

					  FIFO_Write(&txFifo, &dataBuffer[ptr], packetSize);

					  ptr += packetSize;
				  }
			  }

			  rxBytesAvailable = CDC_GetRxBufferBytesAvailable_FS();
		  }

		  DEBUGPIN_CLR(1);
	  }

	  // State: Inactive
	  else if (currentState == ConnectionState_Inactive)
	  {
		  // Try and read the initialization packet from the PC
		  uint16_t rxBytesAvailable = CDC_GetRxBufferBytesAvailable_FS();
		  if (rxBytesAvailable == PC_STATUS_SIZE)
		  {
			  if (ReadPCStatusPacket(pcInitPacket))
			  {
				  currentState = ConnectionState_Waiting;
				  rxIdleCounter = 0;

				  // Enable UART1's IDLE interrupt
				  __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
			  }
		  }
		  else if (rxBytesAvailable > 0)
		  {
			  CDC_FlushRxBuffer_FS();
		  }

	  }

	  // State: Waiting
	  else if (currentState == ConnectionState_Waiting)
	  {
		  CDC_FlushRxBuffer_FS();

		  // Wait for a few IDLE frames, then switch to the Active state
		  if (rxIdleCounter >= RX_IDLE_WAIT_COUNT)
		  {
			  currentState = ConnectionState_Active;
			  CDC_FlushRxBuffer_FS();

			  // Switch UART1 to TX-only mode
			  HAL_UART_DeInit(&huart1);
			  huart1.Init.Mode = UART_MODE_TX;
			  HAL_UART_Init(&huart1);

			  // Disable UART1's IDLE interrupt
			  __HAL_UART_DISABLE_IT(&huart1, UART_IT_IDLE);

			  // Switch the multiplexer over to the STM32
			  HAL_GPIO_WritePin(Multiplexer_GPIO_Port, Multiplexer_Pin, GPIO_PIN_SET);
		  }
	  }

	  // Every 16.67ms, send tx packets from the FIFO to the USART
	  if (shouldSendPacket && huart1.gState != HAL_UART_STATE_BUSY_TX)
	  {
		  shouldSendPacket = false;

		  // Clear the tx output buffer and write the header
		  memset(txOutBuffer, 0, TX_PACKET_SIZE);
		  memcpy(txOutBuffer, packetHeader, TX_HEADER_SIZE);

		  uint16_t bytesRead = TX_HEADER_SIZE;
		  uint16_t bytesAvailable = FIFO_ReadAvailable(&txFifo);
		  if (bytesAvailable > MIN_PACKET_SIZE)
		  {
			  DEBUGPIN_SET(4);

			  // Fill the tx buffer with as many packets as will fit
			  while(bytesRead < TX_PACKET_SIZE && bytesAvailable > 0)
			  {
				  // Peek the first byte for the packet size
				  uint8_t packetSize = 0;
				  FIFO_Peek(&txFifo, &packetSize, 1);

				  // Check the packet size range before incrementing it to account for the size indicator byte
				  assert_param(packetSize >= MIN_PACKET_SIZE - 1 && packetSize <= MAX_PACKET_SIZE - 1);
				  packetSize += 1;

				  if (packetSize > (TX_PACKET_SIZE - bytesRead))
				  {
					  break;
				  }

				  FIFO_Read(&txFifo, &txOutBuffer[bytesRead], packetSize);

				  bytesRead += packetSize;
				  bytesAvailable = FIFO_ReadAvailable(&txFifo);
			  }

			  DEBUGPIN_CLR(4);
		  }

		  // Start the DMA transfer
		  HAL_UART_Transmit_DMA(&huart1, txOutBuffer, bytesRead);

		  DEBUGPIN_SET(3);

		  // Write out the status bit. Depending on the state, this will trigger the PC to send another data packet.
		  uint8_t buffer[3] = { 0xFF, currentState == ConnectionState_Active ? ACTIVE_BYTE : INACTIVE_BYTE, currentError };
		  while(CDC_Transmit_FS(buffer, sizeof(buffer)) == USBD_BUSY);

		  DEBUGPIN_CLR(3);

	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 100;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 15840;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 38400;
  huart1.Init.WordLength = UART_WORDLENGTH_9B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_ODD;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 4, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Multiplexer_GPIO_Port, Multiplexer_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 PA2 PA3 PA4
                           PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : Multiplexer_Pin */
  GPIO_InitStruct.Pin = Multiplexer_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Multiplexer_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  assert_param(false);
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	__asm__("BKPT");
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
