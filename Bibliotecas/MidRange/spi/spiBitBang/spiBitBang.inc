#ifndef SPIBITBANG_INC
#define SPIBITBANG_INC
    ;Pines
    GLOBAL SPI_PORT,SPI_TRIS,SPI_MOSI,SPI_MISO,SPI_SCK
    ;<editor-fold defaultstate="collapsed" desc="simbolos">
    #define mode0 0
    #define mode1 1
    #define mode2 2
    #define mode3 3
    ;</editor-fold>
    ;Funciones
    GLOBAL spiBBtx,spiBBrx,spiBBtxrx
    ;Registros
    GLOBAL SPITXREG,SPIRXREG
    
    ;<editor-fold defaultstate="collapsed" desc="spiTxRxIni mode">
    spiTxRxIni macro puerto,MOSI,MISO,SCK,mode
	SPI_PORT    equ	PORT&puerto
	SPI_TRIS    equ TRIS&puerto
	SPI_MOSI    equ MOSI
	SPI_MISO    equ MISO
	SPI_SCK	    equ SCK   
	messg "biblioteca SPI bit bang www.mgv3d.com"
	banksel SPI_TRIS
	bcf SPI_TRIS,SPI_MOSI
	bsf SPI_TRIS,SPI_MISO
	bcf SPI_TRIS,SPI_SCK
	banksel SPI_PORT
	if (mode=0)|(mode=1)
	    bcf SPI_PORT,SPI_SCK
	    if mode=0
		messg "SPI TxRx modo 0"
	    else
		messg "SPI TxRx modo 1"
	    endif
	else
	    bsf SPI_PORT,SPI_SCK
	    if mode=2
		messg "SPI TxRx modo 2"
	    else 
		messg "SPI TxRx modo 3"
	    endif
	endif
	if PORT&puerto=PORTA
	    messg "SPI Bit Bang Usando puerto A"
	endif
	if PORT&puerto=PORTB
	    messg "SPI Bit Bang Usando puerto B"
	endif
	if (MOSI > 7)|(MISO>7)|(SCK>7)
	    error "spiPins de 0 a 7"
	endif
    endm
    ;</editor-fold>
    ;<editor-fold defaultstate="collapsed" desc="spiTxIni mode">
    spiTxIni macro puerto,MOSI,SCK,mode
	SPI_PORT    equ	PORT&puerto
	SPI_TRIS    equ TRIS&puerto
	SPI_MOSI    equ MOSI
	SPI_MISO    equ 0
	SPI_SCK	    equ SCK   
	messg "biblioteca SPI bit bang www.mgv3d.com"
	banksel SPI_TRIS
	bcf SPI_TRIS,SPI_MOSI
	bcf SPI_TRIS,SPI_SCK
	banksel SPI_PORT
	if (mode=0)|(mode=1)
	    bcf SPI_PORT,SPI_SCK
	else
	    bsf SPI_PORT,SPI_SCK
	endif
	if (mode=0)|(mode=1)
	    bcf SPI_PORT,SPI_SCK
	    if mode=0
		messg "SPI Tx modo 0"
	    else
		messg "SPI Tx modo 1"
	    endif
	else
	    bsf SPI_PORT,SPI_SCK
	    if mode=2
		messg "SPI Tx modo 2"
	    else 
		messg "SPI Tx modo 3"
	    endif
	endif
	if PORT&puerto=PORTA
	    messg "SPI Bit Bang Usando puerto A"
	endif
	if PORT&puerto=PORTB
	    messg "SPI Bit Bang Usando puerto B"
	endif
	if (MOSI > 7)|(SCK>7)
	    error "spiPins de 0 a 7"
	endif
    endm
    ;</editor-fold>
    ;<editor-fold defaultstate="collapsed" desc="spiRxIni mode">
    spiRxIni macro puerto,MISO,SCK,mode
	SPI_PORT    equ	PORT&puerto
	SPI_TRIS    equ TRIS&puerto
	SPI_MOSI    equ 0
	SPI_MISO    equ MISO
	SPI_SCK	    equ SCK   
	messg "biblioteca SPI bit bang www.mgv3d.com"
	banksel SPI_TRIS
	bsf SPI_TRIS,SPI_MISO
	bcf SPI_TRIS,SPI_SCK
	banksel SPI_PORT
	if (mode=0)|(mode=1)
	    bcf SPI_PORT,SPI_SCK
	else
	    bsf SPI_PORT,SPI_SCK
	endif
	if (mode=0)|(mode=1)
	    bcf SPI_PORT,SPI_SCK
	    if mode=0
		messg "SPI Rx modo 0"
	    else
		messg "SPI Rx modo 1"
	    endif
	else
	    bsf SPI_PORT,SPI_SCK
	    if mode=2
		messg "SPI Rx modo 2"
	    else 
		messg "SPI Rx modo 3"
	    endif
	endif
	if PORT&puerto=PORTA
	    messg "SPI Bit Bang Usando puerto A"
	endif
	if PORT&puerto=PORTB
	    messg "SPI Bit Bang Usando puerto B"
	endif
	if (MISO>7)|(SCK>7)
	    error "spiPins de 0 a 7"
	endif
    endm
    ;</editor-fold>
    ;<editor-fold defaultstate="collapsed" desc="spiTxL literal">
    spiTxL macro literal
	if (literal>255)|(literal<0)
	    error "literal invalida"
	endif
	movlw literal
	movwf SPITXREG
	call spiBBtx
    endm
    ;</editor-fold>
    ;<editor-fold defaultstate="collapsed" desc="spiTx file">
    spiTx macro registro
	movf registro,W
	movwf SPITXREG
	call spiBBtx
    endm
    ;</editor-fold>
    ;<editor-fold defaultstate="collapsed" desc="spiRx">
    spiRx macro 
	call spiBBrx
    endm
    ;</editor-fold>
    ;<editor-fold defaultstate="collapsed" desc="spiTxRxL">
    spiTxRxL macro literal
	if (literal>255)|(literal<0)
	    error "literal invalida"
	endif
	movlw literal
	movwf SPITXREG
	call spiBBtxrx
    endm
    ;</editor-fold>
#endif
