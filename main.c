// Tue Aug 21 21:23:47 UTC 2018
// On branch KM_converser_aa-

#include <atmel_start.h>
// #include "driver_examples.h"
#include "serial_io.h"
#include "pins.h"
#include "dump.h"
#include "nyb_stack.h"
#include "clock_gen_OE.h"
#include "itoa.h"

void delays(void) { // delay some
    for (volatile int i=(3*21040); i>0; i--) {
        // empty loop
    }
}

void blink_two(void) {
    // clear first
    PORT->Group[PORTA].OUTCLR.reg  = (uint32_t)(1 << 17); // PA17 //  0 13 pinwrite  // D13
    for (int blinks=2; blinks >0; blinks--) {
        PORT->Group[PORTA].OUTTGL.reg  = (uint32_t)(1 << 17); // PA17 //    13 pintoggle // D13
        delays();
    }
}

void ldelays(void) {
    for (int ie=7; ie >0; ie--) {
        delays();
    }
}

void blink_awhile(void) {

    for (int iter=5; iter >0; iter--) {
        blink_two();
    }
}

int main(void)
{
    // rram, q, i
    uint8_t* rram = 0;
    int q = 0;
    int xec = -1; // true - yes, do exec

    /* Initializes MCU, drivers and middleware */
    atmel_start_init();
    SystemInit();
    // 8 MHz CPU
    pins_setup(); // initialize GPIO D13 PA17

    clock_gen_oe(); // clock generator 0 output enable

    // blink_awhile(); // is the clock running?

    // old location for this important function call:
    // USART_0_example();
    USART_0_example_upper(); // initialize

    // rram = srdump();

    // iterate the cdump over 19 lines of 16 bytes each:
    // for (int jk = 19; jk > 0; jk--) {

    // 0x8000 is ram size (32 kb)
    // That's 0x800 lines of 16 bytes each

    // 0x40000 size of internal flashROM (256 kb)
    if (xec != 0) {
     // 46 seconds
     // for (int jk = 0x800; jk > 0; jk--) {
        for (int jk =   0x7; jk > 0; jk--) { // 7 lines
            rram = cdump(); // dump.c
        }

        q = (int)rram;
        if (q > 2)  q = 2;
        if (q < 1)  q = 2;
        for (volatile int i=-1; i<q; i++) {
            blink_two();
            // ldelays();
        }

    } // fi xec

    /* Replace with your application code */

    // rram = ndump(); // nyb_stack.c
    // rram = cdump();    // dump.c

    _cr(); // examples/driver_examples.c

    call_me_now_ms_cleo();

    // New location for the demo:
    USART_0_example_lower();

    while (1) {
        toggle_d11();
    }
}
