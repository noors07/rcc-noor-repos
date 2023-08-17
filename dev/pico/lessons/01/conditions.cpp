#include "rcc_stdlib.h"
using namespace std;

if (grade>=90 && grade<=100) {printf("a\n")};
if (grade>=97){printf (student got an a\n)}
    else if (grade>=80 && grade<=89) {printf(b\n)}
        else if (grade>=70 && grade<=79) {printf(c\n)}
                else if (grade>=65 && grade<=69) {printf(d\n)}
                        else  {printf(f\n)}
                        if (grade<=43) printf("student got the lowest grade\n")



int main(void)
{
    stdio_init_all();

    if(cyw43_arch_init())
    {
        cout << "CYW43 init failed!" << "\n";
    }

    cyw43_arch_gpio_put(0, 1);
    
    while (true) {
        printf("Hello World\n");  
        sleep_ms(100); 
    } 
}

