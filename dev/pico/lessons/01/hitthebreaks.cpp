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
    cyw43_arch_gpio_put(0,1); //led on
    rcc_init_pushbutton(); //set up button

    Motor motors; //struct setup
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000); //setup left and right
    MotorsOn(&motors); //enable PWM

    rcc_init_i2c(); //setup pico i2c
    VL53L0X lidar; //class
    rcc_init_lidar(&lidar); //setup lidar on i2c1
    
    Servo s3; //struct setup
    ServoInit(&s3, 18, false, 50); //setup 
    ServoOn(&s3); //enable PWM

    bool blinking = false;
    bool foward = false;
    bool stop = false;
    uint16_t distance;


    while(true)
    {
        if(!gpio_get(RCC_PUSHBUTTON)) //if gpio NOT high
        {        
        blinking=false;
        ServoPosition(&s3, 50); //50% of range (forwards)
        MotorPower(&motors, 80, 70);  // %motor speed
        }

        distance = getFastReading(&lidar);
        cout << "distance: " << distance << "\n";
        sleep_ms(100);

        if(distance <= 200){
            MotorPower(&motors, 50, 0); //stop
            blinking = true;
        }

        if(blinking){
            blink_led(300);
        }
    }
}

//Hit the brakes!
    //Use button to start robot's wheels
    //Have servo face forwards
    //Have robot drive forwards
    //If an obstacle is detected, hit the brakes!





   