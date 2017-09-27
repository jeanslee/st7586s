#include "ST7586S.h"


unsigned short GPIO_D[8] = {GPIO_D0,GPIO_D1,GPIO_D2,GPIO_D3,GPIO_D4,GPIO_D5,GPIO_D6,GPIO_D7};

	 /*******************************************************************************
* Function Name  : LCD_CtrlLinesConfig
* Description    : Configures LCD Control lines (FSMC Pins) in alternate function
                   Push-Pull mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/



void delay_ms(u32 time) // 1 ---20us
 {    
	u32 i,j;
	for(i=0;i<time;i++)
	for(j=0;j<125;j++);

    
 }
void LCD_CtrlLinesConfig(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable FSMC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	
	
  /* Set PB.00(D0), PB.01(D1), PB.10(D2), PB.11(D3), PB.12(D4), PB.13(D5), PB.14(D6), PB.15(D7),PB.08(RST), PB.09(EA)
			as alternate function push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_D0 | GPIO_D1 | GPIO_D2 | GPIO_D3 |
                                GPIO_D4 | GPIO_D5 | GPIO_D6 | GPIO_D7 | GPIO_RST | GPIO_EA ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);


  /* Set PC.00(R/W), PC.01(A0),PC.02(LCD_drive),PC.03(CSB))as alternate function push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_RW | GPIO_A0 | GPIO_LCD_DRIVER | GPIO_CS ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC, GPIO_A0);
	//GPIO_SetBits(GPIOB, GPIO_EA);
	
	//GPIO_WriteBit(GPIOC,GPIO_LCD_DRIVER , 1);
  GPIO_InitStructure.GPIO_Pin = GPIO_LED1 | GPIO_LED2 | GPIO_LED3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
//	GPIO_ResetBits(GPIOC,GPIO_LED1);
//	GPIO_ResetBits(GPIOC,GPIO_LED2);
//	GPIO_ResetBits(GPIOC,GPIO_LED3);
	
//	GPIO_SetBits(GPIOC,GPIO_LED1);   //??1 ?e
//	GPIO_SetBits(GPIOC,GPIO_LED2);		//??1 ?e
//	GPIO_SetBits(GPIOC,GPIO_LED3);		//??1 ?e
	


	

}

void writecommand(uchar cmd)
{
	uchar i;
	unsigned short b;
	GPIO_ResetBits(GPIOC, GPIO_CS);	
	GPIO_ResetBits(GPIOC, GPIO_A0);  //0
	GPIO_ResetBits(GPIOC, GPIO_RW);
	//delay_ms(1);  //delay 20us	   
	GPIO_SetBits(GPIOB, GPIO_EA);
		/*
	b = GPIO_ReadOutputData(GPIOB);
	b = b | ((unsigned short)cmd & 0x3) | (((unsigned short)cmd <<8) & 0xfc00);
	
	GPIO_Write(GPIOB, b);
	*/
	
	for(i=0; i<8; ++i)
	{
		
		if(cmd&0x80)
		{
			GPIO_SetBits(GPIOB, GPIO_D[7-i]);
		}else{
			
			GPIO_ResetBits(GPIOB, GPIO_D[7-i]);
		}
		cmd <<= 1;
		
	}
	//delay_ms(1);  //delay 20us
	GPIO_ResetBits(GPIOB, GPIO_EA);
	//GPIO_SetBits(GPIOB, GPIO_EA);
	GPIO_SetBits(GPIOC, GPIO_CS);
	//delay_ms(1);  //delay 20us
}

void writedata(uchar data)
{
	uchar i;
	unsigned short b;
	GPIO_ResetBits(GPIOC, GPIO_CS);
	GPIO_SetBits(GPIOC, GPIO_A0);   //1
	GPIO_ResetBits(GPIOC, GPIO_RW);
	//delay_ms(1);  //delay 20us	
	GPIO_SetBits(GPIOB, GPIO_EA);
  
	/*
	b = GPIO_ReadOutputData(GPIOB);
	b = b | ((unsigned short)data & 0x3) | (((unsigned short)data <<8) & 0xfc00);
	
	GPIO_Write(GPIOB, b);
	*/
	for(i=0; i<8; ++i)
	{
		if(data&0x80)
		{
			GPIO_SetBits(GPIOB, GPIO_D[7-i]);

		}else{
			
			GPIO_ResetBits(GPIOB, GPIO_D[7-i]);
		}
		
		data <<= 1;
	}
	//delay_ms(1);  //delay 20us
	GPIO_ResetBits(GPIOB, GPIO_EA);
	//GPIO_SetBits(GPIOB, GPIO_EA);
	GPIO_SetBits(GPIOC, GPIO_CS);
	//delay_ms(1);  //delay 20us
}




