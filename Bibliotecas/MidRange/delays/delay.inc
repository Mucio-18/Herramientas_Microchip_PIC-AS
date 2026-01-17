#ifndef DELAYS_INC
#define DELAYS_INC

; Frecuencia por defecto si el usuario olvida definirla
#ifndef _XTAL_FREQ
    #define _XTAL_FREQ 4000000
    messg "_XTAL_FREQ no definido, usando 4MHz en su lugar"
#endif

; Declaración de funciones y variables externas
EXTRN DELAY_COUNTER,delay_8bit

; Macro de interfaz
delay_ms MACRO valor
    IF valor > 255
	ERROR "Delay muy grande"
    ENDIF
    movlw   valor
    movwf   DELAY_COUNTER
    fcall   delay_8bit
ENDM

#endif


