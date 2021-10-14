

#include "SSD1306.h"

uint8_t initial_command[27] = {
    0x00, 0xAE, 0xD5, 0x80, 0xA8, 0x3F, 0xD3, 0x00, 0x40,
    0x8D, 0x14, 0x20, 0x00, 0xA1, 0xC8, 0xDA, 0x12, 0x81,
    0xCF, 0xD9, 0xF1, 0xDB, 0x40, 0x2E, 0xA4, 0xA6, 0xAF
};

uint8_t config_buf[16] = {0} ;

uint8_t TEXT_6x8_char [ 13 ][ 6 ] = { // : 
    0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
    0x00, 0x00, 0x42, 0x7F, 0x40, 0x00, // 1
    0x00, 0x42, 0x61, 0x51, 0x49, 0x46, // 2
    0x00, 0x21, 0x41, 0x45, 0x4B, 0x31, // 3
    0x00, 0x18, 0x14, 0x12, 0x7F, 0x10, // 4
    0x00, 0x27, 0x45, 0x45, 0x45, 0x39, // 5
    0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30, // 6
    0x00, 0x01, 0x71, 0x09, 0x05, 0x03, // 7
    0x00, 0x36, 0x49, 0x49, 0x49, 0x36, // 8
    0x00, 0x06, 0x49, 0x49, 0x29, 0x1E, // 9
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // sp 10
    0x00, 0x08, 0x08, 0x08, 0x08, 0x08, //  - 11
    0x00, 0x00, 0x60, 0x60, 0x00, 0x00 //   . 12
}; // :

void OLED_initial( ) {

    // for( uint8_t i = 0 ; i < 27 ; i++ )
    //     I2C_buf[ i ] = initial_command[ i ] ;

    // I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;

    // I2C1_MasterWrite( I2C_buf , 27 ,  SSD1306_SLAVE_ADDRESS  >> 1 , &status);

    // // wait for the message to be sent or status has changed.
    // while (status == I2C1_MESSAGE_PENDING);

    // // while (status != I2C1_MESSAGE_COMPLETE) ;

//////////////////////////////////////////////////////////////////////
/*
    // start I2c
    I2C_Start() ;

    // send slave address & W/R
    I2C_Write(  SSD1306_SLAVE_ADDRESS  ) ;

    // send data
    for ( uint16_t i = 0 ; i < 27 ; i++ )
        I2C_Write( initial_command[i] );

    // stop I2C
    I2C_Stop () ;
    */

    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , &initial_command[1] , 26 );

}


void OLED_clear() {

		SSD1306_Set_XY( 0, 0 ) ; // Page Mode

		memset( config_buf , 0 , 16 );
		
		for( uint16_t i = 0; i < 1024/16; i++ )
				SSD1306_Write( SSD1306_SLAVE_ADDRESS , NORMAL_MODE_ADDRESS , config_buf , 16 );
}

void OLED_write_num(uint8_t num) {

    if (num > 13) num = 13;

//    I2C_Start();
//    I2C_Write( SSD1306_SLAVE_ADDRESS );
//    I2C_Write(0x40);
//    for (uint8_t i = 0; i < 6; i++)
//        I2C_Write(TEXT_6x8_char[ num ][ i ]);
//    I2C_Stop();
		
		SSD1306_Write( SSD1306_SLAVE_ADDRESS , NORMAL_MODE_ADDRESS , &TEXT_6x8_char[num][0] , 6 );
}

/*

void OLED_write_num(uint8_t num) {

    if (num > 13) num = 13;

    I2C_Start();
    I2C_Write( SSD1306_SLAVE_ADDRESS );
    I2C_Write(0x40);
    for (uint8_t i = 0; i < 6; i++)
        I2C_Write(TEXT_6x8_char[ num ][ i ]);
    I2C_Stop();
}

void num_print(int16_t x) {
    (x < 0) ? OLED_write(21) : OLED_write(20); // '-' | ' '
    x = abs(x);
    // OLED_write( (x/1000) );
    OLED_write((x / 100));
    OLED_write(22); // .
    OLED_write((x / 10) % 10);
    OLED_write((x % 10));
}

void OLED_write(uint8_t num) {

    if (num > 12) num = 12;

    I2C_Start();
    I2C_Write( SSD1306_SLAVE_ADDRESS );
    I2C_Write(0x40);
    I2C_Write(num);
    I2C_Stop();
}
*/

