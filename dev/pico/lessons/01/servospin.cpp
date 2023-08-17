#include "rcc_stdlib.h"
using namespace std;
typedef enum{
    WAIT,
    INCREMENT,
    RESET
} state_t;

int main() {
    //Initializations 
    stdio_init_all();
    cyw43_arch_init();
    rcc_init_pushbutton();
    rcc_init_potentiometer();
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
    
    while(true) {
        //Do tons of unnecessary math here
        
    //Change dt based on potentiometer
    
    //Update current time
    cur_time = time_us_32();
    //State0
    switch(state) {
        case WAIT:
            //Do nothing
            //Check conditions
            if(cur_time - prev_time >= dt) {
                state = INCREMENT;
            }
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
    }
}