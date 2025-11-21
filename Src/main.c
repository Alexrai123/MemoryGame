/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f429i_discovery_lcd.h"//biblioteca destinata gestionarii ecranului LCD pe placa de dezvoltare STM32F429I Discovery
#include "stm32f429i_discovery_sdram.h"//gestionarea SDRAM (Synchronous Dynamic Random Access Memory) de pe placa de dezvoltare
#include "stm32f429i_discovery_ts.h"//biblioteca care gestioneaza ecranul tactil (Touch Screen) de pe placa STM32F429I Discovery
#include "stlogo.h"
#include "usv.h"
#include <stdio.h>
#include <stdbool.h>
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
//variabilele care vor fi utilizate în program si sunt initializate perifericele hardware
DMA2D_HandleTypeDef hdma2d;
I2C_HandleTypeDef hi2c3;
LTDC_HandleTypeDef hltdc;
SPI_HandleTypeDef hspi5;
TIM_HandleTypeDef htim1;
UART_HandleTypeDef huart1;
SDRAM_HandleTypeDef hsdram1;

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);//configurarea ceasului
static void MX_GPIO_Init(void);
//Functii pentru initializarea perifericelor
static void MX_DMA2D_Init(void);
static void MX_FMC_Init(void);
static void MX_I2C3_Init(void);
static void MX_LTDC_Init(void);
static void MX_SPI5_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
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
  uint16_t x1, y1; //utilizate pentru stocarea coordonatelor x si y
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /*resetarea perifericelor, initializeaza interfata Flash si Systick */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /*configurarea ceasului sistemului*/
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /*configurarea initiala a LCD-ului si desenarea ecranului de joc*/
  MX_GPIO_Init();
  MX_DMA2D_Init();
  MX_FMC_Init();
  MX_I2C3_Init();
  MX_LTDC_Init();
  MX_SPI5_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
	
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
	/*initializarea ecranului LCD*/

//Desenarea aspectului vizual al tablei de joc Tic Tac Toe pe ecranul LCD.
	printf("\n\rLaborator-Proiect MICROCONTROLERE\n\r");
	BSP_LCD_Init();//Initializeaza driverul LCD
  BSP_LCD_LayerDefaultInit(LCD_BACKGROUND_LAYER, LCD_FRAME_BUFFER);//initializeaza stratul de fundal de pe afisajul LCD 
	BSP_LCD_LayerDefaultInit(LCD_FOREGROUND_LAYER, LCD_FRAME_BUFFER);//initializeaza stratul de prim-plan al afisajului LCD
  BSP_LCD_SelectLayer(LCD_FOREGROUND_LAYER);//Selecteaza stratul de prim-plan ca strat activ pe care se vor desena elementele ulterior. 
	//Aceasta stabileste pe care dintre cele doua straturi (fundal sau prim-plan) se va desena în mod curent.
  BSP_LCD_DisplayOn();//Activeaza afisajul LCD pentru a începe afisarea informatiilor pe ecran
  BSP_LCD_Clear(LCD_COLOR_BLUE);//Curata stratul activ cu o culoare specificata
	HAL_Delay(400);//O întârziere de 400 de milisecunde (0.4 secunde)
	BSP_LCD_Clear(LCD_COLOR_WHITE);//Curata stratul activ cu o alta culoare 
	BSP_LCD_SetTextColor(LCD_COLOR_RED);//Stabileste culoarea textului pentru afisare la rosu
	BSP_LCD_SetFont(&Font16);//se stabileste fontul cu dimensiunea de 16 pixeli
	
	//desenarea tablei de joc Tic Tac Toe pe ecranul LCD
	BSP_LCD_DisplayStringAtLine(0, (uint8_t*)"     TIC TAC TOE");//afiseaza textul "TIC TAC TOE" la linia 0 a ecranului LCD
	BSP_LCD_DisplayStringAtLine(1, (uint8_t*)"      Player:");//afiseaza textul "Player:" la linia 1 a ecranului LCD
	//se afiseaza cate o linie a tablei de joc de la linia 2 pana la linia 6
	BSP_LCD_DisplayStringAtLine(2, (uint8_t*)"      |       |");
	BSP_LCD_DisplayStringAtLine(3, (uint8_t*)"      |       |");
	BSP_LCD_DisplayStringAtLine(4, (uint8_t*)"      |       |");
	BSP_LCD_DisplayStringAtLine(5, (uint8_t*)"      |       |");
	BSP_LCD_DisplayStringAtLine(6, (uint8_t*)"      |       |");
	//afiseaza o linie orizontala care separa rândurile la linia 7 a ecranului LCD
	BSP_LCD_DisplayStringAtLine(7, (uint8_t*)"------+-------+------");
	//se afiseaza cate o linie a tablei de joc de la linia 8 pana la linia 12
	BSP_LCD_DisplayStringAtLine(8, (uint8_t*)"      |       |");
	BSP_LCD_DisplayStringAtLine(9, (uint8_t*)"      |       |");
	BSP_LCD_DisplayStringAtLine(10, (uint8_t*)"      |       |");
	BSP_LCD_DisplayStringAtLine(11, (uint8_t*)"      |       |");
	BSP_LCD_DisplayStringAtLine(12, (uint8_t*)"      |       |");
	//afiseaza o linie orizontala care separa rândurile la linia 13 a ecranului LCD
	BSP_LCD_DisplayStringAtLine(13, (uint8_t*)"------+-------+------");
	//se afiseaza cate o linie a tablei de joc de la linia 14 pana la linia 18
	BSP_LCD_DisplayStringAtLine(14, (uint8_t*)"      |       |");
	BSP_LCD_DisplayStringAtLine(15, (uint8_t*)"      |       |");
	BSP_LCD_DisplayStringAtLine(16, (uint8_t*)"      |       |");
	BSP_LCD_DisplayStringAtLine(17, (uint8_t*)"      |       |");
	BSP_LCD_DisplayStringAtLine(18, (uint8_t*)"      |       |");
	
