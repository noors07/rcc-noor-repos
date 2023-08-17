//inclue any libs we need for this program
#include "rcc_stdlib.h"
using namespace std;

void print_val_n_times(int val, int n)
{
    //loop through n times
    //initialize an itarator
    int i=0;
    while(i < n)
    {
        // print value
        cout << "val:" << val << "'\n'";
        i=i+1;
    }
}

//function declaration
void compare (int a, int b) {
    if (a<b){
        cout << "a<b\n";
    }
    else if(a>b){
        cout<<"a>b\n";
    }
    else if (a==b) {
        cout<<"a=b\n";
    }
}
void compare_led (int a, int b) {
    if (a<b){
        cout << "a<b\n";
        cyw43_arch_gpio_put(0, false);
    }
    else if(a>b){
        cout<<"a>b\n";
         cyw43_arch_gpio_put(0, true);

    }
    else if (a==b) {
        cout<<"a=b\n";
    }
}
// make our main function, entry point to out program
int main () {
    //standard initialization for the pico w
stdio_init_all ();
    if (!cyw43_arch_init()){cout <<"CYW43 init failed!"<< "\n";}
    cyw43_arch_gpio_put(0, true);//turn the led on
//setup anything we need. this will run ONCE
int x_loc =0;
int y_loc =20;
//code here to run something repetedly
 while(true) {
    cout <<"print N times:" << x_loc << " | ";
    print_val_n_times(x_loc, y_loc);
    x_loc = x_loc + 1; //x_loc++
    sleep_ms(500);
}

}
