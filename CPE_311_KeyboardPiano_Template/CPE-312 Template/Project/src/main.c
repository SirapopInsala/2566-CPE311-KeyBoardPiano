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
void initial_setting(void);
void TIM_OC_Config(uint16_t note);
void TIM_BASE_Config(uint16_t ARR);
void TIM_OC_GPIO_Config(void);
void PlayNote(uint16_t note, uint16_t duration);

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
int b=1;
int K=1;
int L=4;
int R=0;
int P=0;
int T=0;
									
int record[16]={0};

int C_note[]={C_01,C_02,C_03,C_04,C_05,C_06,C_07};
int Db_note[]={Db_01,Db_02,Db_03,Db_04,Db_05,Db_06,Db_07};
int D_note[]={D_01,D_02,D_03,D_04,D_05,D_06,D_07};
int Eb_note[]={Eb_01,Eb_02,Eb_03,Eb_04,Eb_05,Eb_06,Eb_07};
int E_note[]={E_01,E_02,E_03,E_04,E_05,E_06,E_07};
int F_note[]={F_01,F_02,F_03,F_04,F_05,F_06,F_07};
int Gb_note[]={Gb_01,Gb_02,Gb_03,Gb_04,Gb_05,Gb_06,Gb_07};
int G_note[]={G_01,G_02,G_03,G_04,G_05,G_06,G_07};
int Ab_note[]={Ab_01,Ab_02,Ab_03,Ab_04,Ab_05,Ab_06,Ab_07};
int A_note[]={A_01,A_02,A_03,A_04,A_05,A_06,A_07};
int Bb_note[]={Bb_01,Bb_02,Bb_03,Bb_04,Bb_05,Bb_06,Bb_07};
int B_note[]={B_01,B_02,B_03,B_04,B_05,B_06,B_07};

int main()
{
	SystemClock_Config();
	initial_setting();
	
	//LED RGB
	RCC->AHBENR |= (1<<0);
	//1
	//LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_10, LL_GPIO_MODE_OUTPUT);
	GPIOA->MODER |= (1<<20) | (1<<18) | (1<<16); //PA10,9,8
	//2
	GPIOA->MODER |= (1<<26) | (1<<24) | (1<<22); //PA13,12,11
	//3
	GPIOA->MODER |= (1<<30) | (1<<28); //PA15,14
	GPIOC->MODER |= (1<<20); //PC10
		
	while(1){
//		if(L==0)
//			{
//				GPIOA->ODR |= (1<<13);
//			}
//		if(L==1)
//			{
//				GPIOA->ODR |= (1<<12);
//			}
//		if(L==2)
//			{
//				GPIOA->ODR |= (1<<11);
//			}
//		if(L==3)
//			{
//				GPIOA->ODR |= (1<<13);
//				GPIOA->ODR |= (1<<12);
//			}
//		if(L==4)
//			{
//				GPIOA->ODR |= (1<<13);
//				GPIOA->ODR |= (1<<11);
//			}
//		if(L==5)
//			{
//				GPIOA->ODR |= (1<<12);
//				GPIOA->ODR |= (1<<11);
//			}
//		if(L==6)
//			{
//				GPIOA->ODR |= (1<<13);
//				GPIOA->ODR |= (1<<12);
//				GPIOA->ODR |= (1<<11);
//			}
		}
}

