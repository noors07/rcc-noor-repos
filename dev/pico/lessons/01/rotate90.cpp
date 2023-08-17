
#include "rcc_stdlib.h"
using namespace std;

int main()
{
    stdio_init_all();    
    sleep_ms(1500);
    cyw43_arch_init();
    cyw43_arch_gpio_put(0,1);

    rcc_init_pushbutton();

    Motor motors;
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000);
    MotorsOn(&motors);
    cout << "after motors" << '\n';

    Left_Odom left;
    Right_Odom right;
    cout << "after odom" << '\n';

    int left_count = 0;
    int right_count = 0;
    int rot90deg = 65; //number of counts for a 90 degree rotation


    while(true)
    {   
        left_count = left.getCount();
        right_count = right.getCount();

        if(!gpio_get(RCC_PUSHBUTTON))
        {
            MotorPower(&motors, 50, 0); //spins left wheel only
        }

        if(left_count >= rot90deg){
            MotorPower(&motors, 0, 0);
        }

        

    }
}

//Rotate robot 90 Degrees

    //Give only one wheel power
    //Experimentally determine number of counts to rotate 90 degrees
    //Stop the robot after it rotates 90 degrees
