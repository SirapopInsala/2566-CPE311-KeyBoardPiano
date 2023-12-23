#include "stm32l1xx.h"
#include "stm32l1xx_ll_system.h"
#include "stm32l1xx_ll_bus.h"
#include "stm32l1xx_ll_utils.h"
#include "stm32l1xx_ll_rcc.h"
#include "stm32l1xx_ll_pwr.h"
#include "stm32l1xx_ll_gpio.h"
#include "stm32l1xx_ll_usart.h"
#include "stm32l1xx_ll_lcd.h"
#include "stm32l152_glass_lcd.h"
#include "stm32l1xx_ll_tim.h"
#include "stm32l1xx_ll_exti.h"
#include "stdio.h"

//00
#define A_00 (uint16_t)27.500
#define Bb_00 (uint16_t)29.135
#define B_00 (uint16_t)30.868

//01
#define C_01 (uint16_t)32.703
#define Db_01 (uint16_t)34.648
#define D_01 (uint16_t)36.708
#define Eb_01 (uint16_t)38.891
#define E_01 (uint16_t)41.203
#define F_01 (uint16_t)43.654
#define Gb_01 (uint16_t)46.249
#define G_01 (uint16_t)48.999
#define Ab_01 (uint16_t)51.913
#define A_01 (uint16_t)55.000
#define Bb_01 (uint16_t)58.270
#define B_01 (uint16_t)61.735

//02
#define C_02 (uint16_t)65.406
#define Db_02 (uint16_t)69.296
#define D_02 (uint16_t)73.416
#define Eb_02 (uint16_t)77.782
#define E_02 (uint16_t)82.407
#define F_02 (uint16_t)87.307
#define Gb_02 (uint16_t)92.499
#define G_02 (uint16_t)97.999
#define Ab_02 (uint16_t)103.83
#define A_02 (uint16_t)110.00
#define Bb_02 (uint16_t)116.54
#define B_02 (uint16_t)123.47

//03
#define C_03 (uint16_t)130.81
#define Db_03 (uint16_t)138.59
#define D_03 (uint16_t)146.83
#define Eb_03 (uint16_t)155.56
#define E_03 (uint16_t)164.81
#define F_03 (uint16_t)174.61
#define Gb_03 (uint16_t)185.00
#define G_03 (uint16_t)196.00
#define Ab_03 (uint16_t)207.65
#define A_03 (uint16_t)220.00
#define Bb_03 (uint16_t)233.08
#define B_03 (uint16_t)246.94

//04
#define C_04 (uint16_t)261.6
#define Db_04 (uint16_t)277.18
#define D_04 (uint16_t)293.67
#define Eb_04 (uint16_t)311.13
#define E_04 (uint16_t)329.67
#define F_04 (uint16_t)349.23
#define Gb_04 (uint16_t)369.99
#define G_04 (uint16_t)392.00
#define Ab_04 (uint16_t)415.30
#define A_04 (uint16_t)440.0
#define Bb_04 (uint16_t)466.16
#define B_04 (uint16_t)493.88

//05
#define C_05 (uint16_t)523.25
#define Db_05 (uint16_t)554.37
#define D_05 (uint16_t)587.33
#define Eb_05 (uint16_t)622.25
#define E_05 (uint16_t)659.26
#define F_05 (uint16_t)698.46
#define Gb_05 (uint16_t)739.99
#define G_05 (uint16_t)783.99
#define Ab_05 (uint16_t)830.61
#define A_05 (uint16_t)880.00
#define Bb_05 (uint16_t)932.33
#define B_05 (uint16_t)987.77

//06
#define C_06 (uint16_t)1046.5
#define Db_06 (uint16_t)1108.7
#define D_06 (uint16_t)1174.7
#define Eb_06 (uint16_t)1244.5
#define E_06 (uint16_t)1318.5
#define F_06 (uint16_t)1396.9
#define Gb_06 (uint16_t)1480.0
#define G_06 (uint16_t)1568.0
#define Ab_06 (uint16_t)1661.2
#define A_06 (uint16_t)1760.0
#define Bb_06 (uint16_t)1864.7
#define B_06 (uint16_t)1975.5