//////////////////////////////////////////////////////////////////

/*
	1. Fundamental Command Table 
*/
void SSD1306_Set_Contrast( uint8_t contrast ){ 	// reset = 0x7F
    // I2C_Start();
    // I2C_Write( SSD1306_SLAVE_ADDRESS );
    // I2C_Write( COMMAND_MODE_ADDRESS  );
    // I2C_Write( 0x81 );
    // I2C_Write( contrast );
    // I2C_Stop();

    config_buf[0] = 0x81 ;
    config_buf[1] = contrast ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 2 );
}

void SSD1306_Set_Entire_Display_OFF( void ) { 	// reset = 0xA4
	// I2C_Start();
 //    I2C_Write( SSD1306_SLAVE_ADDRESS );
 //    I2C_Write( COMMAND_MODE_ADDRESS  );
 //    I2C_Write( 0xA4 );
 //    I2C_Stop();

    config_buf[0] = 0xA4 ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 1 );
}

void SSD1306_Set_Entire_Display_ON( void ) { 	// reset = 0xA4
	// I2C_Start();
 //    I2C_Write( SSD1306_SLAVE_ADDRESS );
 //    I2C_Write( COMMAND_MODE_ADDRESS  );
 //    I2C_Write( 0xA5 );
 //    I2C_Stop();

    config_buf[0] = 0xA5 ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 1 );
}

void SSD1306_Set_Normal_Display ( void ) { 		// reset = 0xA6
	// I2C_Start();
 //    I2C_Write( SSD1306_SLAVE_ADDRESS );
 //    I2C_Write( COMMAND_MODE_ADDRESS  );
 //    I2C_Write( 0xA6 );
 //    I2C_Stop();

    config_buf[0] = 0xA6 ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 1 );
}

void SSD1306_Set_Inverse_Display ( void ) { 	// reset = 0xA6
	// I2C_Start();
 //    I2C_Write( SSD1306_SLAVE_ADDRESS );
 //    I2C_Write( COMMAND_MODE_ADDRESS  );
 //    I2C_Write( 0xA7 );
 //    I2C_Stop();

    config_buf[0] = 0xA7 ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 1 );
}

void SSD1306_Set_Display_ON( void ){ 
    // I2C_Start();
    // I2C_Write( SSD1306_SLAVE_ADDRESS );
    // I2C_Write( COMMAND_MODE_ADDRESS  );
    // I2C_Write( 0xAF );
    // I2C_Stop();

    config_buf[0] = 0xAF ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 1 );
}

void SSD1306_Set_Display_OFF( void ){ 
    // I2C_Start();
    // I2C_Write( SSD1306_SLAVE_ADDRESS );
    // I2C_Write( COMMAND_MODE_ADDRESS  );
    // I2C_Write( 0xAE );
    // I2C_Stop();

    config_buf[0] = 0xAE ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 1 );
}


/*
	2. Scrolling Command Table 
*/
void SSD1306_Set_Continuous_Horizontal_Scroll( bool Direction ,
	uint8_t Start_Page , uint8_t End_Page , uint8_t Frames ){

	if( Start_Page > 0x07 ) Start_Page = 0x07 ;
	if( End_Page   > 0x07 ) End_Page   = 0x07 ;
	if( Frames     > 0x07 ) Frames     = 0x07 ;

    // I2C_Start();
    // I2C_Write( SSD1306_SLAVE_ADDRESS );
    // I2C_Write( COMMAND_MODE_ADDRESS  );
    // I2C_Write( 0x26 | Direction );
    // I2C_Write( 0x00 );
    // I2C_Write( Start_Page );
    // I2C_Write( Frames );
    // I2C_Write( End_Page );
    // I2C_Write( 0x00 );
    // I2C_Write( 0xFF );
    // I2C_Stop();


    config_buf[0] = 0x26 | Direction ;
    config_buf[1] = 0x00 ;
    config_buf[2] = Start_Page ;
    config_buf[3] = Frames ;
    config_buf[4] = End_Page ;
    config_buf[5] = 0x00 ;
    config_buf[6] = 0xFF ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 7 );
}

