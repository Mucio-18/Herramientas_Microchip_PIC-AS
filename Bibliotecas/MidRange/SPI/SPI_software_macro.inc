psect udata_bank0
SPITXREG:	DS 1
SPIRXREG:	DS 1
SPICOUNTER:	DS 1
DCounter1SPI:	DS 1
DCounter2SPI:	DS 1

psect code

SPIMasterIni macro PORT,MOSIpin,MISOpin,SCKpin
	#define SPIPORT PORT
	#define MOSI MOSIpin
	#define MISO MISOpin
	#define SCK SCKpin
	banksel TRIS&SPIPORT
	bcf TRIS&SPIPORT,MOSI
	bsf TRIS&SPIPORT,MISO
	bcf TRIS&SPIPORT,SCK
	banksel 0
	clrf PORT&SPIPORT
	endm

SPISlaveIni macro PORT,MOSIpin,MISOpin,SCKpin
	#define SPIPORT PORT
	#define MOSI MOSIpin
	#define MISO MISOpin
	#define SCK SCKpin
	banksel TRIS&SPIPORT
	bsf TRIS&SPIPORT,MOSI
	bcf TRIS&SPIPORT,MISO
	bsf TRIS&SPIPORT,SCK
	banksel 0
	clrf PORT&SPIPORT
	endm

SPIMasterTX macro SPIDAT
	movlw 8
	movwf SPICOUNTER
	movlw SPIDAT
	movwf SPITXREG
	call SPITXCicle
	endm

SPISlaveRX macro SPIDAT
	movlw 8
	movwf SPICOUNTER,F
	call SPIRXCicle
	movwf SPIDAT
	endm

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
		rrf SPIREG,F
		decfsz SPICOUNTER
		goto SPIRXCicle
		movf SPIRXREG,W
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
