

#ifndef _SSD1306_H
#define _SSD1306_H

#define  TRUE 1
#define FALSE 0

#define  ON 1
#define OFF 0

#define SSD1306_SLAVE_ADDRESS 	0x78 //0x78 ( (0x3C<<1) | 0 )  || 0x7A ( (0x3D<<1) | 0 )
#define COMMAND_MODE_ADDRESS 	0x00
#define NORMAL_MODE_ADDRESS 	0x40

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "main.h"
// #include "I2C.h"

extern I2C_HandleTypeDef hi2c1;

// Porting      I2C_Write( uint8_t slave_addr , uint8_t reg_addr_or_MODE_ADDRESS , uint8_t *data , uint16_t len)
//     		SSD1306_Write( uint8_t slave_addr , uint8_t reg_addr_or_MODE_ADDRESS , uint8_t *data , uint16_t len)
#define SSD1306_Write(A,B,C,D) HAL_I2C_Mem_Write(&hi2c1,A,B,1,C,D,100)

extern uint8_t initial_command[27] ;
extern uint8_t TEXT_6x8_char [ 13 ][ 6 ] ;

void OLED_initial( void );
void OLED_clear( void );
void OLED_write_num(uint8_t num);
void OLED_write(uint8_t num);

void num_print(int16_t x);


///////////////////////////////////////////////////////////

/*
	1. Fundamental Command Table 
*/
void SSD1306_Set_Contrast( uint8_t contrast ); 	// reset = 0x7F
void SSD1306_Set_Entire_Display_OFF( void ) ;
void SSD1306_Set_Entire_Display_ON ( void ) ;
void SSD1306_Set_Normal_Display ( void ) ;
void SSD1306_Set_Inverse_Display( void ) ;
void SSD1306_Set_Display_ON( void )  ;
void SSD1306_Set_Display_OFF( void ) ;

/*
	2. Scrolling Command Table 
*/
void SSD1306_Set_Continuous_Horizontal_Scroll( bool Direction ,
		uint8_t Start_Page , uint8_t End_Page , uint8_t Frames );
void SSD1306_Set_Continuous_Vertical_and_Horizontal_Scroll( 
		bool Direction , uint8_t Start_Page , uint8_t End_Page ,
		uint8_t Frames , uint8_t Vertical_Scroll_Offset  ) ;

void SSD1306_Set_Deactivate_scroll( void ) ;
void SSD1306_Set_Activate_scroll( void ) ;
void SSD1306_Set_Vertical_Scroll_Area( uint8_t Start_Row ,			// reset 0x00 0x3F
									   uint8_t Scroll_rows ) ;


/*
	3. Addressing Setting Command Table 
*/
void SSD1306_Set_Memmory_Address_Horizontal_Mode( void ) ;
void SSD1306_Set_Memmory_Address_Vertical_Mode( void ) ;
void SSD1306_Set_Memmory_Address_Page_Mode( void ) ; // reset
void SSD1306_Set_XY( uint8_t x, uint8_t y ) ; // Page Mode
void SSD1306_Set_Writed_Area( uint8_t column_start , uint8_t column_end	//Horizontal & Vertical Mode 
				 , uint8_t page_start   , uint8_t page_end   ) ;		// reset 0x00,0x7F,0x00,0x07

/*
	4. Hardware Configuration (Panel resolution & layout related) Command Table
*/
void SSD1306_Set_Display_Start_Line( uint8_t x ) ;						// reset 0x00
void SSD1306_Set_Segment_Re_map( bool x ) ;								// reset 0x00
void SSD1306_Set_Multiplex_Ratio( uint8_t x ) ;							// reset 0x3F
void SSD1306_Set_COM_Output_Scan_Direction( bool x ) ;					// reset 0x00
void SSD1306_Set_Display_Offset( uint8_t x ) ;							// reset 0x00
void SSD1306_Set_COM_Pins_Hardware_Configuration( bool x , bool y ) ;	// reset 0x00 , 0x01

/*
	5. Timing & Driving Scheme Setting Command Table 
*/
void SSD1306_Set_Display_Clock_Divid_Fosc( uint8_t divide_ratio ,
										   uint8_t Fosc );		// reset 0x00 , 0x08
void SSD1306_Set_Pre_charge_Period( uint8_t Phase1_period , 
									uint8_t Phase2_period );	// reset 0x02 , 0x02
void SSD1306_Set_Vcomh_Deselect_Level( uint8_t x );				// reset 0x02



#endif
