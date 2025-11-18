;bits de configuracion

; CONFIG
  CONFIG  FOSC = INTOSCIO       ; Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
  CONFIG  WDTE = OFF            ; Watchdog Timer Enable bit (WDT disabled)
  CONFIG  PWRTE = OFF           ; Power-up Timer Enable bit (PWRT disabled)
  CONFIG  MCLRE = OFF           ; RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
  CONFIG  BOREN = OFF           ; Brown-out Detect Enable bit (BOD disabled)
  CONFIG  LVP = OFF             ; Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
  CONFIG  CPD = OFF             ; Data EE Memory Code Protection bit (Data memory code protection off)
  CONFIG  CP = OFF              ; Flash Program Memory Code Protection bit (Code protection off);---
;---
;---
#include <xc.inc>
#include "SPI_software.inc"	;poner la ruta del archivo .inc
#include "cronos4MHz.inc"	;retardos 4Mhz

#define SPITRIS TRISB
#define MOSITRIS TRISB0
#define MISOTRIS TRISB1
#define SCKTRIS	TRISB2
#define SPIPORT PORTB
#define MOSI RB0
#define MISO RB1
#define SCK RB2
#define SS RB7

#define SS RB7

psect udata_bank0
var1:	DS 1

psect resetVec,global,class=CODE,delta=2
resetVec:
    pagesel resetVec
    goto progPrin

psect intVec,global,class=CODE,delta=2
intVec:
    nop
	retfie

psect code
progIni:
    banksel TRISB
    bcf TRISB7
    call SPIMasterIni
    banksel 0
    bsf SS
    return

progPrin:
    call progIni
mainLoop:
    bcf SS			;Habilita el esclavo
    movlw 01010101B		;transmite 0x55
    call SPIMasterTX	
    bsf SS			;Deshabilita el esclavo
    call delay10ms
    goto mainLoop

end resetVec
	