//Se vor seta culorile, dimensiunile si fonturile pe ecranul LCD
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);//seteaza culoarea textului pe albastru
	BSP_LCD_SetFont(&Font24);//seteaza fontul pentru text la dimensiunea 24
	
	//BSP_LCD_DisplayStringAt(0, LINE(3), (uint8_t*)"USV", CENTER_MODE); 
	
	BSP_LCD_SetFont(&Font20);//seteaza fontul pentru text la dimensiunea 20
	
	//BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t*)"FIESC", CENTER_MODE);
	
	HAL_Delay(1000);//realizeaza o întârziere de 1000 de milisecunde “1 secunda”
  BSP_LCD_SetFont(&Font16);//seteaza fontul pentru text la dimensiunea 16
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);//seteaza culoarea textului pe negru
	BSP_LCD_SetTextColor(LCD_COLOR_RED);//seteaza culoarea textului pe rosu
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);//seteaza culoarea textului pe negru
//initializeaza functionalitatea touch si verifica daca aceasta s-a realizat cu success
	if (BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize()) == TS_ERROR) 
		{
			//daca nu merge apare mesajul de eroare
			BSP_LCD_DisplayStringAt(0, LINE(11), (uint8_t*)"Eroare initializare touch!", LEFT_MODE);
		}
	//afi?eaza dimensiunile ecranului touch în terminal
	printf("\n\rCoordonate ecran touch: x=%d, y=%d\n\r", BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
  
//pentru a reprezenta faptul ca jucatorul 1 începe jocul
	bool player1 = true;
//flag1 pâna la flag9 cu valoarea false pentru a urmari starea si conditiile în joc
	bool flag1 = false;
	bool flag2 = false;
	bool flag3 = false;
	bool flag4 = false;
	bool flag5 = false;
	bool flag6 = false;
	bool flag7 = false;
	bool flag8 = false;
	bool flag9 = false;

	//bucla în care se verifica starea ecranului tactil ?i se iau decizii în func?ie de aceasta
	while (1)
  {
		
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
		
		BSP_TS_GetState(&TS_State);//informatiile sunt stocate în variabila TS_State 
		////daca touch-ul a fost atins se intra in codul corespunzator
		if(TS_State.TouchDetected)
		{
			x1 = TS_State.X;
			y1 = TS_State.Y;
			//se declara doua buffer-e de caractere pentru a stoca informatii despre coordonate si primul rând
			uint8_t desc[50];
			uint8_t firstline[50];
			sprintf((char *)desc, "Coord. x:%d, y:%d", x1, y1);
			//se afiseaza coordonatele în partea de jos a ecranului (LINE(19)) utilizând BSP_LCD_DisplayStringAt
			BSP_LCD_DisplayStringAt(0, LINE(19), (uint8_t *)desc, LEFT_MODE);
			char a = ' ';
			char b = ' ';
			char c = ' ';
			//sprintf((char *)firstline, "  %s      %s      %s",  a, b, c);
			BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)firstline, LEFT_MODE);
			
//Se verifica coordonatele atinse si afiseaza "X" sau "O" în functie de jucator si locasia pe tabla
//se asigura ca o celula poate fi setata doar o data prin intermediul variabilelor de tip flag
			
			//primul rand
			if((x1>20 && x1<70) && (y1>30 && y1<110) && flag1 == false)
			{
				//BSP_LCD_SetFont(&Font24);
				if(player1 == true)
				{
					BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *) "  X", LEFT_MODE);//se afiseaza X in stanga
				}
				else 
					if (player1 == false)
					{
						BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *) "  O", LEFT_MODE);//se afiseaza O in stanga
					}
					player1 = !player1;
					flag1 = true;
      }
			if((x1>75 && x1<164) && (y1>30 && y1<110) && flag2 == false)
			{
				if(player1 == true)
				{
					BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *) "  X", CENTER_MODE);//se afiseaza X in mijloc
				}
				else 
					if (player1 == false)
					{
						BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *) "  O", CENTER_MODE);//se afiseaza O in mijloc
					}
					player1 = !player1;
					flag2 = true;
			}
			if((x1>170 && x1<225) && (y1>30 && y1<110) && flag3 == false)
			{
				if(player1 == true)
				{
					BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *) "X", RIGHT_MODE);//se afiseaza X in dreapta
				}
				else 
					if (player1 == false)
					{
						BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *) "O", RIGHT_MODE);//se afiseaza O in dreapta
					}
					player1 = !player1;
					flag3 = true;
	    }
			
			//al doilea rand
			if((x1>20 && x1<70) && (y1>120 && y1<210) && flag4 == false)
			{
				if(player1 == true)
				{
					BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *) "  X", LEFT_MODE);//se afiseaza X in stanga
				}
				else 
					if (player1 == false)
					{
						BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *) "  O", LEFT_MODE);//se afiseaza O in stanga
					}
					player1 = !player1;
					flag4 = true;
      }
			if((x1>75 && x1<164) && (y1>130 && y1<210) && flag5 == false)
			{
				if(player1 == true)
				{
					BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *) "  X", CENTER_MODE);//se afiseaza X in centru
				}
				else 
					if (player1 == false)
					{
						BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *) "  O", CENTER_MODE);//se afiseaza O in centru
					}
					player1 = !player1;
					flag5 = true;
			}
			if((x1>170 && x1<225) && (y1>130 && y1<210) && flag6 == false)
			{
				if(player1 == true)
				{
					BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *) "X", RIGHT_MODE);//se afiseaza X in dreapta
				}
				else 
					if (player1 == false)
					{
						BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *) "O", RIGHT_MODE);//se afiseaza O in dreapta
					}
					player1 = !player1;
					flag6 = true;
	    }	
			
			// al treilea rand
			if((x1>20 && x1<70) && (y1>219 && y1<300) && flag7 == false)
			{
				if(player1 == true)
				{
					BSP_LCD_DisplayStringAt(0, LINE(15), (uint8_t *) "  X", LEFT_MODE);//se afiseaza X in stanga
				}
				else 
					if (player1 == false)
					{
						BSP_LCD_DisplayStringAt(0, LINE(15), (uint8_t *) "  O", LEFT_MODE);//se afiseaza O in stanga
					}
					player1 = !player1;
					flag7 = true;
      }
			if((x1>75 && x1<164) && (y1>219 && y1<300) && flag8 == false)
			{
				if(player1 == true)
				{
					BSP_LCD_DisplayStringAt(0, LINE(15), (uint8_t *) "  X", 	CENTER_MODE);//se afiseaza X in centru
				}
				else 
					if (player1 == false)
					{
						BSP_LCD_DisplayStringAt(0, LINE(15), (uint8_t *) "  O", 	CENTER_MODE);//se afiseaza O in centru
					}
					player1 = !player1;
					flag8 = true;
			}
			else 
				if((x1>170 && x1<225) && (y1>219 && y1<300) && flag9 == false)
				{
					if(player1 == true)
					{
						BSP_LCD_DisplayStringAt(0, LINE(15), (uint8_t *) "X", RIGHT_MODE);//se afiseaza X in dreapta
					}
					else 
						if (player1 == false)
						{
							BSP_LCD_DisplayStringAt(0, LINE(15), (uint8_t *) "O", RIGHT_MODE);//se afiseaza O in dreapta
						}
						player1 = !player1;
						flag9 = true;
				}		
		}
		else 
		{
			
		}
		HAL_Delay(50);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};//se defineste o structura pentru configurarea oscilatoarelor
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};//se defineste o structura pentru configurarea ceasurilor CPU, AHB si APB
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};//se defineste o structura pentru configurarea ceasurilor pentru periferice

	
  __HAL_RCC_PWR_CLK_ENABLE();//se activeaza ceasul pentru blocul de control al consumului de energie “Power Control”
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);//se configureaza nivelul de tensiune al regulatorului pentru a obtine performante optime
 
	
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;//se specifica tipul oscilatorului
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;//se activeaza oscilatorul HSE
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;//se ajusteaza frecventa oscilatorului principal
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;//se specifica sursa pentru PLL, care este HSE
  RCC_OscInitStruct.PLL.PLLM = 8;//se specifica divizorul M pentru PLL
  RCC_OscInitStruct.PLL.PLLN = 336;//se specifica factorul de multiplicare N pentru PLL
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;//se specifica divizorul P pentru PLL
  RCC_OscInitStruct.PLL.PLLQ = 5;//se specifica divizorul Q pentru PLL
	
	//se aplica configuratia oscilatorului si se verifica daca configurarea a fost realizata cu succes
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  
	//se specifica tipurile de ceasuri care vor fi configurate
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	//se specifica sursa pentru ceasul de sistem „SYSCLK” ca fiind PLL
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;////se specifica divizorul pentru ceasul AHB
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;//se specifica divizorul pentru ceasul APB1
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;//se specifica divizorul pentru ceasul APB2
	
	//se aplica configuratia ceasurilor si se verifica daca configurarea a fost realizata cu succes
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
	
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;//se specifica perifericul LTDC pentru care se configureaza ceasul
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 192;//se specifica factorul de multiplicare SAIN pentru PLLSAI
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;//se specifica factorul de reducere SAIR pentru PLLSAI
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;//se specifica divizorul pentru PLLSAI
	
	//se aplica configura?ia pentru perifericul LTDC ?i se verifica daca configurarea a fost realizata cu succes
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief DMA2D Initialization Function
  * @param None
  * @retval None
  */

