
 #include "rcc_stdlib.h"
                using namespace std;
    
                int main()
                {
                    stdio_init_all();    
                    sleep_ms(1500);
                    cyw43_arch_init(); //setup 

                    cyw43_arch_gpio_put(0,1); //turns on LED

                    cout << "gonna blink now;)" << '\n';

                    while(true)
                    {   
                        sleep_ms(300);
                        cyw43_arch_gpio_put(0, !cyw43_arch_gpio_get(0)); //blinks LED
                    }
                }
            