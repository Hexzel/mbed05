#include "mbed.h"
#include "TextLCD.h"

DigitalOut led(LED1);      //LED1 = PA_5
TextLCD lcd(D2, D3, D4, D5, D6, D7);

int main()
{
      int x=0;
      while(true)
      {
            led = !led;             // toggle led
            lcd.locate(2,0);
            // lcd.printf("%5i",x);    //counter display
			lcd.printf("%c", 'a');
            ThisThread::sleep_for(1s);
            x++;
      }
}
