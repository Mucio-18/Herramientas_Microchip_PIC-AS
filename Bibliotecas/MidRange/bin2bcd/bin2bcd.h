#ifndef BIN2BCD_H
    #define BIN2BCD_H

#ifndef __ASSEMBLER__
    #include<xc.h>
	extern uint16_t BINREG;
	extern uint8_t BCD0;
	extern uint8_t BCD1;
	extern uint8_t BCD2;
	extern void doubleDabble(void)
    	void bin2bcd(int);
#else
#include<xc.inc>	
messg "Biblioteca bin2bcd de www.mgv3d.com"
    
EXTRN _BINREG,_double_dabble

bin2bcd MACRO REGL
    movf REGL,W
    movwf _BINREG
    clrf _BINREG+1
    call _double_dabble
ENDM
    
bin2bcd_l MACRO literal
    if literal < 0
	error "valor negativo"
    endif
    if literal > 255
	error "valor superior a 8 bits"
    endif
    movlw literal
    movwf _BINREG
    clrf _BINREG+1
    call _double_dabble
ENDM
    
bin2bcd_16 MACRO REGH,REGL
    movf REGL,W
    movwf _BINREG
    movf REGH,W
    movwf _BINREG+1
    call _double_dabble
ENDM
    
bin2bcd_l_16 MACRO literal
    if literal < 0
	error "valor negativo"
    endif
    if literal > 65535
	error "valor superior a 16bits"
    endif
    movlw low(literal)
    movwf _BINREG
    movlw high(literal)
    movwf _BINREG+1
    call _double_dabble
ENDM
    
#endif

#endif