//setarea si initializarea DMA2D pentru a efectua operatii de transfer de la memorie cu anumite configuratii de culoare si alfa
static void MX_DMA2D_Init(void)
{
  /* USER CODE BEGIN DMA2D_Init 0 */
  /* USER CODE END DMA2D_Init 0 */
  /* USER CODE BEGIN DMA2D_Init 1 */
  /* USER CODE END DMA2D_Init 1 */
  hdma2d.Instance = DMA2D;//Seteaza instanta DMA2D utilizata
  hdma2d.Init.Mode = DMA2D_M2M;//Configureaza modul DMA2D pentru transfer de la memorie la memorie
  hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB565;//Specifica modul de culoare pentru operatiile de transfer 
  hdma2d.Init.OutputOffset = 0; //Specifica offset-ul pentru destinatia transferului
  hdma2d.LayerCfg[1].InputOffset = 0; //Specifica offset-ul pentru sursa transferului
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB565;//Specifica modul de culoare pentru sursa transferului 
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;//Modificarea alfa nu este utilizata
  hdma2d.LayerCfg[1].InputAlpha = 0;//Valoarea alfa pentru sursa transferului
	
	//În cazul în care initializarea DMA2D nu reuseste, declanseaza o eroare
  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
    Error_Handler();
  }
	
	//În cazul în care configurarea stratului DMA2D nu reu?e?te, declan?eaza o func?ie de gestionare a erorilor
  if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
  {
    Error_Handler();
  }
	
  /* USER CODE BEGIN DMA2D_Init 2 */
  /* USER CODE END DMA2D_Init 2 */
}

