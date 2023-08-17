#include "rcc_stdlib.h"
using namespace std;

int main()
{
    stdio_init_all();    
    sleep_ms(1500);
    cyw43_arch_init();
    cyw43_arch_gpio_put(0,1);
    rcc_init_pushbutton ();
    rcc_init_potentiometer();

    int state = 0;
    int val;
    uint32_t enter_time = time_us_32();
    while (true){
    // state0
    if (state == 0){
        val = adc_read();
        if (val <= 2000){
        state=1;
        }
    if (val > 2000 && val < 3000){
        state = 2;
        enter_time = time_us_32();
    }
    if (val >= 3000){
        state = 3;
    }

    }
    //state1
     if (state == 1){
        cout << "FWD\n";
        state = 0;
    }

    //state2
     if (state == 2){
        cout << "STOP\n";
        if ((time_us_32()- enter_time) > 1000000) 
        {state = 0;}  

    }

    //state3
     if (state == 3){
        cout << "REV\n";
        state = 0;
    }
    }
}

//summary: this code is basically letting you use the potentiometer to go foward, stop and reverse based on the value of the potentiometer 
// potentiometer --> counterclockwise -->foward 
//poptentiometer -->clockwise 
//the potentiometer will show "stop" on sudo screen for 1 second when you move from couterclockwise(foward) to clockwise(reverse)

