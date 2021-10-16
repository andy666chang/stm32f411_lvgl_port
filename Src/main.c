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
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "SSD1306.h"

#include "lvgl.h"
#include "lv_port_disp.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
void lvgl_first_demo_start(void);
void lvgl_test(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
    MX_I2C1_Init();
    /* USER CODE BEGIN 2 */

    OLED_initial( );
    lv_init();
    lv_port_disp_init();

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    OLED_clear();
    SSD1306_Set_Inverse_Display();
    SSD1306_Set_XY( 100 , 3 );
    OLED_write_num(2);

    lvgl_first_demo_start();
//  lvgl_test();


    while (1)
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
//    static bool inverse = 0 ;
//    inverse = !inverse ;
//
//    (inverse)? SSD1306_Set_Normal_Display() : SSD1306_Set_Inverse_Display();
//    HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
        HAL_Delay(10);
//    lvgl_first_demo_start();
        lv_task_handler();
//    lv_timer_handler();
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
    /** Initializes the CPU, AHB and APB busses clocks
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 12;
    RCC_OscInitStruct.PLL.PLLN = 96;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB busses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
    {
        Error_Handler();
    }
    /** Enables the Clock Security System
    */
    HAL_RCC_EnableCSS();
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

    /* USER CODE BEGIN I2C1_Init 0 */

    /* USER CODE END I2C1_Init 0 */

    /* USER CODE BEGIN I2C1_Init 1 */

    /* USER CODE END I2C1_Init 1 */
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 400000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN I2C1_Init 2 */

    /* USER CODE END I2C1_Init 2 */

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
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : LED_Pin */
    GPIO_InitStruct.Pin = LED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

static void anim_x_cb(void * var, int32_t v)
{
    lv_obj_set_x(var, v);
}

static void anim_size_cb(void * var, int32_t v)
{
    lv_obj_set_size(var, v, v);
}
void lvgl_first_demo_start(void)
{
//    lv_obj_t * label2 = lv_label_create(lv_scr_act());
//    lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL_CIRCULAR);     /*Circular scroll*/
//    lv_obj_set_width(label2, 150);
//    lv_label_set_text(label2, "It is a circularly scrolling text. ");
//	
//		lv_obj_set_y(label2, 0);
	
//		lv_obj_t * label3 = lv_label_create(lv_scr_act());
//    lv_label_set_long_mode(label3, LV_LABEL_LONG_SCROLL_CIRCULAR);     /*Circular scroll*/
//    lv_obj_set_width(label3, 150);
//    lv_label_set_text(label3, "It is a circularly scrolling text. ");
//	
//		lv_obj_set_y(label3, 32);

    lv_obj_t * obj = lv_obj_create(lv_scr_act());
    lv_obj_set_style_bg_color(obj, lv_palette_main(_LV_PALETTE_LAST), 0);
    lv_obj_set_style_radius(obj, LV_RADIUS_CIRCLE, 0);
		lv_obj_set_size(obj, 60, 60);

    lv_obj_align(obj, LV_ALIGN_LEFT_MID, -30, 0);	

   lv_anim_t a;
   lv_anim_init(&a);
   lv_anim_set_var(&a, obj);
   lv_anim_set_values(&a, 60, 60);
   lv_anim_set_time(&a, 500);
   lv_anim_set_playback_delay(&a, 100);
   lv_anim_set_playback_time(&a, 500);
   lv_anim_set_repeat_delay(&a, 100);
   lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
   lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);

   lv_anim_set_exec_cb(&a, anim_size_cb);
   lv_anim_start(&a);
   lv_anim_set_exec_cb(&a, anim_x_cb);
   lv_anim_set_values(&a, -30, LV_HOR_RES-30);
   lv_anim_start(&a);

}

/*
void my_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    // flush with byte
    uint32_t i = 0 , j = 0 , k = 0 ;
    uint8_t pixel_buff[LV_HOR_RES_MAX] = {0} ;

    if ( area->y1 == 0 && area->y2 == 63 && area->x1 == 0 && area->x2 == LV_HOR_RES_MAX - 1 )
    {
        for ( i = 0 ; i < 8 ; i++ ) // 8 line
        {
            SSD1306_Set_XY( 0 , i );
            memset( pixel_buff , 0 , sizeof(pixel_buff) );
            for ( k = 0 ; k <= 7 ; k++ )
            {
                for (  j = 0 ; j < LV_HOR_RES_MAX ; j++) // LV_HOR_RES_MAX horizontal
                {
                    pixel_buff[j] |= lv_color_to1(*color_p) << (k);
                    color_p++;
                }
            }
            // write 64 byte to screen
            SSD1306_Write( SSD1306_SLAVE_ADDRESS , NORMAL_MODE_ADDRESS , pixel_buff , LV_HOR_RES_MAX );
        }
    }


//     IMPORTANT!!!
//     Inform the graphics library that you are ready with the flushing
    lv_disp_flush_ready(disp_drv);
}

#define BUF_W LV_HOR_RES_MAX
#define BUF_H LV_VER_RES_MAX
lv_color_t buf[BUF_W * BUF_H] = {0};
void lvgl_test(void)
{
    lv_color_t * buf_p = buf;
    uint16_t x, y;
    for (y = 0; y < LV_VER_RES_MAX; y++) {
        for (x = 0; x < LV_HOR_RES_MAX; x++) {
            if ( x > 20 && x < 40 && y > 20 && y < 40 )
                buf_p->full =  0xff;
            buf_p++;
        }
    }

    buf[50 * 100 + 0].full = 0xff ;

    lv_area_t a;
    a.x1 = 0;
    a.y1 = 0;
    a.x2 = LV_HOR_RES_MAX - 1;
    a.y2 = LV_VER_RES_MAX - 1;
    my_flush_cb(NULL, &a, buf);
}
*/
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

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
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
