#include "rcc_stdlib.h"
using namespace std;

void blink_led(int time){
    cyw43_arch_gpio_put(0, !cyw43_arch_gpio_get(0)); //blinks LED
    sleep_ms(time);
}
                                                            //NOT DONE WITH THIS CODE YET
int main()
 {
stdio_init_all();    
sleep_ms(1500);
cyw43_arch_init(); //setup 
cyw43_arch_gpio_put(0,1); //turns on LED

rcc_init_pushbutton(); //set up button
  
 while(true){
 sleep_ms(200);
 ServoPosition(&s3, 50); //50% of range (forwards)
 
 if(!gpio_get(RCC_PUSHBUTTON)) 
        servo_pos += 10;

 cout << "servo facing forwards" << '\n';


 
 }
 }

