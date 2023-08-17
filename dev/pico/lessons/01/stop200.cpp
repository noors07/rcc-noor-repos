#include "rcc_stdlib.h"
using namespace std;

int main()
{
stdio_init_all();    
sleep_ms(1500);
cyw43_arch_init(); //setup 
cyw43_arch_gpio_put(0,1); //turns on LED

rcc_init_pushbutton(); //set up button


   Motor motors; //struct setup
        MotorInit(&motors, RCC_ENA, RCC_ENB, 1000); //setup left and right
        MotorsOn(&motors); //enable PWM
    
    Left_Odom left;
    Right_Odom right;

    int left_count = 0 ;
    int right_count = 0 ;          
    
     while(true)
    {
        left_count = left.getCount(); //current left count
        right_count = right.getCount(); //current right count
    cout << "left count" << '\n';
        if(!gpio_get(RCC_PUSHBUTTON))
        {
         MotorPower(&motors, 80, 80);  // motor speed
        }
        if(left_count >= 200 && right_count >= 200)
        {
            MotorPower(&motors, 0, 0); //stop motors
        }
    }
 }

 // in this challenge we need to Stop after a distance

    //1 Use the button to start the motors
    //2 Give both motors the same power (something above the deadband)
    //3 Stop the robot when BOTH encoders reach 200 counts
