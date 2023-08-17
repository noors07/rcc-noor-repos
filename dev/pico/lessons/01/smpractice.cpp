#include "rcc_stdlib.h"
using namespace std;

int state;
uint32_t cur;
uint32_t s0enter, s1enter, s2enter; 
uint32_t dt0 = 1000000;
uint32_t dt1 = 3000000;

int main()
{
studio_init_all();
cur = time_us_32;
s0enter =  s1enter=s2enter=cur;

while(true){
    cur = time_us_32();
    if(state==0)
    {
        if(cur - s0enter >=)
    }
}



}

//statemachine practice