#include "rcc_stdlib.h"
using namespace std;

int main()
{
    stdio_init_all();
    sleep_ms(1500);
    cyw43_arch_init(); //setup 
    cyw43_arch_gpio_put(0,1); //led on
    Motor motors; //struct setup
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000); //setup left and right
    MotorsOn(&motors); //enable PWM
    while(true)
    {
        MotorPower(&motors, 90, 80);  // %motor speed
        cout << "motors going forwards" << '\n';
        sleep_ms(100);
    }
}
            