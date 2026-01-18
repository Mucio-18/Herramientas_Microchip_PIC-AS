Para usar la biblioteca delay es necesario copiar la pareja de archivos .inc y .S
en la carpeta del proyecto que estemos usando:

ejemplo para 4 mega hertz:

	/header files
		|---> delay4M.inc 

	/source files
		|---> main.S
		|---> delay4M.S

Para usar la biblioteca unicamente se debe de escribir ' #include "delay4M.inc" ' debajo
de XC8.inc

ejemplo para 4 mega hertz:

	#include <xc8.inc>
	#include "delay4M.inc"

Posteriormente usando el macro 'delay_ms x' donde x es el valor en mili segundos se 
generará un retardo de el tiempo establecido, el tiempo puede ser de 1 a 65535 ms

ejemplo para 4 mega hertz:

	mainLoop:
		bsf RB0
		delay_ms 500
		bcf RB0
		delay_ms 500
		goto mainLoop

El código hará parpadear un LED conectado al pin RB0 cada 500ms
