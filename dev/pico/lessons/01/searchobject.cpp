#include "rcc_stdlib.h"
using namespace std;

void blink_led(int time){
    cyw43_arch_gpio_put(0, !cyw43_arch_gpio_get(0)); //blinks LED
    sleep_ms(time);
}
//not done with this code yet
int main()
{
    stdio_init_all();
    sleep_ms(1500);
    cyw43_arch_init(); //setup 
    cyw43_arch_gpio_put(0,1); //led on
    rcc_init_pushbutton(); //set up button

     Motor motors;
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000);
    MotorsOn(&motors);
    cout << "after motors" << '\n';

    rcc_init_i2c(); //setup pico i2c

    VL53L0X lidar; //class
    rcc_init_lidar(&lidar); //setup lidar on i2c1

     Servo s3; //struct setup
    ServoInit(&s3, 18, false, 50); //setup 
    ServoOn(&s3); //enable PWM

    bool blinking = false;

    uint16_t distance;
  
    while(true)
    {

        if(!gpio_get(RCC_PUSHBUTTON)) //if gpio NOT high
        {        
        blinking=false;
        ServoPosition(&s3, 50); //50% of range (forwards)
        MotorPower(&motors, -85, 85);  // %motor speed
        }

        distance = getFastReading(&lidar);

        if(distance <= 200){
            MotorPower(&motors, 0, 0); //stop
            blinking = true;
        }

        if(blinking){
            blink_led(300);
        }
    }               
        
}
                







//Searching for object by spinning robot

   // Use button to start wheels
    //Hint: it is helpful if you make servo face forwards:)
    //Have robot spin clockwise, have 2 options:
    //rotate only one wheel
    //rotate one wheel forwards, one backwards
    //Stop the motors when lidar detects an object less than 200 mm away
    //Bonus: blink the LED to show object detected!
        //SOLUTION --> 01-lidar-spinning-robot.cpp
