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
   // FOLLOW,//i comented out this state bc i never switch into it
    STOP,
    FOLLOW_AND_SCAN,
    PHOTORESISTOR
} state_t;

/*
currently the robot can  detect obstacles and dodge them and continue going straight while scaning 
*/

int main()
{

    adc_init();
    adc_gpio_init(26);
    adc_select_input(0); //Select pin26 ADC input
//the code above is for the pphotoresistor

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
    for (int i=0; i<100; i=i+2 ) {
        pos[i] = i;
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

    int left_count = 0;
    int right_count = 0;
    int rot90deg = 35; //65; this changes how big of a turn you take 
    uint16_t light;

    bool blinking = false;
    bool foward = false;
    bool stop = false;
    uint16_t distance;
    int loc;
    int i = 0;

    cyw43_arch_gpio_put(0,1); //turns on LED

   while(true)
   {
    light = adc_read();//photoresistor
    cout << "light val: " << light << "\n";
    sleep_ms(100);
    distance = getFastReading(&lidar);
    cout << "distance: " << distance << "\n";

    //State0
    switch(state) {
        case INIT:
            if(!gpio_get(RCC_PUSHBUTTON)) //if gpio NOT high
            {        
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
            sleep_ms(100);
            state = SCAN;
            break;

        case SCAN:
            //Increment position and set servo position
            cout << "in scan state\n";
            MotorPower(&motors, 0, 0);
            for (int i=0; i<101; i=i+2 ) {
                ServoPosition(&s3, i);
                distance = getFastReading(&lidar);
                cout << distance << '\n';
                sleep_ms(15);
                // Check conditions 
                if(distance <= 300){
                    if (i < 50) {
                        // go right state
                        state = RIGHT;
                        ServoPosition(&s3, 50);
                        cout << "RIGHT!\n";
                    break;
                    }

                    if (i > 50) {
                    // go left state
                    state = LEFT;
                    ServoPosition(&s3, 50);
                    cout << "LEFT!\n";
                    break;
                    }
                }
            }

            break;
        
        case RIGHT:
            cout << "in right state\n";
            sleep_ms(100);
            distance = getFastReading(&lidar);

            MotorPower(&motors, 0, 50); //spins right wheel only
            if(right.getCount() >= rot90deg){
                MotorPower(&motors, 0, 0);
                state = FOLLOW_AND_SCAN;
                right.setZero();
            }
            break;
            

        case LEFT:
            cout << "in left state\n";
            sleep_ms(100);
            distance = getFastReading(&lidar);

            MotorPower(&motors, 50, 0); //spins left wheel only
    
            if(left.getCount() >= rot90deg){
                MotorPower(&motors, 0, 0);
                state = FOLLOW_AND_SCAN;
                left.setZero();
            }
           break;
            
        
      /*  case FOLLOW:
            cout << "in follow state\n";
            MotorPower(&motors,50,50);//going foward
            //state = SCAN;

            if (distance <= 200){
                MotorPower(&motors, 0, 0);   //(0,0) = stop               
                state = SCAN;
            }
            break;*/
           
        case STOP:
            cout << "in stop state\n";
            sleep_ms(100);
            /*distance = getFastReading(&lidar);
            MotorPower(&motors, 50, 50);   //(0,0) = stop   
            if (distance <= 200){ */
                MotorPower(&motors, 0, 0);   //(0,0) = stop   
               /* ServoPosition(&s3, 0);
                sleep_ms(500);
                state = SCAN; 
                }*/
                
                
                if (light <= 3000){
                    state = FOLLOW_AND_SCAN; // the robot will continue going after the flash is removed 
                }
                cout << "less than 3000\n";
            break;

        case FOLLOW_AND_SCAN:
            cout << "in follow and scan state\n";
            if (light >= 3001) {      
                    // go photoresistor state
                    state = STOP;
                    
                    //i also have to reset the number for the photoresitor
            break;
                    }
            
            MotorPower(&motors,40,40);//going foward
            //state = SCAN;
            //Increment position and set servo position
            for (int i=0; i<101; i=i+2 ) {
                cout << "in follow and scan loop\n";
                ServoPosition(&s3, i);
                distance = getFastReading(&lidar);
                cout << distance << '\n';
                sleep_ms(15);
                // Check conditions 
                if(distance <= 300) 
                {
                    /* if (light >= 3200) {      
                        // go photoresistor state
                        state = STOP;
                        //i also have to reset the number for the photoresitor
                        break;
                    }*/

                    if (i < 50) 
                    {
                        // go right state
                        state = RIGHT;
                        cout << "RIGHT!\n";
                        right.setZero();
                        break;
                    }
                   if (i > 50) {
                        // go left state
                        state = LEFT;
                        cout << "LEFT!\n";
                        left.setZero();
                        break;
                    }
                }
            }
            break;
        }
    }
}



    //final project

       /* 1. the robot will dodge obstacles 
        2. has a goal to reach an end target which is holding a bright light to deliver bandaids to  
        */

       
