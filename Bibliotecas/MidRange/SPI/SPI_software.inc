#define SPITRIS TRISB
#define MOSITRIS TRISB0
#define MISOTRIS TRISB1
#define SCKTRIS	TRISB2
#define SPIPORT PORTB
#define MOSI RB0
#define MISO RB1
#define SCK RB2

psect udata_bank0
SPITXREG:	DS 1
SPIRXREG:	DS 1
SPICOUNTER:	DS 1
DCounter1SPI:	DS 1
DCounter2SPI:	DS 1

psect code
SPIMasterIni:
	banksel SPITRIS
	bcf MOSITRIS
	bsf MISOTRIS
	bcf SCKTRIS
	banksel 0
	clrf SPIPORT
	return

SPISlaveIni:
	banksel SPITRIS
	bsf MOSITRIS
	bcf MISOTRIS
	bsf SCKTRIS
	banksel 0
	clrf SPIPORT
	return

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
		call SPIClock		
		goto NextCicleTX
	SPITXCero:
		bcf MOSI
		call SPIClock
	NextCicleTX:
		decfsz SPICOUNTER,F
		goto SPITXCicle
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
		rrf SPIRXREG,F
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
