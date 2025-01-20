#include <atari.h>
#include <stdint.h>

#define SPACE    0
#define ZERO     16
#define H        40
#define I        41
#define L        44
#define O        47
#define CIRCLE   84
#define ARROW_UP 92
#define ARROW_DN 93
#define ARROW_LT 94
#define ARROW_RT 95

void print_i(uint16_t address, uint8_t input);
void print_pot(uint16_t address, uint8_t input);
void print_hilo(uint16_t address, uint8_t input);
void print_trig_buf(uint16_t address, uint8_t input);

int main (void)
{
    OS.ch = 255;
    while(OS.ch != KEY_ESC) {
        OS.savmsc[40*10+10] = PIA.porta & JOY_UP_MASK ? ARROW_UP : ARROW_UP + 128;
        OS.savmsc[40*11+9] = PIA.porta & JOY_LEFT_MASK ? ARROW_LT : ARROW_LT + 128;
        OS.savmsc[40*11+10] = GTIA_READ.trig0 ? CIRCLE : CIRCLE + 128;
        print_trig_buf(40*8, GTIA_READ.trig0);
        OS.savmsc[40*11+11] = PIA.porta & JOY_RIGHT_MASK ? ARROW_RT : ARROW_RT + 128;        
        OS.savmsc[40*12+10] =  PIA.porta & JOY_DOWN_MASK ? ARROW_DN : ARROW_DN + 128;

        OS.savmsc[40*10+30] = PIA.porta>>4 & JOY_UP_MASK ? ARROW_UP : ARROW_UP + 128;
        OS.savmsc[40*11+29] = PIA.porta>>4 & JOY_LEFT_MASK ? ARROW_LT : ARROW_LT + 128;
        OS.savmsc[40*11+30] = GTIA_READ.trig1 ? CIRCLE : CIRCLE + 128;
        print_trig_buf(40*16, GTIA_READ.trig1);
        OS.savmsc[40*11+31] = PIA.porta>>4 & JOY_RIGHT_MASK ? ARROW_RT : ARROW_RT + 128;        
        OS.savmsc[40*12+30] =  PIA.porta>>4 & JOY_DOWN_MASK ? ARROW_DN : ARROW_DN + 128;
        
        print_i(40*13+9, OS.paddl0);
        print_pot(0, OS.paddl0);
        print_hilo(40*13+13, OS.paddl0);

        print_i(40*14+9, OS.paddl1);
        print_pot(40*1, OS.paddl1);
        print_hilo(40*14+13, OS.paddl1);

        print_i(40*13+29, OS.paddl2);
        print_pot(40*22, OS.paddl2);
        print_hilo(40*13+33, OS.paddl2);

        print_i(40*14+29, OS.paddl3);
        print_pot(40*23, OS.paddl3);
        print_hilo(40*14+33, OS.paddl3);
        /* TODO: do without OS in DLI */
    }
    return 0;
}

void print_i(uint16_t address, uint8_t input) {
    OS.savmsc[address]  = input / 100 + ZERO;
    OS.savmsc[address+1] = (input % 100) / 10 + ZERO;
    OS.savmsc[address+2] = input % 10 + ZERO;
}

void print_pot(uint16_t address, uint8_t input){
    uint8_t i;

    for(i=0; i<(uint8_t)40; ++i){
        if(input / (uint8_t)6 == i)
            OS.savmsc[address + i]  = CIRCLE;
        else
            OS.savmsc[address + i] = 0;
    }
}

void print_hilo(uint16_t address, uint8_t input){
    if(input > 228 / 2) {
        OS.savmsc[address]  = H;
        OS.savmsc[address+1]  = I;
    } else {
        OS.savmsc[address]  = L;
        OS.savmsc[address+1]  = O;
    }
}

void print_trig_buf(uint16_t address, uint8_t input){
    uint8_t i;

    for(i=0; i<(uint8_t)39; ++i)
        OS.savmsc[address+i] = OS.savmsc[address+i+1];

    OS.savmsc[address+39] = input ? 0 : CIRCLE;
}