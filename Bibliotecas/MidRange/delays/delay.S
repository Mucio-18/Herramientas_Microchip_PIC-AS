#include <xc.inc>

GLOBAL DELAY_COUNTER, delay_8bit

PSECT udata_bank0
DELAYREG1:	DS 1
DELAYREG2:	DS 1
DELAY_COUNTER:	DS 1    
    
psect delays,class=CODE,delta=2
 
delay_8bit:
    call delay_1ms
    decfsz DELAY_COUNTER,F
    goto delay_8bit
    return
    
delay_1ms:;	    997uS
    movlw 0X48
    movwf DELAYREG1
    movlw 0X02
    movwf DELAYREG2
    LOOP1ms:
    decfsz DELAYREG1, 1
    goto LOOP1ms
    decfsz DELAYREG2, 1
    goto LOOP1ms
    nop
    nop
    return

