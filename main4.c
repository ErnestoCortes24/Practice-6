/*
 * File:   main3.c
 * Author: Ernesto Cortes Zamor
 *
 * Created on October 19, 2020, 8:47 AM
 */
#include "device_config.h"
#include "practice6.h"
#include <math.h>

enum exponent{
    bbase = 2,
    limit = 8
};
void portInit(void) {
/**
        TRISDbits.TRISB0 =1;
        TRISDbits.TRISB1 =1;
        TRISDbits.TRISB2 =1;
        TRISDbits.TRISB3 =1;
        TRISDbits.TRISB4 =1;
        TRISDbits.TRISB5 =1;
        TRISDbits.TRISB6 =1;
        TRISDbits.TRISB7 =1;
 **/
    ANSELB = 0;
    ANSELD = 0;
    TRISD= 255; // 11111111b - 0xFF
    
}

void larsonDisplay(void){
    LATB = 1;
    for(unsigned char i = 0; i < limit; i++){
        LATB = LATB << 1;
        __delay_ms(DELAY_SWEEP);
    } 
    for(unsigned char i = limit -1; i >= 0; i--){
        LATB = LATB >> 1;
        __delay_ms(DELAY_SWEEP);
    }
}

void main(void) {
    portInit();
    while(1){
        LATB = 0;
        unsigned char random = rand() % limit;
       
       /*
        * 1. Usar pow() -> Obtener el valor a asignar
        * 2. Hacer un shift registar con el valor rand
        */
        
        /**
        Forma 2.
         * random = 0
         * * (1 << 0) = 0b00000001 -> LATB | 0b00000001 -> LATB = Ob00000001;
         *
         * random = 4
         * (1 << 4 ) = 0b00010000 -> LATB | ob0001000 -> LATB = 0b00010000;
         * 
        */
        LATB |= (1 << random);
        
        __delay_ms(500);
        // obtener el estado de los Pushutton
        
        if(PORTB == ~(LATD)) {
            larsonDisplay();
        } else{ 
            __delay_ms(250);
            //Obtener el status de los PushButton
            if(PORTB == ~(LATD)){
                larsonDisplay();
            }
        } 
    }
    return;
}
