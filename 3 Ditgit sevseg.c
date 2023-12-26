#include <16F677.h>                 // Include the PIC16F677 header file
#fuses INTRC_IO,NOWDT,PUT,NOPROTECT,BROWNOUT,NOMCLR  // Configuration fuse settings
#use delay (clock=8000000)         // Set the clock frequency for the delay function

#byte TRISC = 0b10000111 	   // Define TRISC register address and initialize it
#byte PORTC = 0b00000111 	   // Define PORTC register address and initialize it

#define SPORTC PORTC          	   // Define SPORTC as an alias for PORTC

const char SegCode[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};  	// for Common Cathode 7-segment display codes
//const char SegCode[11] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};          // for Common Anode 7-segment display codes
const char Column[3] = {0x20,0x40,0x80};  	// Define column values for the display
static char Segment[3] = {0x7f,0x7f,0x7f};  	// Initialize segment array with off values
static unsigned char ColCount = 0x00;  		// Initialize column count variable

void Display() {
   output_b (0b11100000);
   PORTC = 0b00111111; 			// Turn off segments a-f
   delay_cycles(1);  			// Delay 
   if (ColCount >= 3) ColCount = 0;  	// Reset column count if it exceeds 3
   SPORTC = Segment[ColCount];  	// Set PORTC to the current segment
   output_b (Column[ColCount]^0xE0);  	// Set PORTA based on the current column
   ColCount++;  			// Increment column count
}

#INT_TIMER0
void Timer0(void) { 
   Display(); 					// Display function will display every 100us
}

void CPU_SETUP() {
   set_tris_b (0b01110000); output_b (0b11100000);  	// Configure and initialize TRISA and PORTA
   TRISC= 0b10000000; PORTC=0b00110111;  	// Configure and initialize TRISC and PORTC

   setup_timer_0(T0_INTERNAL | T0_DIV_8);  	// Configure Timer0 with internal clock and 1:8 prescaler *you can change DIV_8 to 16 for 400us
   set_timer0(56);  				// Set Timer0 initial value for a 500us interrupt at 8MHz

   enable_interrupts(GLOBAL);  			// Enable global interrupts
   enable_interrupts(INT_TIMER0);  		// Enable Timer0 interrupt
}

void Show(unsigned int32 Num) { 
   Segment[0] = SegCode[(Num / 100)];  		// Set the first segment based on hundreds digit
   Segment[1] = SegCode[(Num / 10) % 10];  	// Set the second segment based on tens digit
   Segment[2] = SegCode[ Num % 10 ];  		// Set the third segment based on units digit
}

void main() {
   CPU_SETUP(); 
   while (true){
      Show(123);  		// The number that you want to display.
   }
}