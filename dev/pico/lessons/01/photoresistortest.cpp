#include "rcc_stdlib.h"
using namespace std;

int main(void)
{
    stdio_init_all();
    sleep_ms(1000);

    // Initialize the light sensor gpio as ADC
    adc_init();
    adc_gpio_init(26);
    adc_select_input(0); //Select pin26 ADC input

    cyw43_arch_init();
    cyw43_arch_gpio_put(0, true);

    while(true)
    {   
        uint16_t light = adc_read();
        cout << "light val: " << light << "\n";
        sleep_ms(100);
    }
}