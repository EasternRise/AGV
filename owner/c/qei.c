#include "all.h"


/* count per rotation */
uint16_t CPR;
int16_t r_now[2];
TIM_TypeDef* Tim_S[2]={TIM3,TIM8};

void QEI_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	CPR = (u16)ENC_PPR*4;
	
	
	//TIM3
	{
		/* enable the periph clock */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
			
		/* configue IO */	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		/* configue timer */	
		TIM_DeInit(TIM3);		
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
		TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 
		TIM_TimeBaseStructure.TIM_Period = CPR-1; 			
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

		TIM_ICStructInit(&TIM_ICInitStructure);
		TIM_ICInitStructure.TIM_ICFilter = (u8)0;
	
		TIM_ICInit(TIM3, &TIM_ICInitStructure);

		TIM_ClearFlag(TIM3, TIM_FLAG_Update);	
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
		
		/* reset the timer3 counter */
		TIM3->CNT = (u16)0;
		/* enable the timer3 */
		TIM_Cmd(TIM3, ENABLE);

		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	
	}
		
	//TIM2
// 	{
// 		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
// 		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
// 	
// 		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
// 		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 		GPIO_Init(GPIOA, &GPIO_InitStructure);
// 		
// 		TIM_DeInit(TIM2);		
// 		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
// 		TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 
// 		TIM_TimeBaseStructure.TIM_Period = CPR-1; 			
// 		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
// 		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
// 		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
// 		TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
// 		
// 		
// 		TIM_ICStructInit(&TIM_ICInitStructure);
// 		TIM_ICInitStructure.TIM_ICFilter = (u8)0;
// 	
// 		TIM_ICInit(TIM2, &TIM_ICInitStructure);

// 		TIM_ClearFlag(TIM2, TIM_FLAG_Update);	
// 		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
// 		
// 		/* reset the timer3 counter */
// 		TIM2->CNT = (u16)0;
// 		/* enable the timer3 */
// 		TIM_Cmd(TIM2, ENABLE);

// 		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
// 		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 2;
// 		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
// 		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
// 		NVIC_Init(&NVIC_InitStructure);
// 	
// 	}
// 		
	//TIM8
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 | RCC_APB2Periph_GPIOC , ENABLE);
		
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		
		
		TIM_DeInit(TIM8);		
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
		TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 
		TIM_TimeBaseStructure.TIM_Period = CPR-1; 			
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
		TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
		
		
		TIM_ICStructInit(&TIM_ICInitStructure);
		TIM_ICInitStructure.TIM_ICFilter = (u8)0;
	
		TIM_ICInit(TIM8, &TIM_ICInitStructure);

		TIM_ClearFlag(TIM8, TIM_FLAG_Update);	
		TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);
		
		/* reset the timer3 counter */
		TIM8->CNT = (u16)0;
		/* enable the timer3 */
		TIM_Cmd(TIM8, ENABLE);

		NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	
		
	}
// 		
// 	//IIM4
// 	{
// 		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
// 		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
// 		
// 		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
// 		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 		GPIO_Init(GPIOB, &GPIO_InitStructure);

// 		TIM_DeInit(TIM4);		
// 		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
// 		TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 
// 		TIM_TimeBaseStructure.TIM_Period = CPR-1; 			
// 		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
// 		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
// 		TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
// 		TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
// 		
// 		
// 		TIM_ICStructInit(&TIM_ICInitStructure);
// 		TIM_ICInitStructure.TIM_ICFilter = (u8)0;
// 	
// 		TIM_ICInit(TIM4, &TIM_ICInitStructure);

// 		TIM_ClearFlag(TIM4, TIM_FLAG_Update);	
// 		TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
// 		
// 		/* reset the timer3 counter */
// 		TIM4->CNT = (u16)0;
// 		/* enable the timer3 */
// 		TIM_Cmd(TIM4, ENABLE);

// 		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
// 		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 2;
// 		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
// 		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
// 		NVIC_Init(&NVIC_InitStructure);
// 		
// 	}

// 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE);
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_TIM8 , ENABLE);
}

void TIM3_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
    if(!(TIM3->CR1&0x0010))
    {/* count up overflow interrupt */
        //Com_Printf("up overflow\n\r");
        r_now[0]++;
    }
    else
    {/* count down overflow interrupt */
        //Com_Printf("down overflow\n\r");
        r_now[0]--;
    }
}

// void TIM2_IRQHandler(void)
// {
// 	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//     if(!(TIM2->CR1&0x0010))
//     {/* count up overflow interrupt */
//         //Com_Printf("up overflow\n\r");
//         r_now[0]++;
//     }
//     else
//     {/* count down overflow interrupt */
//         //Com_Printf("down overflow\n\r");
//         r_now[0]--;
//     }
// }

void TIM8_UP_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM8,TIM_IT_Update);
    if(!(TIM8->CR1&0x0010))
    {/* count up overflow interrupt */
        //Com_Printf("up overflow\n\r");
        r_now[1]++;
    }
    else
    {/* count down overflow interrupt */
        //Com_Printf("down overflow\n\r");
        r_now[1]--;
    }
}

// void TIM4_IRQHandler(void)
// {
// 	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
//     if(!(TIM4->CR1&0x0010))
//     {/* count up overflow interrupt */
//         //Com_Printf("up overflow\n\r");
//         r_now[1]++;
//     }
//     else
//     {/* count down overflow interrupt */
//         //Com_Printf("down overflow\n\r");
//         r_now[1]--;
//     }
// }