void initial_setting(void)
{
	//USER
	//A0
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
	
	//NOTE
	//A1
	LL_EXTI_InitTypeDef PA1_EXTI_InitStruct;
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA,LL_SYSCFG_EXTI_LINE1);
	PA1_EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_1;
	PA1_EXTI_InitStruct.LineCommand = ENABLE;
	PA1_EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	PA1_EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;	
	LL_EXTI_Init(&PA1_EXTI_InitStruct);
	NVIC_EnableIRQ((IRQn_Type)7);
	NVIC_SetPriority((IRQn_Type)7,0);

	//A2
	LL_EXTI_InitTypeDef PA2_EXTI_InitStruct;
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA,LL_SYSCFG_EXTI_LINE2);
	PA2_EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_2;
	PA2_EXTI_InitStruct.LineCommand = ENABLE;
	PA2_EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	PA2_EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;	
	LL_EXTI_Init(&PA2_EXTI_InitStruct);
	NVIC_EnableIRQ((IRQn_Type)8);
	NVIC_SetPriority((IRQn_Type)8,0);
	
	//A3
	LL_EXTI_InitTypeDef PA3_EXTI_InitStruct;
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA,LL_SYSCFG_EXTI_LINE3);
	PA3_EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_3;
	PA3_EXTI_InitStruct.LineCommand = ENABLE;
	PA3_EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	PA3_EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;	
	LL_EXTI_Init(&PA3_EXTI_InitStruct);
	NVIC_EnableIRQ((IRQn_Type)9);
	NVIC_SetPriority((IRQn_Type)9,0);

	//A4
	LL_EXTI_InitTypeDef PA4_EXTI_InitStruct;
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA,LL_SYSCFG_EXTI_LINE4);
	PA4_EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_4;
	PA4_EXTI_InitStruct.LineCommand = ENABLE;
	PA4_EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	PA4_EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;	
	LL_EXTI_Init(&PA4_EXTI_InitStruct);
	NVIC_EnableIRQ((IRQn_Type)10);
	NVIC_SetPriority((IRQn_Type)10,0);
	
	//A5
	LL_EXTI_InitTypeDef PA5_EXTI_InitStruct;
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA,LL_SYSCFG_EXTI_LINE5);
	PA5_EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_5;
	PA5_EXTI_InitStruct.LineCommand = ENABLE;
	PA5_EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	PA5_EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;	
	LL_EXTI_Init(&PA5_EXTI_InitStruct);
	NVIC_EnableIRQ((IRQn_Type)23);
	NVIC_SetPriority((IRQn_Type)23,0);
	
	//B10
	LL_EXTI_InitTypeDef PB10_EXTI_InitStruct;
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB,LL_SYSCFG_EXTI_LINE10);
	PB10_EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_10;
	PB10_EXTI_InitStruct.LineCommand = ENABLE;
	PB10_EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	PB10_EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;	
	LL_EXTI_Init(&PB10_EXTI_InitStruct);
	NVIC_EnableIRQ((IRQn_Type)40);
	NVIC_SetPriority((IRQn_Type)40,0);
	
	//B11
	LL_EXTI_InitTypeDef PB11_EXTI_InitStruct;
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB,LL_SYSCFG_EXTI_LINE11);
	PB11_EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_11;
	PB11_EXTI_InitStruct.LineCommand = ENABLE;
	PB11_EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	PB11_EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;	
	LL_EXTI_Init(&PB11_EXTI_InitStruct);
	NVIC_EnableIRQ((IRQn_Type)40);
	NVIC_SetPriority((IRQn_Type)40,0);
	
	//B12 
	LL_EXTI_InitTypeDef PB12_EXTI_InitStruct;
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB,LL_SYSCFG_EXTI_LINE12);
	PB12_EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_12;
	PB12_EXTI_InitStruct.LineCommand = ENABLE;
	PB12_EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	PB12_EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;	
	LL_EXTI_Init(&PB12_EXTI_InitStruct);
	NVIC_EnableIRQ((IRQn_Type)40);
	NVIC_SetPriority((IRQn_Type)40,0);
	
	//B13
	LL_EXTI_InitTypeDef PB13_EXTI_InitStruct;
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB,LL_SYSCFG_EXTI_LINE13);
	PB13_EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_13;
	PB13_EXTI_InitStruct.LineCommand = ENABLE;
	PB13_EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	PB13_EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;	
	LL_EXTI_Init(&PB13_EXTI_InitStruct);
	NVIC_EnableIRQ((IRQn_Type)40);
	NVIC_SetPriority((IRQn_Type)40,0);
	
	//B14
	LL_EXTI_InitTypeDef PB14_EXTI_InitStruct;
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB,LL_SYSCFG_EXTI_LINE14);
	PB14_EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_14;
	PB14_EXTI_InitStruct.LineCommand = ENABLE;
	PB14_EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	PB14_EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;	
	LL_EXTI_Init(&PB14_EXTI_InitStruct);
	NVIC_EnableIRQ((IRQn_Type)40);
	NVIC_SetPriority((IRQn_Type)40,0);
	
	//B15
	LL_EXTI_InitTypeDef PB15_EXTI_InitStruct;
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB,LL_SYSCFG_EXTI_LINE15);
	PB15_EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_15;
	PB15_EXTI_InitStruct.LineCommand = ENABLE;
	PB15_EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	PB15_EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;	
	LL_EXTI_Init(&PB15_EXTI_InitStruct);
	NVIC_EnableIRQ((IRQn_Type)40);
	NVIC_SetPriority((IRQn_Type)40,0);
	
	//C7
	LL_EXTI_InitTypeDef PC7_EXTI_InitStruct;
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC,LL_SYSCFG_EXTI_LINE7);
	PC7_EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_7;
	PC7_EXTI_InitStruct.LineCommand = ENABLE;
	PC7_EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	PC7_EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;	
	LL_EXTI_Init(&PC7_EXTI_InitStruct);
	NVIC_EnableIRQ((IRQn_Type)23);
	NVIC_SetPriority((IRQn_Type)23,0);

	//UP,DOWN
	//C8
	LL_EXTI_InitTypeDef PC8_EXTI_InitStruct;
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC,LL_SYSCFG_EXTI_LINE8);
	PC8_EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_8;
	PC8_EXTI_InitStruct.LineCommand = ENABLE;
	PC8_EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	PC8_EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;	
	LL_EXTI_Init(&PC8_EXTI_InitStruct);
	NVIC_EnableIRQ((IRQn_Type)23);
	NVIC_SetPriority((IRQn_Type)23,0);
	
	//RECORD
	//C9
	LL_EXTI_InitTypeDef PC9_EXTI_InitStruct;
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC,LL_SYSCFG_EXTI_LINE9);
	PC9_EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_9;
	PC9_EXTI_InitStruct.LineCommand = ENABLE;
	PC9_EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	PC9_EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;	
	LL_EXTI_Init(&PC9_EXTI_InitStruct);
	NVIC_EnableIRQ((IRQn_Type)23);
	NVIC_SetPriority((IRQn_Type)23,0);
}

