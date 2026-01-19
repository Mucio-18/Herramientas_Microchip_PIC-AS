Para usar la biblioteca delay es necesario copiar la pareja de archivos .inc y .S
en la carpeta del proyecto que estemos usando:

se recomienda la siguiente organización dentro del arbol de proyecto:

	/header files
		|---> bin2bcd.inc 

	/source files
		|---> main.S
		|---> bin2bcd.S

Para usar la biblioteca unicamente se debe de escribir ' #include "bin2bcd.inc" ' debajo
de XC8.inc

ejemplo:

	#include <xc8.inc>
	#include "delay4M.inc"

Con la biblioteca incluida tenemos 4 instrucciones nuevas disponibles:
	-bin2bcd f		---> Convierte 1 registro de 8 bits a BCD
	-bin2bcd_l k		---> Convierte 1 literal de 8 bits a BCD
	-bin2bcd_16 f,f		---> Convierte 1 dupla de registros 8 bits a BCD
	-bin2bcd_l_16 k		---> Convierte 1 literal de 16 bits a BCD
La biblioteca utiliza estos 3 registros guardados en el banco 0:
	-BCD0			---> Almacena el resultado de unidades y decenas
	-BCD1			---> Almacena el resultado de centenas y millares
	-BCD2			---> Almacena el resultado de decenas de millar

##########################################################################################
Ejemplo de uso bin2bcd:
##########################################################################################

	movlw 147	; Cargamos W con un dato
	movwf REG1	; Cargamos un registro cualquiera con W
	bin2bcd REG1	; convertimos ese registro a BCD
	
Los datos BCD convertidos se guardarán en 3 registros llamados BCD2,BCD1,BCD0
(ESTOS REGISTROS YA ESTÁN CREADOS COMO UNA VARIABLE) continuando el ejemplo
del número 147 la conversión se verá así en los 3 registros:

registro:	BCD2		BCD1		BCD0
casillas:	 cm | dm	 um | c		 d  | u
bits:		7654|3210	7654|3210	7654|3210
binaro:		0000|0000	0000|0001	0100|0111
decimal:	  0 | 0		  0 | 1		  4 | 7
dato:_________________________________^___________^___^__
donde:
	cm = centenas de millar (no se usa para 8 o 16 bits)
	dm = decenas de millar (no se usa para 8 bits)
	um = unidades de millar (no se usa para 8 bits)
	c  = centenas 
	d  = decenas
	u  = unidades

##########################################################################################
Ejemplo para bin2bcd_l:
##########################################################################################

	bin2bcd_l 243	; convertimos la literal a BCD

La conversión de datos del número 243 se verá asi en los 3 registros:

registro:	BCD2		BCD1		BCD0
casillas:	 cm | dm	 um | c		 d  | u
bits:		7654|3210	7654|3210	7654|3210
binaro:		0000|0000	0000|0010	0100|0011
decimal:	  0 | 0		  0 | 2		  4 | 3
dato:_________________________________^___________^___^__
donde:
	cm = centenas de millar (no se usa para 8 o 16 bits)
	dm = decenas de millar (no se usa para 8 bits)
	um = unidades de millar (no se usa para 8 bits)
	c  = centenas 
	d  = decenas
	u  = unidades

##########################################################################################
Ejemplo para bin2bcd_16
##########################################################################################

	movlw 0xFF		; Cargamos W con un dato (8 bits menos significativos)
	movwf REGL		; Cargamos un registro cualquiera con estos 8 bits 
	movlw 0XFF		; Cargamos W con un dato (8 bits más significativos)
	movwf REGH		; cargamos un registro cualquiera con estos 8 bits
	bin2bcd_16 REGH,REGL 	; convertimos los 2 registros a BCD (16bits en total)
                     \     \_______Registro menos significativo
                      \____________Registro más significativo

La conversión de datos del número 0xFFFF = 65635  se verá asi en los 3 registros:

registro:	BCD2		BCD1		BCD0
casillas:	 cm | dm	 um | c		 d  | u
bits:		7654|3210	7654|3210	7654|3210
binaro:		0000|0110	0101|0101	0011|0101
decimal:	  0 | 6		  5 | 5		  3 | 5
dato:_________________^___________^___^___________^___^__
donde:
	cm = centenas de millar (no se usa para 8 o 16 bits)
	dm = decenas de millar (no se usa para 8 bits)
	um = unidades de millar (no se usa para 8 bits)
	c  = centenas 
	d  = decenas
	u  = unidades