void SSD1306_Set_Continuous_Vertical_and_Horizontal_Scroll( 
		bool Direction , uint8_t Start_Page , uint8_t End_Page ,
		uint8_t Frames , uint8_t Vertical_Scroll_Offset  ){

	if( Start_Page > 0x07 ) Start_Page = 0x07 ;
	if( End_Page   > 0x07 ) End_Page   = 0x07 ;
	if( Frames     > 0x07 ) Frames     = 0x07 ;
	if( Vertical_Scroll_Offset > 0x3F ) 
		Vertical_Scroll_Offset     = 0x3F ;

    // I2C_Start();
    // I2C_Write( SSD1306_SLAVE_ADDRESS );
    // I2C_Write( COMMAND_MODE_ADDRESS  );
    // I2C_Write( 0x29 + Direction );
    // I2C_Write( 0x00 );
    // I2C_Write( Start_Page );
    // I2C_Write( Frames );
    // I2C_Write( End_Page );
    // I2C_Write( Vertical_Scroll_Offset );
    // I2C_Stop();


    config_buf[0] = 0x29 + Direction ;
    config_buf[1] = 0x00 ;
    config_buf[2] = Start_Page ;
    config_buf[3] = Frames ;
    config_buf[4] = End_Page ;
    config_buf[5] = Vertical_Scroll_Offset ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 6 );
}

void SSD1306_Set_Deactivate_scroll( void ){
	// I2C_Start();
 //    I2C_Write( SSD1306_SLAVE_ADDRESS );
 //    I2C_Write( COMMAND_MODE_ADDRESS  );
 //    I2C_Write( 0x2E );
 //    I2C_Stop();

    config_buf[0] = 0x2E ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 1 );
}

void SSD1306_Set_Activate_scroll( void ){
	// I2C_Start();
 //    I2C_Write( SSD1306_SLAVE_ADDRESS );
 //    I2C_Write( COMMAND_MODE_ADDRESS  );
 //    I2C_Write( 0x2F );
 //    I2C_Stop();

    config_buf[0] = 0x2F ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 1 );
}

void SSD1306_Set_Vertical_Scroll_Area( uint8_t Start_Row ,			// reset 0x00 0x3F
									   uint8_t Scroll_rows ){
	if ( Start_Row   > 0x3F ) Start_Row   = 0x3F ;
	if ( Scroll_rows > 0x40 ) Scroll_rows = 0x40 ;

	// I2C_Start();
 //    I2C_Write( SSD1306_SLAVE_ADDRESS );
 //    I2C_Write( COMMAND_MODE_ADDRESS  );
 //    I2C_Write( 0xA3 );
 //    I2C_Write( Start_Row );
 //    I2C_Write( Scroll_rows );
 //    I2C_Stop();

    config_buf[0] = 0xA3 ;
    config_buf[1] = Start_Row ;
    config_buf[2] = Scroll_rows ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 3 );
}


/*
	3. Addressing Setting Command Table 
*/
void SSD1306_Set_Memmory_Address_Horizontal_Mode( void ){
	// I2C_Start();
 //    I2C_Write( SSD1306_SLAVE_ADDRESS );
 //    I2C_Write( COMMAND_MODE_ADDRESS  );
 //    I2C_Write( 0x20 );
 //    I2C_Write( 0x00 );
 //    I2C_Stop();

    config_buf[0] = 0x20 ;
    config_buf[1] = 0x00 ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 2 );
}

void SSD1306_Set_Memmory_Address_Vertical_Mode( void ){
	// I2C_Start();
 //    I2C_Write( SSD1306_SLAVE_ADDRESS );
 //    I2C_Write( COMMAND_MODE_ADDRESS  );
 //    I2C_Write( 0x20 );
 //    I2C_Write( 0x01 );
 //    I2C_Stop();

    config_buf[0] = 0x20 ;
    config_buf[1] = 0x01 ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 2 );
}