//07
#define C_07 (uint16_t)2093.0
#define Db_07 (uint16_t)2217.5
#define D_07 (uint16_t)2349.3
#define Eb_07 (uint16_t)2489.0
#define E_07 (uint16_t)2637.0
#define F_07 (uint16_t)2793.8
#define Gb_07 (uint16_t)2960.0
#define G_07 (uint16_t)3136.0
#define Ab_07 (uint16_t)3322.4
#define A_07 (uint16_t)3520.0
#define Bb_07 (uint16_t)3729.3
#define B_07 (uint16_t)3951.1

//08
#define C_08 (uint16_t)4186.0

#define MUTE (uint16_t)20000

#define Whole 1600
#define Dotted_Half 1200
#define Half 800
#define Dotted_Quarter 600
#define Quarter 400
#define Dotted_Eighth 300
#define Eighth 200
#define Sixteenth 100


/*for 10ms update event*/
#define TIMx_PSC 2 

/*Macro function for ARR calculation*/
#define ARR_CALCULATE(N) ((32000000) / ((TIMx_PSC) * (N)))

void SystemClock_Config(void);
void PA0_EXTI_Config(void);
void TIM_OC_Config(uint16_t note);
void TIM_BASE_Config(uint16_t ARR);
void TIM_OC_GPIO_Config(void);
void PlayNote(uint16_t note, uint16_t duration);
void TIM_BASE_DurationConfig(void);

char disp_str[5];

int note_01[][2]={
									{F_05,Eighth},{Eb_05,Eighth},{Ab_05,Quarter},{Ab_05,Quarter},{Bb_05,Quarter},{Bb_05,Quarter},{C_06,Quarter},{Ab_05,Quarter},{Eb_05,Quarter},
									{F_05,Eighth},{Eb_05,Eighth},{Ab_05,Quarter},{Ab_05,Quarter},{Bb_05,Quarter},{Bb_05,Quarter},{C_06,Quarter},{Ab_05,Quarter},{MUTE,Quarter},
									{F_05,Eighth},{Eb_05,Eighth},{Ab_05,Quarter},{Ab_05,Quarter},{Bb_05,Quarter},{Bb_05,Quarter},{C_06,Quarter},{Ab_05,Quarter},{Eb_05,Quarter},
									{F_05,Eighth},{Eb_05,Eighth},{Ab_05,Quarter},{Ab_05,Quarter},{Bb_05,Quarter},{Bb_05,Half},{MUTE,Half},
									
									{F_05,Eighth},{Eb_05,Eighth},{Ab_05,Quarter},{Ab_05,Quarter},{Bb_05,Quarter},{Bb_05,Quarter},{C_06,Quarter},{Ab_05,Quarter},{Eb_05,Quarter},
									{F_05,Eighth},{Eb_05,Eighth},{Ab_05,Quarter},{Ab_05,Quarter},{Bb_05,Quarter},{Bb_05,Quarter},{C_06,Quarter},{Bb_05,Half},
									{F_05,Eighth},{Eb_05,Eighth},{Ab_05,Quarter},{Ab_05,Quarter},{Bb_05,Quarter},{Bb_05,Quarter},{C_06,Quarter},{Ab_05,Quarter},{Eb_05,Quarter},
									{F_05,Eighth},{Eb_05,Eighth},{Ab_05,Quarter},{Ab_05,Quarter},{Bb_05,Quarter},{Bb_05,Half},{Eb_05,Half},
									
									{Db_06,Eighth},{C_06,Eighth},{Ab_05,Eighth},{F_06,Quarter},{Ab_05,Eighth},{Bb_05,Eighth},{F_06,Eighth},{Ab_05,Quarter},{Eb_05,Quarter},{F_06,Quarter},{Ab_05,Quarter},
									{Db_06,Eighth},{C_06,Eighth},{Ab_05,Eighth},{F_06,Quarter},{Ab_05,Eighth},{Bb_05,Eighth},{F_06,Eighth},{Ab_05,Quarter}
									};