/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */

//configureaza si initializeaza modulul I2C3 pe microcontroller
static void MX_I2C3_Init(void)
{
  /* USER CODE BEGIN I2C3_Init 0 */
  /* USER CODE END I2C3_Init 0 */
  /* USER CODE BEGIN I2C3_Init 1 */
  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;//seteaza instanta I2C3 utilizata
  hi2c3.Init.ClockSpeed = 100000;//seteaza viteza de comunica?ie la 100kHz
  hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;//se seteaza ciclul de lucru al semnalului I2C la 2
  hi2c3.Init.OwnAddress1 = 0;//se seteaza adresa proprie a dispozitivului I2C, nu este folosita în modul 7 biti
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;//se dezactiveaza modul de adresare duala
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;//se seteaza a doua adresa proprie
  hi2c3.Init.OwnAddress2 = 0;//se seteaza a doua adresa proprie
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;//se dezactiveaza modul de apel general
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;//se dezactiveaza modul de întindere a perioadelor de ceas
	//initializeaza I2C3 cu configuratiile specificate si verifica daca initializarea a avut succes
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }
	
  /** Configure Analogue filter 
  */
	
	//configureaza filtrul analog si verifica daca configurarea a avut succes
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_DISABLE) != HAL_OK)
  {
    Error_Handler();
  }
	
  /** Configure Digital filter 
  */
	
	//se configureaza filtrul digital si verifica daca configurarea a avut succes
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK)
  {
    Error_Handler();
  }
	
  /* USER CODE BEGIN I2C3_Init 2 */
  /* USER CODE END I2C3_Init 2 */
}

/**
  * @brief LTDC Initialization Function
  * @param None
  * @retval None
  */