void SSD1306_Set_Memmory_Address_Page_Mode( void ){						// reset
	// I2C_Start();
 //    I2C_Write( SSD1306_SLAVE_ADDRESS );
 //    I2C_Write( COMMAND_MODE_ADDRESS  );
 //    I2C_Write( 0x20 );
 //    I2C_Write( 0x02 );
 //    I2C_Stop();

    config_buf[0] = 0x20 ;
    config_buf[1] = 0x02 ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 2 );
}

void SSD1306_Set_XY( uint8_t x, uint8_t y ){							// Page Mode

    if (x > 127)	x = 127 ; // MAX = 127 ( column )
    if (y > 7) 		y =   7 ; // MAX =   7 (   page )

    // I2C_Start();
    // I2C_Write( SSD1306_SLAVE_ADDRESS );
    // I2C_Write( COMMAND_MODE_ADDRESS  );	// command mode
    // I2C_Write( 0x10 |  (x >> 4)  ); 	// x high 4 bits
    // I2C_Write( 0x00 | (x & 0x0F) ); 	// x  low 4 bits
    // I2C_Write( 0xb0 | y ); 				// y
    // I2C_Stop();

    config_buf[0] = 0x10 | ( x >> 4 ) ; // x high 4 bits
    config_buf[1] = 0x00 | (x & 0x0F) ; // x  low 4 bits
    config_buf[2] = 0xb0 | y ;          // y
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 3 );

}

void SSD1306_Set_Writed_Area( uint8_t column_start , uint8_t column_end	//Horizontal & Vertical Mode
					, uint8_t page_start   , uint8_t page_end   ){		// reset 0x00,0x7F,0x00,0x07
	// I2C_Start();
 //    I2C_Write( SSD1306_SLAVE_ADDRESS );
 //    I2C_Write( COMMAND_MODE_ADDRESS  );
 //    I2C_Write( 0x21 ); 			// set column address
 //    I2C_Write( column_start );	// set start address
 //    I2C_Write(   column_end );	// set   end address
 //    I2C_Write( 0x22 );			// set   page address
 //    I2C_Write( page_start );	// set start address
 //    I2C_Write(   page_end );	// set   end address
 //    I2C_Stop();


    config_buf[0] = 0x21 ;          // set column address
    config_buf[1] = column_start ;  // set start address
    config_buf[2] =   column_end ;  // set   end address
    config_buf[3] = 0x22 ;          // set   page address
    config_buf[4] = page_start ;    // set start address
    config_buf[5] =   page_end ;    // set   end address
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 6 );
}


/*
	4. Hardware Configuration (Panel resolution & layout related) Command Table
*/
void SSD1306_Set_Display_Start_Line( uint8_t x ){ 						// reset 0x00
	if ( x > 63 ) x = 63 ;
	x |= 0x40 ;

	// I2C_Start();
 //    I2C_Write( SSD1306_SLAVE_ADDRESS );
 //    I2C_Write( COMMAND_MODE_ADDRESS  );
 //    I2C_Write( x );
 //    I2C_Stop();

    config_buf[0] = x ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 1 );
}

void SSD1306_Set_Segment_Re_map( bool x ){ 								// reset 0x00
	// I2C_Start();
 //    I2C_Write( SSD1306_SLAVE_ADDRESS );
 //    I2C_Write( COMMAND_MODE_ADDRESS  );
 //    ( x )? I2C_Write( 0xA1 ):I2C_Write( 0xA0 );
 //    I2C_Stop();

    config_buf[0] = ( x )? 0xA1:0xA0 ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 1 );
}

void SSD1306_Set_Multiplex_Ratio( uint8_t x ){ 							// reset 0x3F
	if( x > 63 ) x = 63 ;
	else if( x < 15 ) x = 15 ;

	// I2C_Start();
 //    I2C_Write( SSD1306_SLAVE_ADDRESS );
 //    I2C_Write( COMMAND_MODE_ADDRESS  );
 //    I2C_Write( 0xA8 );
 //    I2C_Write( x );
 //    I2C_Stop();

    config_buf[0] = 0xA8 ;
    config_buf[1] = x;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 2 );
}

