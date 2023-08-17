#include "rcc_stdlib.h"
using namespace std;

void blink_led(int time){
    cyw43_arch_gpio_put(0, !cyw43_arch_gpio_get(0)); //blinks LED
    sleep_ms(time);
}

int main()
 {
stdio_init_all();    
sleep_ms(1500);
cyw43_arch_init(); //setup 
cyw43_arch_gpio_put(0,1); //turns on LED

rcc_init_pushbutton(); //set up button
    bool blinking = false;
 while(true)
 {   
 if(!gpio_get(RCC_PUSHBUTTON)) //if gpio NOT high
  { blinking = true;
//do stuff here when button pressed
 cout << "PUSHBUTTON PRESSED!" << '\n'; 

    if (blinking){
        blink_led(500); 
        }
 }
 }
 }

   