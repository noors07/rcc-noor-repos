#include "rcc_stdlib.h"
using namespace std;

int main()
{
    stdio_init_all();
    sleep_ms(1000);
    cyw43_arch_init();
    cyw43_arch_gpio_put(0, 1); //turns on led
    rcc_init_i2c();//lidar
    VL53L0X lidar;
    rcc_init_lidar(&lidar);
    Motor motors;
    MotorInit (&motors, RCC_ENA, RCC_ENB, 20000);
    MotorsOn(&motors);
    MotorPower(&motors, 0, 0);
    
    //control syatem varibles 
    float desired = 200;// the desired distance
    float actual;// the actual distance from the lidar
    uint16_t lidar_reading; 
    float error;//error input to controller
    float kp=1;//proportional gain
    float power;//piower to motors

    while (true) {
        //get the distance from the lidar
        lidar_reading = getFastReading(&lidar);
        //convert the lidar sensor from uinit to float
        actual = static_cast<float>(lidar_reading);
        //calculate the error
        error = desired - actual;
        //calculate the controller output (kp*error)
        power= kp*error;
        //saturate the controller output(dont allow outsid eof range -100-->100)
        power= max(min(power,100.f), -100.f);
        //convert power to an integer and flip sign so direction is propper
        int power_int = static_cast<int>(-1*power);
        //apply the controller output(power) to the motors
        MotorPower (&motors, power_int, power_int);
        //print some stuff for debugging
        cout << "des:" <<desired<< "act:" << actual << "err:" << error << "power:" <<power_int << "\n";
    }
}