void Image_Disp(uchar x,uchar y,uchar width,uchar high,const uchar *pstr)
{
   
} 




void init_ST7586S()
{
		GPIO_SetBits(GPIOB, GPIO_RST);
		delay_ms(50);
		GPIO_ResetBits(GPIOB, GPIO_RST);
		delay_ms(1);
		GPIO_SetBits(GPIOB, GPIO_RST );
		delay_ms(1000);//Delay_ms120 

	  writecommand(0xD7);         // Disable Auto Read 
    writedata(0x9F); 
		//writecommand(0xE0);         // Enable OTP Read 
		//writedata(0x00); 
		 //delay_ms(10);
		//writecommand(0xE3);         // OTP Up-Load 
		//delay_ms(20);
		//writecommand(0xE1);
	  writecommand(0x11);         // Sleep Out
	  writecommand(0x28);         // Display OFF
		//delay_ms(200);
	  writecommand(0xC0);         // VOP SET
	  writedata(0x43);        // 16.5V
	  writedata(0x01);        // 00
	
	  writecommand(0xC3);         // BIAS
	  writedata(0x00);        // 01 = 1/13
	
		//writecommand(0xC4);         // Booster = x8
		//writedata(0x06);

	  writecommand(0xD0);         // Enable Analog Circuit
	  writedata(0x1D);
		//writecommand(0xB5);         // N-Line = 13
		//writedata(0x30);        //8d

	  writecommand(0x39);         // display Mode
	
	  writecommand(0x3A);         // Enable DDRAM Interface
	  writedata(0x02);
	
	  writecommand(0x36);         // Scan Direction Setting   //display control
	  writedata(0xC0);						// COM159->COM0, SEG383->SEG0
	  //writedata(0x00);					// COM0->COM159, SEG0->SEG383
	
	  writecommand(0xB0);         // Duty Setting
	  writedata(159);        //9F
	
	  writecommand(0x20);         // Display Inversion OFF

	
	  writecommand(0xf1);
	  writedata(0x15);
	  writedata(0x15);
	  writedata(0x15);
		writedata(0x15);

		//	writecommand(0xb1);              // COM0
		//	writedata(0x9F);

	  //clealddram();
	  
	  writecommand(0x29);              // Display ON
		LCD_ClrScreen(0,0,79,159);


}



void showpic(const unsigned char *k)	 //??
{
		 int i,j;
	   uchar a,b,c,d,e,f,g;
		 writecommand(0x2A);             // Column Address Setting
		 
		 writedata(0x00);            // SEG0-> SEG239
		 writedata(0x00);
		 writedata(0x00);
	   writedata(79);
		 writecommand(0x2B);             // Row Address Setting
		 writedata(0x00);            // COM0 -> COM159
		 writedata(0x00);
		 writedata(0x00);
		 writedata(159);

		 writecommand(0x2c);

		 for(i=0;i<160;i++)
		 {
					for(j=0;j<20;j++)
		 {
				a=*k++;
				b=*k++;
				c=*k++;
				d=(a&0xc0)|((a>>1)&0x18)|((a>>2)&0x03);
				writedata(d);
				e=((a<<6)&0xc0)|((b>>3)&0x18)|((b>>4)&0x03);
				writedata(e);
				f=((b<<4)&0xc0)|((b<<3)&0x18)|((c>>6)&0x03);
				writedata(f);
				g=((c<<2)&0xc0)|((c<<1)&0x18)|(c&0x03);
				writedata(g);
		
		 }
		 }

}


//xs:¨¢D¦Ì??¡¤?e¨º?¦Ì??¡¤¡ê?xe:¨¢D¦Ì??¡¤?¨¢¨º?¦Ì??¡¤
//ys:DD¦Ì??¡¤?e¨º?¦Ì??¡¤¡ê?ye:DD¦Ì??¡¤?¨¢¨º?¦Ì??¡¤
//??¨º???¨®¨°¦Ì?¨¦¨¨??
void LCDSetXY(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye )

{

		writecommand(0x2A);    //¨¦¨¨??¨¢D¦Ì??¡¤
		writedata(0x00);
		writedata(xs + 48);								// Column Address Setting
		//writedata(xs);							// SEG0 -> SEG239   //ADRR: 0x00 -> 0x4F   0-->79
		writedata(0x00);     					
		//writedata(xe);
		writedata(xe + 48);						//SEG383 -> SEG144  //ADDR¡êo0x30 -> 0x7F   48->127
	
		writecommand(0x2B);    //¨¦¨¨??DD¦Ì??¡¤
		writedata(0x00);
		writedata(ys);								// Row Address Setting
		writedata(0x00);							// COM0 -> COM159   //ADDR: 0x00 -> 0x9F    0-->159
		writedata(ye);

}