static void MX_LTDC_Init(void)
{
  /* USER CODE BEGIN LTDC_Init 0 */
  /* USER CODE END LTDC_Init 0 */
  LTDC_LayerCfgTypeDef pLayerCfg = {0};//structura de configurare a stratului LTDC
  /* USER CODE BEGIN LTDC_Init 1 */
  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;//se seteaza instanta LTDC utilizata
	//configurarile de baza ale LTDC
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;//polaritatea orizontala a semnalului de sincronizare
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;//polaritatea verticala a semnalului de sincronizare
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;//polaritatea semnalului Data Enable
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;//polaritatea semnalului de pixel clock
	//configureaza caracteristicile temporale si spatiale ale semnalului video care controleaza afisarea pe ecran
  hltdc.Init.HorizontalSync = 9;//se seteaza durata sincronizarii orizontale în pixeli
  hltdc.Init.VerticalSync = 1;//se specifica câte linii sunt utilizati pentru semnalul de sincronizare verticala
  hltdc.Init.AccumulatedHBP = 29;//se seteaza numarul total de pixeli pentru sincronizarea orizontala si back porch, aceasta reprezinta suma dintre durata sincronizarii orizontale si back porch
  hltdc.Init.AccumulatedVBP = 3;//se seteaza numarul total de linii pentru sincronizarea verticala si back porch
  hltdc.Init.AccumulatedActiveW = 269;//se seteaza numarul total de pixeli pe linie, inclusiv zona activa a ecranului si zonele de sincronizare orizontala si back porch
  hltdc.Init.AccumulatedActiveH = 323;//se seteaza numarul total de linii, inclusiv zona activa a ecranului si zonele de sincronizare verticala si back porch
  hltdc.Init.TotalWidth = 279;//se seteaza latimea totala a liniei video
  hltdc.Init.TotalHeigh = 327;//se seteaza înal?imea totala a cadrului video
  hltdc.Init.Backcolor.Blue = 0;//se seteaza componenta albastra a culorii de fundal (background) a ecranului
  hltdc.Init.Backcolor.Green = 0;//se seteaza componenta verde a culorii de fundal a ecranului
  hltdc.Init.Backcolor.Red = 0;//se seteaza componenta ro?ie a culorii de fundal a ecranului
	//in cazul în care initializarea LTDC nu reuseste, declanseaza o functie de gestionare a erorilor
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
	//configurarile specifice stratului (layer) LTDC
	//definirea ferestrei de afisare
  pLayerCfg.WindowX0 = 0;//coordonata X a coltului stânga-sus al ferestrei straturii (layer), aceasta indica începutul zonei active pe axa orizontala
  pLayerCfg.WindowX1 = 240;//coordonata X a coltului dreapta-jos al ferestrei straturii (layer), aceasta indica sfârsitul zonei active pe axa orizontala
  pLayerCfg.WindowY0 = 0;//coordonata Y a coltului stânga-sus al ferestrei straturii (layer), aceasta indica începutul zonei active pe axa verticala
  pLayerCfg.WindowY1 = 320;//coordonata Y a coltului dreapta-jos al ferestrei straturii (layer), aceasta indica sfârsitul zonei active pe axa verticala
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;//formatul pixelilor, unde sunt alocate 5 biti pentru rosu, 6 biti pentru verde si 5 biti pentru albastru
  pLayerCfg.Alpha = 255;//nivelul de transparenta, nivelul de 255 înseamna ca stratul este complet opac, fara transparenta
  pLayerCfg.Alpha0 = 0;//se seteaza nivelul de opacitate al pixelilor care au o valoare de transparenta (alpha) de 0
	//factorii de amestecare „blending” a culorilor
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;//culoarea stratului este multiplicata cu nivelul de transparenta (alpha) 1
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;//culoarea stratului este multiplicata cu nivelul de transparenta (alpha) 2
  pLayerCfg.FBStartAdress = 0;//adresa de început este setata la 0, ceea ce ar putea însemna ca datele sunt stocate în prima zona a memoriei RAM
  pLayerCfg.ImageWidth = 240;//latimea imaginii pe acest strat, acest lucru indica câti pixeli sunt prezentati pe axa orizontala
  pLayerCfg.ImageHeight = 320;//înaltimea imaginii pe acest strat, acest lucru indica câti pixeli sunt prezentati pe axa verticala
  pLayerCfg.Backcolor.Blue = 0;//componenta de culoare albastra a culorii de fundal a stratului
  pLayerCfg.Backcolor.Green = 0;//componenta de culoare verde a culorii de fundal a stratului
  pLayerCfg.Backcolor.Red = 0;//componenta de culoare ro?ie a culorii de fundal a stratului
	//in cazul în care configurarea stratului LTDC nu reuseste, declanseaza o functie de gestionare a erorilor
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */
  /* USER CODE END LTDC_Init 2 */
}

/**
  * @brief SPI5 Initialization Function
  * @param None
  * @retval None
  */

