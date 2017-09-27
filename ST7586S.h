#ifndef __ST7586S_H__
#define __ST7586S_H__

#ifdef __cplusplus
extern   "C"   {
#endif

#include "os.h"
#include "stm32f10x_lib.h"
	
#define  uchar  unsigned char
#define  uint   unsigned int


#define GPIO_RW GPIO_Pin_0
#define GPIO_A0 GPIO_Pin_1
#define GPIO_LCD_DRIVER GPIO_Pin_2
#define GPIO_CS	GPIO_Pin_3
#define GPIO_LED1 GPIO_Pin_4
#define GPIO_LED2 GPIO_Pin_5
#define GPIO_LED3 GPIO_Pin_6

#define GPIO_RST 	GPIO_Pin_8
#define GPIO_EA 	GPIO_Pin_9
#define GPIO_D0 GPIO_Pin_0
#define GPIO_D1 GPIO_Pin_1
#define GPIO_D2 GPIO_Pin_10
#define GPIO_D3 GPIO_Pin_11
#define GPIO_D4 GPIO_Pin_12
#define GPIO_D5 GPIO_Pin_13
#define GPIO_D6 GPIO_Pin_14
#define GPIO_D7 GPIO_Pin_15


//ST7586 COMMAND
 
#define LCD_NOP 0x00
#define LCD_RST 0x01 //????,RAM????
#define POWER_SAVE_ON 0x10 //0X10,SLEEP,0X11,WAKE UP
#define POWER_SAVE_OFF 0x11
#define PARTIAL_DISPLAY_ON 0x12 //0x12,ON,0x13,OFF
#define PARTIAL_DISPLAY_OFF 0x13
#define INVERSE_DISPLAY_OFF 0x20 //0x20,??,0X21,?? 
#define INVERSE_DISPLAY_ON 0x21 
#define ALL_PIXEL_ON 0x23 //0x22,off,0X23,on
#define ALL_PIXEL_OFF 0x22 
#define DISPLAY_ON 0x29
#define DISPLAY_OFF 0X28
#define SET_COLUMN_ADDRESS 0x2A //0x2A+XS0000H+XE007FH 0<=XS<=XE<=7F
#define SET_ROW_ADDRESS 0x2B //0x2B+YS+YE 0<=YS<=YE<=9F
#define WRITE_DISPLAY_DATA 0x2C 
//#define READ_DISPLAY_DATA 0x2E //???????? 
#define PARTIAL_DISPLAY_AREA 0x30 //??? 
#define SCROLL_AREA 0x33 // TA,SA,BA:0-A0
#define DISPLAY_CONTROL 0x36 //MY,MX1,MX0 
#define START_LINE 0x37 //0-9F
#define DISPLAY_MODE 0x38 //????,39,????
#define ENABLE_DDRAM_INTERFACE 0x3A //3AH+02H
#define DISPLAY_DUTY 0xB0 //B0+9F
#define FIRST_OUTPUT_COM 0xB1 //B1H+00H 
#define FOSC_DIVIDER 0xB3 //B3H+1;0:???,1:2??,2:4??,3:8??
#define PARTIAL_DISPLAY 0xB4 //B4+A0,?????????????
#define SET_VOP 0xC0 //+42H+01H 
#define VOP_INCREASE 0xC1 
#define VOP_DECREASE 0xC2 
#define BIAS_SYSYTEM 0xC3  //C3+04;1/10
#define BOOSTER_LEVEL 0xC4 //C4+07 
#define VOP_OFFSET 0xC7 //C7+1 
#define ANALOG_CONTROL 0xD0 //D0+1D
#define FRAME_RATE 0xF0 //F0+06+0B+0D+12H


extern void delay_ms(u32 time);
extern void LCD_CtrlLinesConfig(void);
extern void init_ST7586S(void);
extern void showpic(const unsigned char *k);
extern void clealddram(const unsigned char dd, const unsigned char cc); 
void writecommand(uchar cmd);
void writedata(uchar data);
void LCDPaint(u16 col,u16 row,u16 width,u16 height,uc8 *lattice/*,u8 convert*/);
void DispChar(u16 col, u16 row, u16 width, u16 height, uc8 *lattice);
extern unsigned char bmp[];
extern const unsigned char gImage_logo240X160[9600];
extern const unsigned char gImage_chinese[9600];
extern const unsigned char Image24_ceng[];
extern const unsigned char InvtLogo[];
extern unsigned char const ASCII_A[];
extern unsigned char const da[];
extern void LCD_ClrScreen(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye);
extern void Active_Line(unsigned char ys, unsigned char t, unsigned char data);
extern void LCDSetXY(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye );
	#ifdef __cplusplus
}
#endif

#endif