int size_01=sizeof(note_01)/sizeof(note_01[0]);

int note_02[][2]={
									{C_06,Quarter},{C_06,Quarter},{G_06,Quarter},{G_06,Quarter},{A_06,Quarter},{A_06,Quarter},{G_06,Quarter},{MUTE,Quarter},
									{F_06,Quarter},{F_06,Quarter},{E_06,Quarter},{E_06,Quarter},{D_06,Quarter},{D_06,Quarter},{C_06,Quarter},{MUTE,Quarter},
									{G_06,Quarter},{G_06,Quarter},{F_06,Quarter},{F_06,Quarter},{E_06,Quarter},{E_06,Quarter},{D_06,Quarter},{MUTE,Quarter}
									};
int size_02=sizeof(note_02)/sizeof(note_02[0]);

int note_03[][2]={
									{C_05,Quarter},{Eb_05,Quarter},{F_05,Dotted_Eighth},{Eb_05,Dotted_Eighth},{F_05,Eighth},{F_05,Eighth},{F_05,Eighth},{Bb_05,Eighth},{Ab_05,Eighth},{G_05,Sixteenth},{F_05,Eighth},{G_05,Quarter},
									{G_05,Quarter},{Bb_05,Quarter},{C_06,Dotted_Eighth},{F_05,Dotted_Eighth},{Eb_05,Eighth},{Bb_05,Eighth},{Bb_05,Eighth},{G_05,Eighth},{Bb_05,Eighth},{Bb_05,Dotted_Eighth},{C_06,Whole}
									};
int size_03=sizeof(note_03)/sizeof(note_03[0]);
									
int i=0;
int a=0;

int main()
{
	SystemClock_Config();
	PA0_EXTI_Config();
	LCD_GLASS_Init();

	while(1);
}

void PA0_EXTI_Config(void)
{
	LL_EXTI_InitTypeDef PA0_EXTI_InitStruct;
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA,LL_SYSCFG_EXTI_LINE0);
	PA0_EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_0;
	PA0_EXTI_InitStruct.LineCommand = ENABLE;
	PA0_EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	PA0_EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
	LL_EXTI_Init(&PA0_EXTI_InitStruct);
	
	NVIC_EnableIRQ((IRQn_Type)6);
	NVIC_SetPriority((IRQn_Type)6,0);
}

void EXTI0_IRQHandler(void)
{
	N1:
		if(((EXTI->PR & (1<<0)) == 1) && a==0)
		{
			sprintf(disp_str, "%d", a);
			LCD_GLASS_DisplayString((uint8_t*)disp_str);
			while(1)
			{
				for (int i = 0; i < size_01; ++i)
				{
					PlayNote(note_01[i][0],note_01[i][1]);
					
					if(((EXTI->PR & (1<<0)) == 1) && a==1)
					{
						EXTI->PR |= (1<<0);
						goto N2;
					}
					
					EXTI->PR |= (1<<0);
					a=1;
				}		
			}
		}
	
	N2:
		if(((EXTI->PR & (1<<0)) == 1) && a==1)
		{
			while(1)
			{
				for (int i = 0; i < size_02; ++i)
				{
					PlayNote(note_02[i][0],note_02[i][1]);
					
					if(((EXTI->PR & (1<<0)) == 1) && a==2)
					{
						EXTI->PR |= (1<<0);
						goto N3;
					}
					
					EXTI->PR |= (1<<0);
					a=2;
				}		
			}
		}
	
	N3:
		if(((EXTI->PR & (1<<0)) == 1) && a==2)
		{
			while(1)
			{
				for (int i = 0; i < size_03; ++i)
				{
					PlayNote(note_03[i][0],note_03[i][1]);
					
					if(((EXTI->PR & (1<<0)) == 1) && a==3)
					{
						EXTI->PR |= (1<<0);
						a=0;
						goto N1;
					}
					
					EXTI->PR |= (1<<0);
					a=3;
				}		
			}
		}
		
	sprintf(disp_str, "%d", a);
	LCD_GLASS_DisplayString((uint8_t*)disp_str);
}

