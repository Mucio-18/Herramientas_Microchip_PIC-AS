SPIMasterIni MACRO puerto,mosipin,misopin,sckpin
	IF puerto=PORTA
		#define puerto,mosipin MOSI
		#define puerto,misopin MISO
		#define puerto,sckpin SCK
		banksel TRISA
		bcf TRISA,mosipin
		bsf TRISA,misopin
		bcf TRISA,sckpin
		messg "Pines SPI Maestro PORTA configurados"
	ELSEIF puerto=PORTB
		#define puerto,mosipin MOSI
		#define puerto,misopin MISO
		#define puerto,sckpin SCK
		banksel TRISB
		bcf TRISB,mosipin
		bsf TRISB,misopin
		bcf TRISB,sckpin
		messg "Pines SPI Maestro PORTB configurados"
	ELSEIF puerto=PORTC
		#define puerto,mosipin MOSI
		#define puerto,misopin MISO
		#define puerto,sckpin SCK
		banksel TRISC
		bcf TRISC,mosipin
		bsf TRISC,misopin
		bcf TRISC,sckpin
		messg "Pines SPI Maestro PORTC configurados"
	ELSEIF puerto=PORTD
		#define puerto,mosipin MOSI
		#define puerto,misopin MISO
		#define puerto,sckpin SCK
		banksel TRISD
		bcf TRISD,mosipin
		bsf TRISD,misopin
		bcf TRISD,sckpin
		messg "Pines SPI Maestro PORTD configurados"
	ELSEIF puerto=GPIO
		#define puerto,mosipin MOSI
		#define puerto,misopin MISO
		#define puerto,sckpin SCK
		banksel TRISIO
		bcf TRISIO,mosipin
		bsf TRISIO,misopin
		bcf TRISIO,sckpin
		messg "Pines SPI Maestro GPIO configurados"
	ELSE messg "Puerto invalido o error de syntaxis"
	ENDIF
	ENDIF
	ENDIF
	ENDIF
	ENDIF
	banksel 0
	ENDM

SPISlaveIni MACRO puerto,mosipin,misopin,sckpin
	IF puerto=PORTA
		#define puerto,mosipin MOSI
		#define puerto,misopin MISO
		#define puerto,sckpin SCK
		banksel TRISA
		bsf TRISA,mosipin
		bcf TRISA,misopin
		bsf TRISA,sckpin
		messg "Pines SPI Esclavo PORTA configurados"
	ELSEIF puerto=PORTB
		#define puerto,mosipin MOSI
		#define puerto,misopin MISO
		#define puerto,sckpin SCK
		banksel TRISB
		bsf TRISB,mosipin
		bcf TRISB,misopin
		bsf TRISB,sckpin
		messg "Pines SPI Esclavo PORTB configurados"
	ELSEIF puerto=PORTC
		#define puerto,mosipin MOSI
		#define puerto,misopin MISO
		#define puerto,sckpin SCK
		banksel TRISC
		bsf TRISC,mosipin
		bcf TRISC,misopin
		bsf TRISC,sckpin
		messg "Pines SPI Esclavo PORTC configurados"
	ELSEIF puerto=PORTD
		#define puerto,mosipin MOSI
		#define puerto,misopin MISO
		#define puerto,sckpin SCK
		banksel TRISD
		bsf TRISD,mosipin
		bcf TRISD,misopin
		bsf TRISD,sckpin
		messg "Pines SPI Esclavo PORTD configurados"
	ELSEIF puerto=GPIO
		#define puerto,mosipin MOSI
		#define puerto,misopin MISO
		#define puerto,sckpin SCK
		banksel TRISIO
		bsf TRISIO,mosipin
		bcf TRISIO,misopin
		bsf TRISIO,sckpin
		messg "Pines SPI Esclavo GPIO configurados"
	ELSE messg "Puerto invalido o error de syntaxis"
	ENDIF
	ENDIF
	ENDIF
	ENDIF
	ENDIF
	banksel 0
	ENDM

SPIMasterSend MACRO dato
	movlw dato
	call SPIMasterTX


psect udata_bank0
SPITXREG:	DS 1
SPIRXREG:	DS 1
SPICOUNTER:	DS 1
DCounter1SPI:	DS 1
DCounter2SPI:	DS 1

psect code

SPIMasterTX:
	movwf SPITXREG
	movlw 8
	movwf SPICOUNTER
SPITXCicle:
	rlf SPITXREG,F
	btfss CARRY		
	goto SPITXCero
	SPITXUno:
		bsf MOSI
		call SPI_pulse		
		goto NextCicleTX
	SPITXCero:
		bcf MOSI
		call SPI_pulse
	NextCicleTX:
		decfsz SPICOUNTER,F
		goto SPITXCicle
		return

SPI_pulse:
    bsf SCK
    call SPIClock		
    bcf SCK
    call SPIClock
    return
		
SPISlaveRX:
	movlw 8
	movwf SPICOUNTER
SPIRXCicle:
	btfss SCK
	goto SPIRXCicle
	btfss MOSI
	goto SPIRXCero
	SPIRXUno:
		bsf CARRY
		goto NextCicleRX
	SPIRXCero:
		bcf CARRY
	NextCicleRX:
		btfsc SCK
		goto NextCicleRX
		rlf SPIRXREG,F
		decfsz SPICOUNTER
		goto SPIRXCicle
		return

SPIClock:
	MOVLW 0X49
	MOVWF DCounter1SPI
	MOVLW 0X02
	MOVWF DCounter2SPI
	LoopSPI:
		decfsz DCounter1SPI,F
		goto LoopSPI
		decfsz DCounter2SPI,F
		goto LoopSPI
		nop
		nop
		return