void EXTI0_IRQHandler(void)
{
	rec:
		if(((EXTI->PR & (1<<0)) == 1) && a==0)
		{
			if(P==0)
			{
				a=1;
				EXTI->PR |= (1<<0);
				goto N1;
			}
			else
			{
				while(1)
				{
					for (i = 0 ; i < P ; ++i)
					{
						PlayNote(record[i],Half);
						
						if(((EXTI->PR & (1<<0)) == 1) && a==1)
						{
							goto N1;
						}
						
						EXTI->PR |= (1<<0);
						a=1;
					}		
				}
			}
		}
		
 	N1:
		if(((EXTI->PR & (1<<0)) == 1) && a==1)
		{
			while(1)
			{
				for (i = 0; i < size_01; ++i)
				{
					PlayNote(note_01[i][0],note_01[i][1]);
					
					if(((EXTI->PR & (1<<0)) == 1) && a==2)
					{
						goto N2;
					}
					
					EXTI->PR |= (1<<0);
					a=2;
				}		
			}
		}
	
	N2:
		if(((EXTI->PR & (1<<0)) == 1) && a==2)
		{
			while(1)
			{
				for (i = 0; i < size_02; ++i)
				{
					PlayNote(note_02[i][0],note_02[i][1]);
					
					if(((EXTI->PR & (1<<0)) == 1) && a==3)
					{
						goto N3;
					}
					
					EXTI->PR |= (1<<0);
					a=3;
				}		
			}
		}
	
	N3:
		if(((EXTI->PR & (1<<0)) == 1) && a==3)
		{
			while(1)
			{
				for (i = 0; i < size_03; ++i)
				{
					PlayNote(note_03[i][0],note_03[i][1]);
					
					if(((EXTI->PR & (1<<0)) == 1) && a==4)
					{
						a=0;
						goto rec;
					}
					
					EXTI->PR |= (1<<0);
					a=4;
				}		
			}
		}
}

void EXTI1_IRQHandler(void)
{
	//A1 C
	if((EXTI->PR & (1<<1)) == (1<<1))
	{
		if(b==1)
		{
			TIM_OC_Config(ARR_CALCULATE(C_note[L]));
			b=0;			
			GPIOA->ODR |= (1<<10);
			GPIOA->ODR |= (1<<12);
			if(R==1 && P<16)
			{
				record[P]=C_note[L];
				P=P+1;
			}
		}
		else
		{
			TIM_OC_Config(ARR_CALCULATE(MUTE));
			b=1;
			GPIOA->ODR &= ~(1<<10);		
			GPIOA->ODR &= ~(1<<12);
		}
		EXTI->PR |= (1<<1);
	}
}

void EXTI2_IRQHandler(void)
{
	//A2 Db
	if((EXTI->PR & (1<<2)) == (1<<2))
	{
		if(b==1)
		{
			TIM_OC_Config(ARR_CALCULATE(Db_note[L]));
			b=0;
			GPIOA->ODR |= (1<<9);
			GPIOA->ODR |= (1<<11);
			if(R==1 && P<16)
			{
				record[P]=Db_note[L];
				P=P+1;
			}
		}
		else
		{
			TIM_OC_Config(ARR_CALCULATE(MUTE));
			b=1;
			GPIOA->ODR &= ~(1<<9);
			GPIOA->ODR &= ~(1<<11);
		}
		EXTI->PR |= (1<<2);
	}
}