//o initializare a perifericului SPI5 (Serial Peripheral Interface) în cadrul unui proiect bazat pe platforma STM32
static void MX_SPI5_Init(void)
{
  /* USER CODE BEGIN SPI5_Init 0 */
  /* USER CODE END SPI5_Init 0 */
  /* USER CODE BEGIN SPI5_Init 1 */
  /* USER CODE END SPI5_Init 1 */
  /* SPI5 parameter configuration*/
  hspi5.Instance = SPI5;//se specifica instanta SPI pe care se va face initializarea SPI5
  hspi5.Init.Mode = SPI_MODE_MASTER;//se configureaza modul de operare al SPI ca master, masterul controleaza comunicatia
  hspi5.Init.Direction = SPI_DIRECTION_2LINES;//configurare pentru doua linii de date, adica o linie de date MOSI (Master Out, Slave In) si o linie de date MISO (Master In, Slave Out)
  hspi5.Init.DataSize = SPI_DATASIZE_8BIT;//dimensiunea datelor este setata la 8 biti pe transfer
  hspi5.Init.CLKPolarity = SPI_POLARITY_LOW;//se specifica polaritatea semnalului de ceas (CLK) ca fiind LOW în starea de repaus
  hspi5.Init.CLKPhase = SPI_PHASE_1EDGE;//se specifica faza în care datele sunt stabilite sau citite, pe prima margine de urcare 
  hspi5.Init.NSS = SPI_NSS_SOFT;//se utilizeaza NSS software, ceea ce înseamna ca gestionarea semnalului NSS (Slave Select) este realizata software
  hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;//se seteaza prescaler-ul pentru stabilirea ratei de transfer de date, este setat la 16
  hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;//se specifica ordinea de transmisie a bitilor, cel mai semnificativ bit este transmis primul
  hspi5.Init.TIMode = SPI_TIMODE_DISABLE;//dezactiveaza modul de comunicare prin transfer de mesaje 
  hspi5.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;//dezactiveaza calculul CRC (Cyclic Redundancy Check) pentru integritatea datelor
  hspi5.Init.CRCPolynomial = 10;//daca CRC este activat, aici se specifica polinomul utilizat pentru calcul
	//fragmentul de cod verifica daca initializarea perifericului SPI5 (HAL_SPI_Init(&hspi5)) a fost realizata cu succes sau nu
  if (HAL_SPI_Init(&hspi5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI5_Init 2 */
  /* USER CODE END SPI5_Init 2 */
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
//configureaza si initializeaza un timer hardware
static void MX_TIM1_Init(void)
{
  /* USER CODE BEGIN TIM1_Init 0 */
  /* USER CODE END TIM1_Init 0 */
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};//se declara o structura pentru configurarea sursei de ceas a timerului
  TIM_MasterConfigTypeDef sMasterConfig = {0};//se declara o structura de tip pentru configurarea modului maestru al timerului
	
  /* USER CODE BEGIN TIM1_Init 1 */
  /* USER CODE END TIM1_Init 1 */
	
  htim1.Instance = TIM1;//se specifica instanta hardware a timerului
  htim1.Init.Prescaler = 0;//se seteaza prescaler-ul timerului la 0
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;//se configureaza modulul de numarare al timerului ca fiind "UP"
  htim1.Init.Period = 0;//se seteaza valoarea la care timerul va ajunge înainte de a se reseta
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;//se configureaza divizarea ceasului timerului
  htim1.Init.RepetitionCounter = 0;//se seteaza un contor de repetare
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;//se dezactiveaza încarcarea automata a valorii de auto-reîncarcare
	//Se initializeaza timerul de baza folosind configuratia specificata. Daca initializarea nu reuseste, se apeleaza Error_Handler().
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;//se configureaza sursa interna de ceas pentru timer
	//Se aplica configurarea sursei de ceas timerului. În cazul unei erori, se apeleaza Error_Handler().
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;//se configureaza semnalul de iesire al modului maestru pentru a reseta timerul
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;//se dezactiveaza modulul maestru-sclav al timerului
	//Se aplica configurarea modului maestru al timerului. În cazul unei erori, se apeleaza Error_Handler()
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */
  /* USER CODE END TIM1_Init 2 */
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
  huart1.Instance = USART1;//se specifica instanta hardware a modulului
  huart1.Init.BaudRate = 115200;//se configureaza rata de baud a modulului UART la 115200 biti pe secunda
  huart1.Init.WordLength = UART_WORDLENGTH_8B;//se seteaza lungimea cuvântului la 8 biti
  huart1.Init.StopBits = UART_STOPBITS_1;//se configureaza numarul de biti de stop la 1
  huart1.Init.Parity = UART_PARITY_NONE;//se dezactiveaza paritatea
  huart1.Init.Mode = UART_MODE_TX_RX;//se configureaza modulul UART pentru transmitere si receptie simultana
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;//se dezactiveaza controlul hardware al fluxului
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;//se seteaza oversampling-ul la 16x
	//se initializeaza modulul UART folosind configura?ia specificata. Daca initializarea nu reuseste, se apeleaza Error_Handler().
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
	
  /* USER CODE BEGIN USART1_Init 2 */
	
	SET_BIT(huart1.Instance->CR1, USART_CR1_RXNEIE);//activeaza întreruperea pentru evenimentul de receptie
  HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);//se configureaza prioritatea pentru întreruperea legata de USART1
  HAL_NVIC_EnableIRQ(USART1_IRQn);//se activeaza întreruperea pentru USART1
	
  /* USER CODE END USART1_Init 2 */
}

/* FMC initialization function */
static void MX_FMC_Init(void)
{
  /* USER CODE BEGIN FMC_Init 0 */
  /* USER CODE END FMC_Init 0 */
	
  FMC_SDRAM_TimingTypeDef SdramTiming = {0};//se defineste o structura numita SdramTiming pentru a configura timpii specifici SDRAM
	
  /* USER CODE BEGIN FMC_Init 1 */
  /* USER CODE END FMC_Init 1 */
  /** Perform the SDRAM1 memory initialization sequence
  */
	
  hsdram1.Instance = FMC_SDRAM_DEVICE;//se specifica instanta hardware a modulului FMC pentru memorie SDRAM
	
  /* hsdram1.Init */
	
  hsdram1.Init.SDBank = FMC_SDRAM_BANK2;//se configureaza numarul de biti pentru adresa coloanei SDRAM la 8 biti
  hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;//se configureaza numarul de biti pentru adresa coloanei SDRAM la 8 biti
  hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;//se configureaza numarul de biti pentru adresa rândului SDRAM la 12 biti
  hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;//se seteaza latimea datelor la 16 biti
  hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;//se specifica numarul intern de banci SDRAM
  hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;//se configureaza latenta CAS a SDRAM la 3 cicluri
  hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;//se dezactiveaza protectia la scriere pentru SDRAM
  hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;//se configureaza perioada de ceas pentru SDRAM la 2 cicluri
  hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_DISABLE;//se dezactiveaza modul de citire burst
  hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_1;//se configureaza delay-ul pentru read pipe la 1 ciclu
	
  /* SdramTiming */
	
  SdramTiming.LoadToActiveDelay = 2;//se configureaza delay-ul de la Load Mode la Active Mode
  SdramTiming.ExitSelfRefreshDelay = 7;//se configureaza delay-ul pentru a iesi din Self Refresh Mode
  SdramTiming.SelfRefreshTime = 4;//se configureaza timpul de auto-refresh pentru SDRAM
  SdramTiming.RowCycleDelay = 7;//se configureaza delay-ul pentru ciclul de rând al SDRAM
  SdramTiming.WriteRecoveryTime = 3;//se configureaza timpul de recuperare pentru scriere
  SdramTiming.RPDelay = 2;//se configureaza delay-ul pentru Precharge
  SdramTiming.RCDDelay = 2;//se configureaza delay-ul pentru Read to Write Delay
	//se initializeaza modulul SDRAM folosind configuratia specificata în structura SdramTiming. Daca initializarea nu reuseste, se apeleaza Error_Handler()
  if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
  {
    Error_Handler( );
  }
  /* USER CODE BEGIN FMC_Init 2 */
  /* USER CODE END FMC_Init 2 */
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};//se declara o structura pentru a configura parametrii GPIO
	
  /* GPIO Ports Clock Enable */
	
  __HAL_RCC_GPIOC_CLK_ENABLE();//se activeaza ceasul pentru portul GPIOC
  __HAL_RCC_GPIOF_CLK_ENABLE();//se activeaza ceasul pentru portul GPIOF
  __HAL_RCC_GPIOH_CLK_ENABLE();//se activeaza ceasul pentru portul GPIOH
  __HAL_RCC_GPIOA_CLK_ENABLE();//se activeaza ceasul pentru portul GPIOA
  __HAL_RCC_GPIOB_CLK_ENABLE();//se activeaza ceasul pentru portul GPIOB
  __HAL_RCC_GPIOG_CLK_ENABLE();//se activeaza ceasul pentru portul GPIOG
  __HAL_RCC_GPIOE_CLK_ENABLE();//se activeaza ceasul pentru portul GPIOE
  __HAL_RCC_GPIOD_CLK_ENABLE();//se activeaza ceasul pentru portul GPIOD

  /*Configure GPIO pin Output Level */
	
	//se scrie nivelul logic "RESET" pe pinii 1, 2 ?i 4
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
	
	//se scrie nivelul logic "RESET" pe pinul 7
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
	
	//se scrie nivelul logic "RESET" pe pinii 12 si 13
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
	
	//se scrie nivelul logic "RESET" pe pinii 13 si 14
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC1 PC2 PC4 */
	
	//se specifica pinii 1, 2 si 4 de pe portul GPIOC care vor fi configurati
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//se configureaza modul de lucru pentru pinii specificati ca iesiri cu push-pull
  GPIO_InitStruct.Pull = GPIO_NOPULL;//se configureaza modul de pull-up/pull-down pentru pinii specificati ca "None"
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;//se configureaza viteza de comutare pentru pinii specificati la o frecventa redusa
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);//se aplica configurarea pentru portul GPIOC

  /*Configure GPIO pins : PA0 PA1 PA2 PA15 */
	
	//se specifica pinii  0, 1, 2 si 15 de pe portul GPIOA care vor fi configurati
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;//se configureaza modul de lucru pentru pinii specifica?i ca intrari cu declansare la nivel crescator
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);//se aplica configurarea pentru portul GPIOA

  /*Configure GPIO pin : PA7 */
	
  GPIO_InitStruct.Pin = GPIO_PIN_7;//specifica pinul 7 de pe portul GPIOA pentru configuratie
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//configureaza pinul 7 de pe portul GPIOA ca iesire cu push-pull
  GPIO_InitStruct.Pull = GPIO_NOPULL;//configurare fara rezistenta de pull pentru pinul 7 de pe portul GPIOA
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;//configureaza viteza de comutare a pinului 7 de pe portul GPIOA la o frecventa scazuta
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);//aplica configurarea pentru portul GPIOA pe pinul 7

  /*Configure GPIO pin : PC5 */
	
  GPIO_InitStruct.Pin = GPIO_PIN_5;//specifica pinul 5 de pe portul GPIOC pentru configuratie
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;//configureaza pinul 5 de pe portul GPIOC ca intrare cu declansare la nivel crescator
  GPIO_InitStruct.Pull = GPIO_NOPULL;//configurare fara rezistenta de pull pentru pinul 5 de pe portul GPIOC
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);//aplica configurarea pentru portul GPIOC pe pinul 5

  /*Configure GPIO pin : PB2 */
	
  GPIO_InitStruct.Pin = GPIO_PIN_2;//specifica pinul 2 de pe portul GPIOB pentru configuratie
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;//configureaza pinul 2 de pe portul GPIOB ca intrare
  GPIO_InitStruct.Pull = GPIO_NOPULL;//configurare fara rezistenta de pull pentru pinul 2 de pe portul GPIOB
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);//aplica configurarea pentru portul GPIOB pe pinul 2

  /*Configure GPIO pins : PB12 PB14 PB15 */
	
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_14|GPIO_PIN_15;//specifica pinii 12, 14 si 15 de pe portul GPIOB pentru configuratie
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;//configureaza pinii 12, 14 si 15 de pe portul GPIOB ca iesiri alternative cu push-pull
  GPIO_InitStruct.Pull = GPIO_NOPULL;//configurare fara rezistenta de pull pentru pinii 12, 14 si 15 de pe portul GPIOB
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//configureaza viteza de comutare pentru pinii 12, 14 si 15 de pe portul GPIOB la o frecventa foarte înalta
  GPIO_InitStruct.Alternate = GPIO_AF12_OTG_HS_FS;//configureaza functia alternativa a pinilor 12, 14 si 15 de pe portul GPIOB
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);//aplica configurarea pentru portul GPIOB pe pinii 12, 14 si 15

  /*Configure GPIO pin : PB13 */
	
  GPIO_InitStruct.Pin = GPIO_PIN_13;//specifica pinul 13 de pe portul GPIOB pentru configuratie
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;//configureaza pinul 13 de pe portul GPIOB ca intrare
  GPIO_InitStruct.Pull = GPIO_NOPULL;//configurare fara rezistenta de pull pentru pinul 13 de pe portul GPIOB
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);//aplica configurarea pentru portul GPIOB pe pinul 13

  /*Configure GPIO pin : PD11 */
	
  GPIO_InitStruct.Pin = GPIO_PIN_11;//specifica pinul 11 de pe portul GPIOD pentru configuratie
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;//configureaza pinul 11 de pe portul GPIOD ca intrare
  GPIO_InitStruct.Pull = GPIO_NOPULL;//configurare fara rezistenta de pull pentru pinul 11 de pe portul GPIOD
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);//aplica configurarea pentru portul GPIOD pe pinul 11

  /*Configure GPIO pins : PD12 PD13 */
	
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;//specifica pinii 12 si 13 de pe portul GPIOD pentru configuratie
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//configureaza pinii 12 si 13 de pe portul GPIOD ca iesiri cu push-pull
  GPIO_InitStruct.Pull = GPIO_NOPULL;//configurare fara rezistenta de pull pentru pinii 12 si 13 de pe portul GPIOD
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;//configureaza viteza de comutare pentru pinii 12 si 13 de pe portul GPIOD la o frecventa scazuta
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);//aplica configurarea pentru portul GPIOD pe pinii 12 si 13

  /*Configure GPIO pins : PG13 PG14 */
	
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;//specifica pinii 13 si 14 de pe portul GPIOG pentru configuratie
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//configureaza pinii 13 si 14 de pe portul GPIOG ca iesiri cu push-pull
  GPIO_InitStruct.Pull = GPIO_NOPULL;//configurare fara rezistenta de pull pentru pinii 13 si 14 de pe portul GPIOG
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;//configureaza viteza de comutare pentru pinii 13 si 14 de pe portul GPIOG la o frecventa scazuta
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);//aplica configurarea pentru portul GPIOG pe pinii 13 si 14
}

/* USER CODE BEGIN 4 */
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */

// transmitere a unui singur caracter catre UART
PUTCHAR_PROTOTYPE
{
  /* write a character to the uart1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF); 
  return ch;
}

/* USER CODE END 4 */
 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */

// gestionarea întreruperilor de la timer în cadrul bibliotecii HAL
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) 
	{
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  /* USER CODE END Callback 1 */
}

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