void clealddram(uchar dd,uchar cc)                   //?0
{


   int i,j;
   writecommand(0x2A);          // Column Address Setting
   writedata(0x00);             // SEG0 -> 
   writedata(0x00);
   writedata(0x00);
   writedata(0x4f);             //
   writecommand(0x2B);              // Row Address Setting
   writedata(0x00);             // COM0 -> 
   writedata(0x00);
   writedata(0x00);
   writedata(0x9F);             //

   writecommand(0x2c);

   for(i=0;i<160;i++)
   {
         for(j=0;j<80;j++)
   {
         writedata(dd);
         writedata(cc);
   }
   }
}

void LCD_ClrScreen(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye)
{
	unsigned char i,j;
//	LCDSetXY(0,0,79,159);
	LCDSetXY(xs, ys, xe, ye);
	writecommand(0x2c);
	
	for(i=0; i<80; i++)
	{
		for(j=0; j<160; j++)
		{
			writedata(0x00);
		}
	}
}

//ys:o¨¢??????; t:o¨¢??¡ä???   ys:0->159
// data: D¨¦??o¨ª¨º¦Ì??¦Ì?¨ºy?Y    //¨º¦Ì??¡êo0xFF¡ê?D¨¦??¡êo0xFC
void Active_Line(unsigned char ys, unsigned char t, unsigned char data)
{
	unsigned char i;
	LCDSetXY(0, ys, 79, ys + t -1);
	
	writecommand(0x2c);	
	for(i=0; i<80*t; i++)
	{
		if(data == 1)
		{
			writedata(0xFF);
		}
		else
		{
			writedata(0xFC);
		}
	}
	
}

void Imaginary_Line()
{
	
}


