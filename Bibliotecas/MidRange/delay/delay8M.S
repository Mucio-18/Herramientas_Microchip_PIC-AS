#include <xc.inc>

GLOBAL DELAY_COUNTERL,DELAY_COUNTERH, delay_8bit, delay_16bit

PSECT udata_shr
DELAYREG1:	DS 1
DELAYREG2:	DS 1
DELAY_COUNTERL:	DS 1
DELAY_COUNTERH: DS 1
    
psect delay,global,class=CODE,delta=2
 
delay_8bit:
    call delay_1ms
    decfsz DELAY_COUNTERL,F
    goto delay_8bit
    return
    
delay_16bit:
    movf DELAY_COUNTERL,W
    iorwf DELAY_COUNTERH,W
    btfsc ZERO
    return
    call delay_1ms16
    movlw 1
    subwf DELAY_COUNTERL,F
    btfss CARRY
    decf DELAY_COUNTERH,F
    goto delay_16bit
    
    
delay_1ms:;	    
    movlw 0X95
    movwf DELAYREG1
    movlw 0X03
    movwf DELAYREG2
    LOOP1ms:
    decfsz DELAYREG1, 1
    goto LOOP1ms
    decfsz DELAYREG2, 1
    goto LOOP1ms
    nop
    return

delay_1ms16:
    movlw 0X93
    movwf DELAYREG1
    movlw 0X03
    movwf DELAYREG2
    LOOP1ms16:
    decfsz DELAYREG1, 1
    goto LOOP1ms16
    decfsz DELAYREG2, 1
    goto LOOP1ms16
    return
