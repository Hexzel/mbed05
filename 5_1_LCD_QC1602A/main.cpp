#include "mbed.h"

DigitalOut RS(D2);            //check out these pin numbers CAREFULLY!!!
DigitalOut E(D3);
BusOut data(D4,D5,D6,D7);
AnalogOut V0(D13);

void toggle_enable(void);        //function to toggle/pulse the enable bit
void LCD_init(void);             //function to initialise the LCD
void display_to_LCD(char value); //function to display characters
void set_location(char location);//function to set display locationi

int main()
{
      LCD_init();                     // call the initialise function
      display_to_LCD(0x48);           // ‘H’
      display_to_LCD(0x45);           // ‘E’
      display_to_LCD(0x4C);           // ‘L’
      display_to_LCD(0x4C);           // ‘L’
      display_to_LCD(0x4F);           // ‘O’
      for(char x=0x30;x<=0x39;x++)
      {
            display_to_LCD(x);      // display numbers 0-9
      }
}

void toggle_enable(void)
{
      E=1;
      ThisThread::sleep_for(1ms);
      E=0;
      ThisThread::sleep_for(1ms);
}

//initialise LCD function
void LCD_init(void)
{
      ThisThread::sleep_for(20ms);             // pause for 20 ms
      RS=0;                   // set low to write control data
      E=0;                    // set low

      //function mode
      data=0x2;               // 4 bit mode (data packet 1, DB4-DB7)
      toggle_enable();
      data=0x8;               // 2-line, 7 dot char (data packet 2, DB0-DB3)
      toggle_enable();
      //display mode
      data=0x0;               // 4 bit mode (data packet 1, DB4-DB7)
      toggle_enable();
      data=0xF;               // display on, cursor on, blink on
      toggle_enable();

      //clear display
      data=0x0;
      toggle_enable();
      data=0x1;               // clear
      toggle_enable();
	  V0 = 0.2;
}

//display function
void display_to_LCD(char value)
{
      RS=1;               // set high to write character data
      data=value>>4;      // value shifted right 4 = upper nibble
      toggle_enable();
      data=value;         // value bitmask with 0x0F = lower nibble
      toggle_enable();
}

void set_location(char location)
{
      RS=0;
      data=(location|0x80)>>4;        // upper nibble
      toggle_enable();
      data=location&0x0F;             // lower nibble
      toggle_enable();
}