void EXTI3_IRQHandler(void)
{
	//A3 D
	if((EXTI->PR & (1<<3)) == (1<<3))
	{
		if(b==1)
		{
			TIM_OC_Config(ARR_CALCULATE(D_note[L]));
			b=0;
			GPIOA->ODR |= (1<<8);
			GPIOA->ODR |= (1<<13);
			if(R==1 && P<16)
			{
				record[P]=D_note[L];
				P=P+1;
			}
		}
		else
		{
			TIM_OC_Config(ARR_CALCULATE(MUTE));
			b=1;
			GPIOA->ODR &= ~(1<<8);
			GPIOA->ODR &= ~(1<<13);
		}
		EXTI->PR |= (1<<3);
	}
}

void EXTI4_IRQHandler(void)
{
	//A4 Eb
	if((EXTI->PR & (1<<4)) == (1<<4))
	{
		if(b==1)
		{
			TIM_OC_Config(ARR_CALCULATE(Eb_note[L]));
			b=0;
			GPIOA->ODR |= (1<<10);
			GPIOA->ODR |= (1<<9);
			GPIOA->ODR |= (1<<11);
			if(R==1 && P<16)
			{
				record[P]=Eb_note[L];
				P=P+1;
			}
		}
		else
		{
			TIM_OC_Config(ARR_CALCULATE(MUTE));
			b=1;
			GPIOA->ODR &= ~(1<<10);
			GPIOA->ODR &= ~(1<<9);
			GPIOA->ODR &= ~(1<<11);
		}
		EXTI->PR |= (1<<4);
	}
}

void EXTI9_5_IRQHandler(void)
{
	//A5 E
	if((EXTI->PR & (1<<5)) == (1<<5))
	{
		if(b==1)
		{
			TIM_OC_Config(ARR_CALCULATE(E_note[L]));
			b=0;
			GPIOA->ODR |= (1<<10);
			GPIOA->ODR |= (1<<8);
			GPIOA->ODR |= (1<<12);
			if(R==1 && P<16)
			{
				record[P]=E_note[L];
				P=P+1;
			}
		}
		else
		{
			TIM_OC_Config(ARR_CALCULATE(MUTE));
			b=1;
			GPIOA->ODR &= ~(1<<10);
			GPIOA->ODR &= ~(1<<8);
			GPIOA->ODR &= ~(1<<12);
		}
		EXTI->PR |= (1<<5);
	}
	
	//B7 B
	if((EXTI->PR & (1<<7)) == (1<<7))
	{
		if(b==1)
		{
			TIM_OC_Config(ARR_CALCULATE(B_note[L]));
			b=0;
			GPIOA->ODR |= (1<<10);
			GPIOA->ODR |= (1<<8);			
			GPIOA->ODR |= (1<<13);
			GPIOA->ODR |= (1<<12);
			if(R==1 && P<16)
			{
				record[P]=B_note[L];
				P=P+1;
			}
		}
		else
		{
			TIM_OC_Config(ARR_CALCULATE(MUTE));
			b=1;
			GPIOA->ODR &= ~(1<<10);
			GPIOA->ODR &= ~(1<<8);			
			GPIOA->ODR &= ~(1<<13);
			GPIOA->ODR &= ~(1<<12);
		}
		EXTI->PR |= (1<<7);
	}
	
	//B8 UP DOWN
	if((EXTI->PR & (1<<8)) == (1<<8))
	{		
		if(K==1)
		{
			L++;
			LL_mDelay(200);
			if(L==6)
			{
				K=0;
			}
		}
		else
		{
			L--;
			LL_mDelay(200);
			if(L==0)
			{
				K=1;
			}
		}
		EXTI->PR |= (1<<7);
	}
	
	//B9 RECORD
	if((EXTI->PR & (1<<9)) == (1<<9))
	{
		if(R==0)
		{
			GPIOA->ODR |= (1<<15);
			GPIOA->ODR |= (1<<14);
			GPIOC->ODR |= (1<<10);
			R=1;
			P=0;
			LL_mDelay(200);
		}
		else
		{
			GPIOA->ODR &= ~(1<<15);
			GPIOA->ODR &= ~(1<<14);
			GPIOC->ODR &= ~(1<<10);
			R=0;
			LL_mDelay(200);
		}
		EXTI->PR |= (1<<9);
	}
}

