

#include "rcc_stdlib.h" using namespace std; 
typedef enum {
     WAIT, 
     SCAN, 
     FOUND, 
     MOVE_FORWARD, 
     TARGET_ACQUIRED, 
     CONTINUE_STRAIGHT }// New state
     state_t; 

     int main() { 
    stdio_init_all(); 
    sleep_ms(1500); 
    cyw43_arch_init(); 
    cyw43_arch_gpio_put(0, 1);
     Servo s3; 
     ServoInit(&s3, 18, false, 50);
    ServoOn(&s3); 
    state_t state = WAIT; 
    int servo_pos = 0; 
    rcc_init_pushbutton();
     //set up button 
     Motor motors; 
     MotorInit(&motors, RCC_ENA, RCC_ENB, 1000); 
     MotorsOn(&motors); 
     VL53L0X lidar; 
     rcc_init_lidar(&lidar); 
     uint16_t distance; 
     int target_location = -1; 
     // Store the "location" of the target.
      while (true) { // State machine 
      switch (state)
       { case WAIT: if (!gpio_get(RCC_PUSHBUTTON)) { 
        // If the button is pressed, start scanning. 
        state = SCAN; 
        target_location = -1; 
        // Reset the target location.
         } break;
          case SCAN: 
         // Increment servo position and read the LIDAR distance. 
         ServoPosition(&s3, servo_pos); 
         distance = getFastReading(&lidar);
          if (distance <= 200) { 
            // Stop the servo and store the target location when an object is detected. 
            ServoPosition(&s3, 50); 
            // Face forwards.
             state = FOUND; } 
             if (servo_pos >= 100) 
             { state = FOUND; sleep_ms(300); 
             cyw43_arch_gpio_put(0, !cyw43_arch_gpio_get(0)); 
             } servo_pos++; 
             // Increment the servo position. 
             sleep_ms(50); 
             // Add a delay to slow down the servo rotation. 
             break;
              case FOUND: servo_pos = 0; 
              // Reset servo position.
               state = WAIT; 
               break; 
               case MOVE_FORWARD: distance = getFastReading(&lidar); 
               if (distance <= 20 && distance >= 2) 
               { // If the target is within 2-3 cm, stop and go to TARGET_ACQUIRED state. 
               state = TARGET_ACQUIRED; } 
               else if (distance > 20 && distance < 1000) { 
                // If there are no obstacles in front, go to CONTINUE_STRAIGHT state. 
               state = CONTINUE_STRAIGHT; } else { 
                // Otherwise, keep moving forward. 
                MotorPower(&motors, 100, 100);
                 ServoPosition(&s3, 50); 
                 // Face forwards. 
                 } 
                 sleep_ms(100); break; 
                 case CONTINUE_STRAIGHT: 
                 // Continue moving straight without obstacle detection for a while. 
                 MotorPower(&motors, 100, 100); 
                 ServoPosition(&s3, 50); 
                 // Face forwards. 
                 sleep_ms(1000); 
                  state = MOVE_FORWARD; 
                  // Go back to obstacle detection mode. 
                  break; case TARGET_ACQUIRED: 
                  // Target acquired, blink LED and stop the motors. 
                  cyw43_arch_gpio_put(0, !cyw43_arch_gpio_get(0)); 
                  MotorPower(&motors, 0, 0); 
                  break; }
         }
 }

                
