#include "rcc_stdlib.h"
using namespace std;

void blink_led(int time){
    cyw43_arch_gpio_put(0, !cyw43_arch_gpio_get(0)); //blinks LED
    sleep_ms(time);
}
typedef enum{
    WAIT,
    INCREMENT,
    RESET
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
    
    state_t state=WAIT;
    uint32_t prev_time = 0;
    uint32_t prev_time2 = 0;
    uint32_t cur_time = 0;
    int servo_pos = 0;
    uint32_t dt = 50000;
    uint32_t dt2 = 50000;

    rcc_init_pushbutton(); //set up button

    Motor motors; //struct setup
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000); //setup left and right
    MotorsOn(&motors); //enable PWM

    Left_Odom left; //class
    Right_Odom right; //class

 
    rcc_init_i2c(); //setup pico i2c
    VL53L0X lidar; //class
    rcc_init_lidar(&lidar); //setup lidar on i2c1
   
    bool blinking = false;
    bool foward = false;
    bool stop = false;
    uint16_t distance;



   while(true)
   {
             
    cur_time = time_us_32();
    //State0
    switch(state) {
        case WAIT:
            //Do nothing
            //Check conditions
            /*if(cur_time - prev_time >= dt) {
                state = INCREMENT;
            }*/
            sleep_ms(200);
            state = INCREMENT;
            break;
        case INCREMENT:
            cout << "INCREMENT BY 1!\n";
            //Increment position and set servo position
            servo_pos = servo_pos + 1;
            ServoPosition(&s3, servo_pos);
            // Check conditions
            if(servo_pos < 100){ //INCREMENT - WAIT
                prev_time = cur_time;
                state = WAIT;
            }
            if(servo_pos >= 100){ // INCREMENT - RESET
                prev_time2 = cur_time;
                state = RESET;
            }
            break;
        case RESET:
            cout << "RESETING SERVO POS\n";
            //set servo position to 0 to reset it
            servo_pos = 0;
            ServoPosition(&s3, servo_pos);
            //check conditions
            if(cur_time - prev_time2 >= dt2){//REST - WAIT
                prev_time = cur_time;
                state = WAIT;
            }
                break;
        }

        
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
                MotorPower(&motors, 0, 50); //turn
                blinking = true;
            }


            MotorPower(&motors, 100, 100);  // %motor speed
            cout << "motors going forwards" << '\n';
            sleep_ms(100);

            ServoPosition(&s3, 100); //50% of range (forwards)
            cout << "servo facing forwards" << '\n';
            sleep_ms(100);


            
            
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
