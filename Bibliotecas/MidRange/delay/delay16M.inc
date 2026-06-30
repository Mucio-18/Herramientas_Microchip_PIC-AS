#ifndef DELAY_INC
#define DELAY_INC

messg "Biblioteca delay de www.mgv3d.com"
messg "Usando cristal de 16MHz"

; Declaración de funciones y variables externas
EXTRN DELAY_COUNTERL,DELAY_COUNTERH,delay_8bit,delay_16bit

; Macro de interfaz
delay_ms MACRO valor
    if valor < 1
	error "el tiempo debe ser entre 1 y 65535"
    endif
    if valor < 256
	movlw   valor
	movwf   DELAY_COUNTERL
	fcall   delay_8bit	
    endif
    if valor > 65535
	error "el tiempo debe ser entre 1 y 65535"
    endif
    if valor > 255
	movlw low(valor)
	movwf DELAY_COUNTERL
	movlw high(valor)
	movwf DELAY_COUNTERH
	fcall delay_16bit
    endif
ENDM

#endif

