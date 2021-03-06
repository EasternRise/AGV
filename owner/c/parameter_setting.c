#include "all.h"
#include "can.h"

extern float AGV_speed,delta_x,delta_y;
extern int Stop_time;
extern union fi64_to_u8 flash_save[11];

void parameter_setting (void)
{
	while(1)
	{
		LCD_Clear();
		LCD_SetXY(0,0);
		LCD_WriteString("PARAMETER SETTING");	
		
		LCD_SetXY(0,1);
		LCD_WriteString("1.SPEED:");
		LCD_WriteDouble(AGV_speed,1);
		
		LCD_SetXY(0,2);
		LCD_WriteString("2.DELTA:");
		LCD_WriteDouble(delta_x,0);
		LCD_WriteString("/");
		LCD_WriteDouble(delta_y,0);
				
		LCD_SetXY(0,3);
		LCD_WriteString("3.STOPTIME:");
		LCD_WriteInt(Stop_time);
		
		refresh();
		
		if (KeyReady==1)
		{
			KeyReady=0;
			
			switch (KeyValue)
			{
				case 1:
					Input_FloatValue(&AGV_speed,"SPEED");
				  flash_save[0].u16_data[0]=AGV_speed;
				  break;
				
				case 2:
					Input_FloatValue(&delta_x,"DELTA_X");
				  flash_save[0].u16_data[1]=delta_x;
				  Input_FloatValue(&delta_y,"DELTA_Y");
				  flash_save[0].u16_data[2]=delta_y;
 				  break;

				case 3:
					Input_IntValue(&Stop_time,"STOPTIME");
				  flash_save[0].u16_data[3]=Stop_time;
				  break;
				
				case 5:
					return;
				
			}
			Data_Save();
			init_parameter();
		}
		
		delay(LCD_DELAY);
		
	}
}

void load_defaults (void)
{
	while (1)
	{
		LCD_Clear();
		LCD_SetXY(0,0);
		LCD_WriteString("------NOTICE------");
		LCD_SetXY(0,1);
		LCD_WriteString("Are you sure to load defaults?Press OK to continue,or back to cancel");
		
		refresh();
		delay(LCD_DELAY);
		
		if(KeyReady==1)
		{
			KeyReady=0;
			switch(KeyValue)
			{
				case 18://ok
				  flash_save[0].u16_data[0]=800;//AGV_speed
					flash_save[0].u16_data[1]=800;//delta_x
					flash_save[0].u16_data[2]=800;//delta_y
					flash_save[0].u16_data[3]=200;//Stop_time
					Data_Save();
					init_parameter();				
					return;
				case keyback:
					return;
			}
		}
	}
}