void TIM_BASE_Config(uint16_t ARR)
{
	LL_TIM_InitTypeDef timbase_initstructure;
	
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
	//Time-base configure
	timbase_initstructure.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
	timbase_initstructure.CounterMode = LL_TIM_COUNTERMODE_UP;
	timbase_initstructure.Autoreload = ARR - 1;
	timbase_initstructure.Prescaler =  TIMx_PSC- 1;
	LL_TIM_Init(TIM4, &timbase_initstructure);
	
	LL_TIM_EnableCounter(TIM4); 
}

void TIM_OC_GPIO_Config(void)
{
	LL_GPIO_InitTypeDef gpio_initstructure;
	
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
	
	gpio_initstructure.Mode = LL_GPIO_MODE_ALTERNATE;
	gpio_initstructure.Alternate = LL_GPIO_AF_2;
	gpio_initstructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	gpio_initstructure.Pin = LL_GPIO_PIN_6;
	gpio_initstructure.Pull = LL_GPIO_PULL_NO;
	gpio_initstructure.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	LL_GPIO_Init(GPIOB, &gpio_initstructure);
}

void TIM_OC_Config(uint16_t note)
{
	LL_TIM_OC_InitTypeDef tim_oc_initstructure;
	
	TIM_OC_GPIO_Config();
	TIM_BASE_Config(note);
	
	tim_oc_initstructure.OCState = LL_TIM_OCSTATE_DISABLE;
	tim_oc_initstructure.OCMode = LL_TIM_OCMODE_PWM1;
	tim_oc_initstructure.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
	tim_oc_initstructure.CompareValue = LL_TIM_GetAutoReload(TIM4) / 2;
	LL_TIM_OC_Init(TIM4, LL_TIM_CHANNEL_CH1, &tim_oc_initstructure);
	/*Interrupt Configure*/
	NVIC_SetPriority(TIM4_IRQn, 1);
	NVIC_EnableIRQ(TIM4_IRQn);
	LL_TIM_EnableIT_CC1(TIM4);
	
	/*Start Output Compare in PWM Mode*/
	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1);
	LL_TIM_EnableCounter(TIM4);
}

void TIM4_IRQHandler(void)
{
	if(LL_TIM_IsActiveFlag_CC1(TIM4) == SET)
	{
		LL_TIM_ClearFlag_CC1(TIM4);
	}
}

void PlayNote(uint16_t note, uint16_t duration)
{
	TIM_OC_Config(ARR_CALCULATE(note));
	LL_mDelay(duration);
	LL_TIM_DisableCounter(TIM4);
	TIM_OC_Config(ARR_CALCULATE(MUTE)); // Mute sound
	LL_mDelay(duration/4); // Mute duration 200ms
	LL_TIM_DisableCounter(TIM4);
}

void SystemClock_Config(void)
{
  /* Enable ACC64 access and set FLASH latency */ 
  LL_FLASH_Enable64bitAccess();; 
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);

  /* Set Voltage scale1 as MCU will run at 32MHz */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  
  /* Poll VOSF bit of in PWR_CSR. Wait until it is reset to 0 */
  while (LL_PWR_IsActiveFlag_VOSF() != 0)
  {
  };
  
  /* Enable HSI if not already activated*/
  if (LL_RCC_HSI_IsReady() == 0)
  {
    /* HSI configuration and activation */
    LL_RCC_HSI_Enable();
    while(LL_RCC_HSI_IsReady() != 1)
    {
    };
  }
  
	
  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLL_MUL_6, LL_RCC_PLL_DIV_3);

  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };
  
  /* Sysclk activation on the main PLL */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };
  
  /* Set APB1 & APB2 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  /* Set systick to 1ms in using frequency set to 32MHz                             */
  /* This frequency can be calculated through LL RCC macro                          */
  /* ex: __LL_RCC_CALC_PLLCLK_FREQ (HSI_VALUE, LL_RCC_PLL_MUL_6, LL_RCC_PLL_DIV_3); */
  LL_Init1msTick(32000000);
  
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(32000000);
}