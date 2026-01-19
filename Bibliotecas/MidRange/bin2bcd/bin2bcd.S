#include <xc.inc>

global BINREG,BCD0,BCD1,BCD2,double_dabble
    
psect udata_bank0
BINREG:	    DS 2
BCD0:	    DS 1
BCD1:	    DS 1
BCD2:	    DS 1
BCDTEMP:    DS 1
BCDCOUNT:   DS 1

psect   bin2bcd,global,class=CODE,delta=2 ; PIC10/12/16
double_dabble:
    clrf BCD0
    clrf BCD1
    clrf BCD2
    movlw 16
    movwf BCDCOUNT
    dd_loop:
	movf BCD0,W
	call bcd_adjust
	movwf BCD0
	movf BCD1,W
	call bcd_adjust
	movwf BCD1
	bcf CARRY
	rlf BINREG,F
	rlf BINREG+1,F
	rlf BCD0,F
	rlf BCD1,F
	rlf BCD2,F
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
    