#include "rcc_stdlib.h"
using namespace std;

int main()
{
    stdio_init_all();
    sleep_ms(1000);
    cyw43_arch_init();
    cyw43_arch_gpio_put(0, 1); //turns on led

    Left_Odom left; //struct
    Right_Odom right; //struct

       while(true)
    {
        int left_count = left.getCount(); 
        int right_count = right.getCount();
        cout << left_count << "|" << right_count << "\n";
        sleep_ms(200);
    }
}
//How many counts in one rotation?
//Experimentally determine how many counts getCount() returns in one rotation of the wheel
//How many counts for 10 rotations?