void SSD1306_Set_COM_Output_Scan_Direction( bool x ){ 					// reset 0x00
	// I2C_Start();
 //    I2C_Write( SSD1306_SLAVE_ADDRESS );
 //    I2C_Write( COMMAND_MODE_ADDRESS  );
 //    ( x )? I2C_Write( 0xC8 ):I2C_Write( 0xC0 );
 //    I2C_Stop();

    config_buf[0] = ( x )? 0xC8:0xC0 ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 1 );
}

void SSD1306_Set_Display_Offset( uint8_t x ){ 							// reset 0x00
	if( x > 63 ) x = 63 ;

	// I2C_Start();
 //    I2C_Write( SSD1306_SLAVE_ADDRESS );
 //    I2C_Write( COMMAND_MODE_ADDRESS  );
 //    I2C_Write( 0xD3 );
 //    I2C_Write( x );
 //    I2C_Stop();

    config_buf[0] = 0xD3 ;
    config_buf[1] = x;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 2 );
}

void SSD1306_Set_COM_Pins_Hardware_Configuration( bool x , bool y ){ 	// reset 0x00 , 0x01
	// I2C_Start();
 //    I2C_Write( SSD1306_SLAVE_ADDRESS );
 //    I2C_Write( COMMAND_MODE_ADDRESS  );
 //    I2C_Write( 0xDA );
 //    I2C_Write( (uint8_t)(x<<5) | (uint8_t)(y<<4) | 0x02 );
 //    I2C_Stop();

    config_buf[0] = 0xDA ;
    config_buf[1] = (uint8_t)(x<<5) | (uint8_t)(y<<4) | 0x02 ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 2 );
}


/*
	5. Timing & Driving Scheme Setting Command Table 
*/
void SSD1306_Set_Display_Clock_Divid_Fosc( uint8_t divide_ratio , uint8_t Fosc ){		// reset 0x00 , 0x08
	if( divide_ratio > 0x0F ) divide_ratio = 0x0F ;
	if( Fosc 		 > 0x0F ) Fosc         = 0x0F ;

	// I2C_Start();
 //    I2C_Write( SSD1306_SLAVE_ADDRESS );
 //    I2C_Write( COMMAND_MODE_ADDRESS  );
 //    I2C_Write( 0xD5 );
 //    I2C_Write( (divide_ratio<<4) | Fosc );
 //    I2C_Stop();

    config_buf[0] = 0xD5 ;
    config_buf[1] = (divide_ratio<<4) | Fosc ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 2 );
}

void SSD1306_Set_Pre_charge_Period( uint8_t Phase1_period , uint8_t Phase2_period ){	// reset 0x02 , 0x02
	if( Phase1_period > 0x0F ) Phase1_period = 0x0F ; // Phase 1 period of up to 15 DCLK
	if( Phase2_period > 0x0F ) Phase2_period = 0x0F ; // Phase 2 period of up to 15 DCLK

	if( Phase1_period & Phase2_period ){ 			  // clocks 0 is invalid entry
		// I2C_Start();
  //   	I2C_Write( SSD1306_SLAVE_ADDRESS );
  //   	I2C_Write( COMMAND_MODE_ADDRESS  );
  //   	I2C_Write( 0xD9 );
  //   	I2C_Write( (Phase2_period<<4) | Phase1_period );
  //   	I2C_Stop();

        config_buf[0] = 0xD9 ;
        config_buf[1] = (Phase2_period<<4) | Phase1_period ;
        SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 2 );
	}
}

void SSD1306_Set_Vcomh_Deselect_Level( uint8_t x ){										// reset 0x02
	x &= 0x07 ; // mask 0b00000111
	x <<= 4   ;	// shift 4 bit

	// I2C_Start();
 //    I2C_Write( SSD1306_SLAVE_ADDRESS );
 //    I2C_Write( COMMAND_MODE_ADDRESS  );
 //    I2C_Write( 0xDB );
	// I2C_Write( x );
	// I2C_Stop();

    config_buf[0] = 0xDB ;
    config_buf[1] = x ;
    SSD1306_Write( SSD1306_SLAVE_ADDRESS , COMMAND_MODE_ADDRESS , config_buf , 2 );
}


