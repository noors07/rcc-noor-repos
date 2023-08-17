#include "rcc_stdlib.h"
using namespace std;

void blink_led(int time){
    cyw43_arch_gpio_put(0, !cyw43_arch_gpio_get(0)); //blinks LED
    sleep_ms(time);
}
typedef enum{
    INIT,
    WAIT,
    SCAN,
    LEFT,
    RIGHT,
    FOLLOW,
    STOP
} state_t;


int main()
{
    stdio_init_all();    
    sleep_ms(1500);
    cyw43_arch_init();
    cyw43_arch_gpio_put(0,1);
    Servo s3;
    ServoInit(&s3, 18, false, 50);
    ServoOn(&s3);
    
    state_t state = INIT;
    uint32_t prev_time = 0;
    uint32_t prev_time2 = 0;
    uint32_t cur_time = 0;
    int servo_pos = 0;
    uint32_t dt = 50000;
    uint32_t dt2 = 50000;
    int pos [100];
    for (int i=0; i<101; i++ ) {

    }


    rcc_init_pushbutton(); //set up button

    Motor motors; //struct setup
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000); //setup left and right
    MotorsOn(&motors); //enable PWM

 
    rcc_init_i2c(); //setup pico i2c
    VL53L0X lidar; //class
    rcc_init_lidar(&lidar); //setup lidar on i2c1
   
    Left_Odom left;
    Right_Odom right;

    bool blinking = false;
    bool foward = false;
    bool stop = false;
    uint16_t distance;
    int loc;
    int i = 0;

    cyw43_arch_gpio_put(0,1); //turns on LED

   while(true)
   {
    distance = getFastReading(&lidar);

    if (blinking) {
        blink_led(100);
    }   
   
    cur_time = time_us_32();
    //State0
    switch(state) {
        case INIT:
            if(!gpio_get(RCC_PUSHBUTTON)) //if gpio NOT high
            {        
                blinking=true;
                state = SCAN;
            }
            break;
        case WAIT:
            //Do nothing
            //Check conditions
            /*if(cur_time - prev_time >= dt) {
                state = INCREMENT;
            }*/
            cout<<"in wait state\n";
            distance = getFastReading(&lidar);
            cout << "distance: " << distance << "\n";
            sleep_ms(100);
            state = SCAN;
            break;

        case SCAN:
            cout << "INCREMENT BY 1\n";
            //Increment position and set servo position
            for (int i=0; i<101; i++ ) {
            ServoPosition(&s3, i);
            distance = getFastReading(&lidar);
            cout << distance << '\n';
            sleep_ms(25);
            // Check conditions 
            if(distance <= 300){
                if (i < 50) {
                    // go right state
                    state = RIGHT;
                    cout << "RIGHT!\n";
                    break;
                }

                if (i > 50) {
                    // go left state
                    state = LEFT;
                    cout << "RIGHT!\n";
                    break;
                }
            }
            }

            break;
        
        case RIGHT:
            sleep_ms(100);
            distance = getFastReading(&lidar);

            MotorPower(&motors,100,0);//turn left
            if (distance <= 200){
                MotorPower(&motors, 0, 0);   //(0,0) = stop  
                state = STOP;
                //enter stop state             
            }
            break;

        case LEFT:
            sleep_ms(100);
            distance = getFastReading(&lidar);

            MotorPower(&motors, 0, 100);//turn left
            if (distance <= 200){
                MotorPower(&motors, 0, 0);   //(0,0) = stop  
                state = STOP;
                //enter stop state             
            }
            break;
        
        case FOLLOW:
            MotorPower(&motors,100,100);//going foward
            //state = SCAN;

            if (distance <= 200){
                MotorPower(&motors, 0, 0);   //(0,0) = stop               
            }
            stop = true ;
            break;
           
        case STOP:
            if (distance <= 200){ 
                MotorPower(&motors, 0, 0);   //(0,0) = stop               
            }
            break;
            
    }
}
}



    //Target Acquired

        //Use the button to start rotating the servo back and forth
        //When an object is detected, stop the servo
        //Store somewhere the "location" of the object
        //Hint: ~left or right
        //Have the servo face forwards
        //Rotate the robot towards the object until the object is detected again
        //Blink LED when target acquired:)
        //Flashy Bonus: Move forward until 2-3 cm from the object, then stop and blink LED
        // 03-target-found.cpp
