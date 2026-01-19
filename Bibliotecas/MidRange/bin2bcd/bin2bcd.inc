#ifndef BIN2BCD_INC
    #define BIN2BCD_INC
    
messg "Biblioteca bin2bcd de www.mgv3d.com"
    
EXTRN BINREG,double_dabble

bin2bcd MACRO REGL
    movf REGL,W
    movwf BINREG
    clrf BINREG+1
    call double_dabble
ENDM
    
bin2bcd_l MACRO literal
    if literal < 0
	error "valor negativo"
    endif
    if literal > 255
	error "valor superior a 8 bits"
    endif
    movlw literal
    movwf BINREG
    clrf BINREG+1
    call double_dabble
ENDM
    
bin2bcd_16 MACRO REGH,REGL
    movf REGL,W
    movwf BINREG
    movf REGH,W
    movwf BINREG+1
    call double_dabble
ENDM
    
bin2bcd_l_16 MACRO literal
    if literal < 0
	error "valor negativo"
    endif
    if literal > 65535
	error "valor superior a 16bits"
    endif
    movlw low(literal)
    movwf BINREG
    movlw high(literal)
    movwf BINREG+1
    call double_dabble
ENDM
    
#endif
   