//8??¨ºy?Y¨¤¡ä??¨º?¨¨y????¦Ì?¡ê?width¡À?D??a3¦Ì???¨ºy¡À?
//col¡êo?e¨º?¨¢D¡ê¡§0-79¡ê?¡ê? row:?e¨º?DD¡ê¡§0-159¡ê?¡ê?    
// 240*160  ???D3??¦Ì??a1¨¢D
//width¡êo¡Á??¡ê?¨ª?¨¨¡ê? height:¡Á??¡ê???¨¨¡ê?
//lattice¡êo¡Á??¡ê¨ºy?Y¡ê¡§???D??1????¨®|¨°?????¦Ì?¡ê?
//convert: 0?a?y3¡ê??¨º?¡ê?1?a¡¤¡ä?¨°??¨º?¡ê?
//¨¨??¡ê¡¤?¨º?¡êo¨°???¡ê??eDD¡ê??3?¨°¡ê¡§?????¨²?¡ã¦Ì¨ª???¨²o¨®¡ê?¡ê¡§¨¨??¡ê¨¨¨ª?tPCtoLCD2002¡ê?
void LCDPaint(u16 col, u16 row, u16 width, u16 height, uc8 *lattice/*, u8 convert*/)  //0,0,24,20
{
		u16 i,j,w, col_end, len,k,xe,ye;
		u32 data;
		unsigned char temp ,str;
	
		col_end = col + width/3 - 1;    //7
	
		xe = col + width/3 -1;
		ye = row + height -1;
		w = width/3; 										//8    
		if(width%8 == 0)								//¨°?DD  ??¦Ì?¦Ì?¡Á??¨²¨ºy
			{
				len = width/8;     //len = 3
			}
		else
			{
				len = width/8 + 1;
			}

//		LCDSetXY(col, row, col_end, row+height-1); //20,20,27,59    //¨¦¨¨????¨º???¨®¨°
			
		LCDSetXY(col, row, xe, ye); //0,0,7,19   //¨¦¨¨????¨º???¨®¨°
		//LCDSetXY(col, 0, col_end, 159);
		writecommand(0x2C);			//?¨°DDRAMD¡ä??¨º?¨ºy?Y
		for(i=0;i<height;i++)		//height = 40       ¡Á¨¹12heightDD
		{
					data = *lattice;
					for(j = 0; j < len - 1; j++) 			//??¡Á??¡ê??¨°?DD¨ºy?Y¨º¡Á?2¨¢??¨®
					{
							lattice++;
							data = (data << 8)|(*lattice);

					}
					
					data = data >> (len*8-width); 		//¨°?3y¨¨??¡ê¨¨¨ª?t¡Á??¡¥¨¤?3?¦Ì?¨ºy?Y
					for(k = 1; k < w + 1; k++)				// w = 8    ??DD¨¨?8¡ä?128*3=24??¦Ì? ?¡ã24??
					{
							temp = (data >> (width - 3*k))&0x07; //??¨°?DD¡ä¨®¡Á¨®?¨¢¨®¨°¨¨?¨¨y????¦Ì?
/* COM0->COM159, SEG0->SEG383
//							switch(temp)
//							{
//									case 0x00:str = 0x00; break;      //000     ->      00000000

//									case 0x01:str = 0x03; break;		 	//001			->		  00000011

//									case 0x02:str = 0x1C; break;			//010			->			00011100

//									case 0x03:str = 0x1F; break;			//011			->			00011111
//								
//									case 0x04:str = 0xE0; break;			//100			->			11100000
//								
//									case 0x05:str = 0xE3; break;			//101			->			11100011

//									case 0x06:str = 0xFC; break;			//110			->			11111100

//									case 0x07:str = 0xFF; break;			//111			->			11111111
//							}
*/							
							switch(temp)
							{
									case 0x00:str = 0x00; break;      //000     ->      00000000

									case 0x01:str = 0xc0; break;		 	//001			->		  00000011

									case 0x02:str = 0x1C; break;			//010			->			00011100

									case 0x03:str = 0xFC; break;			//011			->			00011111
								
									case 0x04:str = 0x03; break;			//100			->			11100000
								
									case 0x05:str = 0xE3; break;			//101			->			11100011

									case 0x06:str = 0x1F; break;			//110			->			11111100

									case 0x07:str = 0xFF; break;			//111			->			11111111
							}

						//	writedata(str^convert);
							writedata(str);

					}

				lattice++;

		}
}
//16*16 o¨ª 32*32
void DispChar(u16 col, u16 row, u16 width, u16 height, uc8 *lattice)  //0,0,24,20
{
		u16 i,j,w, real_width, len,k,xe,ye;
		u32 data;
		unsigned char temp ,str;
	
	  real_width = width/2; 
	
	  xe = col + width/6;   
		ye = row + height -1;
		w = width/6; 			//2 5							
	
		if(width%16 == 0)								//¨°?DD  ??¦Ì?¦Ì?¡Á??¨²¨ºy
			{
				len = width/16;     //len = 3
			}
		else
			{
				len = width/16 + 1;
			}
			
		LCDSetXY(col, row, xe, ye); //0,0,7,19   //¨¦¨¨????¨º???¨®¨°
		//LCDSetXY(col, 0, col_end, 159);
		writecommand(0x2C);			//?¨°DDRAMD¡ä??¨º?¨ºy?Y
		for(i=0;i<height;i++)		//height = 40       ¡Á¨¹12heightDD
		{
					data = *lattice;
					for(j = 0; j < len - 1; j++) 			//??¡Á??¡ê??¨°?DD¨ºy?Y¨º¡Á?2¨¢??¨®
					{
							lattice++;
							data = (data << 8)|(*lattice);

					}
					
					data = data >> (len*8-real_width); 		//¨°?3y¨¨??¡ê¨¨¨ª?t¡Á??¡¥¨¤?3?¦Ì?¨ºy?Y
					for(k = 1; k <= w + 1; k++)				// w = 8    ??DD¨¨?8¡ä?128*3=24??¦Ì? ?¡ã24??
					{
							if(k < w+1){	
															temp = (data >> (real_width - 3*k))&0x07; //??¨°?DD¡ä¨®¡Á¨®?¨¢¨®¨°¨¨?¨¨y????¦Ì?
															switch(temp)
															{
																	case 0x00:str = 0x00; break;      //000     ->      00000000
																	case 0x01:str = 0xc0; break;		 	//001			->		  00000011
																	case 0x02:str = 0x1C; break;			//010			->			00011100
																	case 0x03:str = 0xFC; break;			//011			->			00011111								
																	case 0x04:str = 0x03; break;			//100			->			11100000								
																	case 0x05:str = 0xE3; break;			//101			->			11100011
																	case 0x06:str = 0x1F; break;			//110			->			11111100
																	case 0x07:str = 0xFF; break;			//111			->			11111111
															}
													}
										else if(k==3)
													{
															temp = data & 0x03;
															switch(temp)
															{
																	case 0x00:str = 0x00; break;      //00     ->       00000000
																	case 0x01:str = 0x1C; break;		 	//01			->		  00011100
																	case 0x02:str = 0x03; break;			//10			->			11100000
																	case 0x03:str = 0x1F; break;			//11			->			11111100
															}	
													}
										 else if(k==6)
										 {
											 temp = data & 0x01;
											 	switch(temp)
															{
																	case 0x00:str = 0x00; break;      //0     ->       00000000
																	case 0x01:str = 0x03; break;		 	//1			->		   11100000
																
															}
										 }else{}
						
							writedata(str);

					}

				lattice++;

		}
}


