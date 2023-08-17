
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
    int rot360deg = 260; //number counts for 360 degree rotation


    while(true)
    {   
        left_count = left.getCount();
        right_count = right.getCount();

        if(!gpio_get(RCC_PUSHBUTTON))
        {
            MotorPower(&motors, 100, 0); //spins left wheel only
            cout << "motors going forwards" << '\n';
        }

        if(left_count >= rot360deg){
            MotorPower(&motors, 0, 0);
        }



    }

}

//Rotate robot 360 Degrees

// 1 Pick your favorite wheel, only give that wheel power
// 2 Experimentally determine how many counts for the robot to spin around itself once (full 360)