void EXTI15_10_IRQHandler(void)
{
	//B10 F
	if((EXTI->PR & (1<<10)) == (1<<10))
	{
		if(b==1)
		{
			TIM_OC_Config(ARR_CALCULATE(F_note[L]));
			b=0;
			GPIOA->ODR |= (1<<9);
			GPIOA->ODR |= (1<<8);
			GPIOA->ODR |= (1<<13);
			if(R==1 && P<16)
			{
				record[P]=F_note[L];
				P=P+1;
			}
		}
		else
		{
			TIM_OC_Config(ARR_CALCULATE(MUTE));
			b=1;
			GPIOA->ODR &= ~(1<<9);
			GPIOA->ODR &= ~(1<<8);
			GPIOA->ODR &= ~(1<<13);
		}
		EXTI->PR |= (1<<10);
	}
	
	//B11 Gb
	if((EXTI->PR & (1<<11)) == (1<<11))
	{
		if(b==1)
		{
			TIM_OC_Config(ARR_CALCULATE(Gb_note[L]));
			b=0;
			GPIOA->ODR |= (1<<10);
			GPIOA->ODR |= (1<<12);
			GPIOA->ODR |= (1<<11);
			if(R==1 && P<16)
			{
				record[P]=Gb_note[L];
				P=P+1;
			}
		}
		else
		{
			TIM_OC_Config(ARR_CALCULATE(MUTE));
			b=1;
			GPIOA->ODR &= ~(1<<10);
			GPIOA->ODR &= ~(1<<12);
			GPIOA->ODR &= ~(1<<11);
		}
		EXTI->PR |= (1<<11);
	}
	
	//B12 G
	if((EXTI->PR & (1<<12)) == (1<<12))
	{
		if(b==1)
		{
			TIM_OC_Config(ARR_CALCULATE(G_note[L]));
			b=0;
			GPIOA->ODR |= (1<<9);
			GPIOA->ODR |= (1<<13);
			GPIOA->ODR |= (1<<11);
			if(R==1 && P<16)
			{
				record[P]=G_note[L];
				P=P+1;
			}
		}
		else
		{
			TIM_OC_Config(ARR_CALCULATE(MUTE));
			b=1;
			GPIOA->ODR &= ~(1<<9);
			GPIOA->ODR &= ~(1<<13);
			GPIOA->ODR &= ~(1<<11);
		}
		EXTI->PR |= (1<<12);
	}
	
	//B13 Ab
	if((EXTI->PR & (1<<13)) == (1<<13))
	{
		if(b==1)
		{
			TIM_OC_Config(ARR_CALCULATE(Ab_note[L]));
			b=0;
			GPIOA->ODR |= (1<<8);
			GPIOA->ODR |= (1<<13);
			GPIOA->ODR |= (1<<12);
			if(R==1 && P<16)
			{
				record[P]=Ab_note[L];
				P=P+1;
			}
		}
		else
		{
			TIM_OC_Config(ARR_CALCULATE(MUTE));
			b=1;
			GPIOA->ODR &= ~(1<<8);
			GPIOA->ODR &= ~(1<<13);
			GPIOA->ODR &= ~(1<<12);
		}
		EXTI->PR |= (1<<13);
	}
	
	//B14 A
	if((EXTI->PR & (1<<14)) == (1<<14))
	{
		if(b==1)
		{
			TIM_OC_Config(ARR_CALCULATE(A_note[L]));
			b=0;
			GPIOA->ODR |= (1<<10);
			GPIOA->ODR |= (1<<9);
			GPIOA->ODR |= (1<<12);
			GPIOA->ODR |= (1<<11);
			if(R==1 && P<16)
			{
				record[P]=A_note[L];
				P=P+1;
			}
		}
		else
		{
			TIM_OC_Config(ARR_CALCULATE(MUTE));
			b=1;
			GPIOA->ODR &= ~(1<<10);
			GPIOA->ODR &= ~(1<<9);
			GPIOA->ODR &= ~(1<<12);
			GPIOA->ODR &= ~(1<<11);
		}
		EXTI->PR |= (1<<14);
	}
	
	//B15 Bb
	if((EXTI->PR & (1<<15)) == (1<<15))
	{
		if(b==1)
		{
			TIM_OC_Config(ARR_CALCULATE(Bb_note[L]));
			b=0;
			GPIOA->ODR |= (1<<9);
			GPIOA->ODR |= (1<<8);
			GPIOA->ODR |= (1<<13);
			GPIOA->ODR |= (1<<11);
			if(R==1 && P<16)
			{
				record[P]=Bb_note[L];
				P=P+1;
			}
		}
		else
		{
			TIM_OC_Config(ARR_CALCULATE(MUTE));
			b=1;
			GPIOA->ODR &= ~(1<<9);
			GPIOA->ODR &= ~(1<<8);
			GPIOA->ODR &= ~(1<<13);
			GPIOA->ODR &= ~(1<<11);
		}
		EXTI->PR |= (1<<15);
	}
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
