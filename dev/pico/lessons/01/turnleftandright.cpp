    #include "rcc_stdlib.h"
    using namespace std;
    
    //setup instance of config struct
    PID_control_config_t config;
    
    int main(){
        stdio_init_all();
        cyw43_arch_init();
        sleep_ms(1500);
    
        //init i2c first
        rcc_init_i2c(); 
        MPU6050 imu;
        imu.begin(i2c1);
        imu.calibrate();
    
        Motor motors;
        MotorInit(&motors, RCC_ENA, RCC_ENB, 20000);
        MotorsOn(&motors);
    
        //set values for config
        config.kp = 0.3; 
        config.ki = 0;
        config.kd = 0;
        config.ts = 0.01; // 1ms
        config.sigma = 0.1;
        config.lowerLimit = -20;
        config.upperLimit = 20;
        config.antiWindupEnabled = true;
    
        //create controller class based on config
        PID_control controller(config);
    
        //motor power variables setup
        int base_power = 80;
        int output; 
        float angle =0;
    
        //timing variables setup
        uint32_t current_time, previous_time;
        current_time = time_us_32();
    
        //pico led on when done setup
        cyw43_arch_gpio_put(0,1); 

        int state;
        uint32_t cur;
        uint32_t s0enter, s1enter, s2enter; //Timing variables
        uint32_t smprev ;
        uint32_t 
        left_count = left.getCount();
        right_count = right.getCount();
        while(true){
            //update current time
            current_time = time_us_32();
    
            //if config's timestep has passed
            if((current_time - previous_time) >= config.ts*1e6){
                
                //get data from sensors
                imu.update_pico();
                angle += imu.getAngVelZ()*config.ts;

                //calculate controller output:
                    //first input is desired value
                    //second input is actual value
                output = controller.pid(0.0, angle);
                 cout<< angle<<"\n";
                //set motor power based on controller output
                MotorPower(&motors, (base_power-output), (base_power + output));

                //reset previous time
                previous_time = cur;
                    
                if(state == 1) { 
                sp=0//sp= set point
                bp=50 //bp= base power
                if(cur - smprev>= smdt)
                { 
                state = 1; smprev = cur; }
                }
                //State 1
                if(state == 1) {
                sp=90
                bp=0
                if(cur - smprev>= smdt) { state = 2; smprev = cur; }
                }
                //State 2
                if(state == 2) {
                sp=90
                bp=25
                if(cur - smprev>= smdt) { state = 3; smprev = cur; }
                  }
            
        }
        
        }

    //drive straight then turn left and right 