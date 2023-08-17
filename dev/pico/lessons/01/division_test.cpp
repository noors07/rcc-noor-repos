#include "rcc_stdlib.h"
using namespace std;

int division(int a,int b)
{
return a/b;
}

int main(void)
{
    stdio_init_all();

    if(cyw43_arch_init())
    {
        cout << "CYW43 init failed!" << "\n";
    }

    cyw43_arch_gpio_put(0, 1);
    int x = 9;
    int y = 3;
    int div_result = divide(x, y);
    
    while (true) {
        printf("%d\n",div_result);  
        sleep_ms(100); 
        
    } 
}

