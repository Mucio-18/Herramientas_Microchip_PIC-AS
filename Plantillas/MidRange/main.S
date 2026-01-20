;Bits de configuracion

;Bibliotecas
#include <xc.inc>		;biblioteca de registros

;Constantes
#define LEDpin BR0		;renombra pin RB0 a LEDpin

;Variables
psect udata_bank0		;banco 0 de memoria 
variable1: DS 1			;reserva 1 byte en la variable
variable2: DS 3			;reserva 3 bytes en la variable

;vector reinicio
psect resetVec,global,class=CODE,delta=2
resetVec:
	pagesel main	;selecciona pagina 0
	goto main		;va a programa principal

psect intVec,global,class=CODE,delta=2
intVec:				;vector interrupcion
	nop			;contenido de interrupciones
	retife			;regresa de interrupcion

psect code
ini:
	nop			;contenido de programa inicial
	return			;regresa de programa inicial

main:
	call ini		;llama a programa inicial
	loop:
		call sub1	;llamada a subrutinas
		nop		;contenido de programa principal
		goto loop	;loop infinito

sub1:				;subrutina generica
	nop			;contenido de subrutina
	return			;regresa de subrutina

end resetVec			;finaliza el programa
