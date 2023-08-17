#include "rcc_stdlib.h"
using namespace std;

int main()
{

stdio_init_all();    
sleep_ms(1500);
cyw43_arch_init(); //setup 
cyw43_arch_gpio_put(0,1); //turns on LED

    int state = 0;
    int val;
    uint32_t curr_time = 0; 
    uint32_t prev_time = 0; 


    while(true)
    {   curr_time = time_us_32 ();
      switch (state) {
        case 0: 
            cout << "waiting\n";
            if (curr_time -  prev_time>= 1000000){
                state=1;
            }
        break;


      }
        
    }

}

    //In this challenge we do Blink LED
    // 1 LED has 2 states, ON & OFF
    // 2 Transition Condition: has 400 ms passed?
    // 3 Use previous_time and current_time method NOT sleep_ms()