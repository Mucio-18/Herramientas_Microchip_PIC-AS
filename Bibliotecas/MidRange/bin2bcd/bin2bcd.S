#include <xc.inc>

global _BINREG,_BCD0,_BCD1,_BCD2,_double_dabble
    
psect udata_bank0
_BINREG:    DS 2
_BCD0:	    DS 1
_BCD1:	    DS 1
_BCD2:	    DS 1
BCDTEMP:    DS 1
BCDCOUNT:   DS 1

psect   bin2bcd,global,class=CODE,delta=2 ; PIC10/12/16
_double_dabble:
    clrf _BCD0
    clrf _BCD1
    clrf _BCD2
    movlw 16
    movwf BCDCOUNT
    dd_loop:
	movf _BCD0,W
	call bcd_adjust
	movwf _BCD0
	movf _BCD1,W
	call bcd_adjust
	movwf _BCD1
	bcf CARRY
	rlf _BINREG,F
	rlf _BINREG+1,F
	rlf _BCD0,F
	rlf _BCD1,F
	rlf _BCD2,F
	decfsz BCDCOUNT
	goto dd_loop
	return

bcd_adjust:
    movwf BCDTEMP
    movlw 0x0F
    andwf BCDTEMP,W
    sublw 4
    btfss CARRY
    goto add_low
checkhigh:
    movlw 0xF0
    andwf BCDTEMP,W
    sublw 0X40
    btfss CARRY
    goto add_high
    goto finish_adjust
    add_low:
	movlw 3
	addwf BCDTEMP,F
	goto checkhigh
    add_high:
	movlw 0x30
	addwf BCDTEMP,F
finish_adjust:
    movf BCDTEMP,W
    return
    
