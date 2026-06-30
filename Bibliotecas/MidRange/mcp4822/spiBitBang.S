#include <xc.inc>
#include "spiBitBang.inc"

global SPITXREG,SPIRXREG,spiBBtx,spiBBrx,spiBBtxrx,spiSCKtoogle

;<editor-fold defaultstate="collapsed" desc="REGISTROS">
psect udata_bank0
    SPIBBCOUNT: DS 1
    SPITXREG:   DS 1
    SPIRXREG:   DS 1
;</editor-fold>  
psect code
;psect spiBitBang,global,class=CODE,delta=2 ; PIC10/12/16
;<editor-fold defaultstate="collapsed" desc="spiSCKtoogle">
spiSCKtoogle:
    btfss SPI_PORT,SPI_SCK
    goto spiSCK1
    spiSCK0:
	bcf SPI_PORT,SPI_SCK
	return
    spiSCK1:
	bsf SPI_PORT,SPI_SCK
	return
;</editor-fold>
;<editor-fold defaultstate="collapsed" desc="spiBBtx">
spiBBtx:
    movlw 8
    movwf SPIBBCOUNT
    spiBBloopTx:
	rlf SPITXREG,F
	btfsc CARRY
	goto spiBBOneTx
	spiBBZeroTx:
	    bcf SPI_PORT,SPI_MOSI
	    goto spiBBtxClock
	spiBBOneTx:
	    bsf SPI_PORT,SPI_MOSI
	    nop
	    nop
	spiBBtxClock:
	    call spiSCKtoogle
	    call spiSCKtoogle
	    decfsz SPIBBCOUNT,F
	    goto spiBBloopTx
	    bcf SPI_PORT,SPI_MOSI;<<<<<<<<<<<<<<<<
	    return
;</editor-fold>
;<editor-fold defaultstate="collapsed" desc="spiBBrx">
spiBBrx:
    movlw 8
    movwf SPIBBCOUNT
    spiBBloopRx:
	call spiSCKtoogle
	call spiSCKtoogle
	btfsc SPI_PORT,SPI_MISO
	goto spiBBOneRx
	spiBBZeroRx:
	    bcf CARRY
	    goto spiBBrxSave
	spiBBOneRx:
	    bsf CARRY
	    nop
	    nop
	spiBBrxSave:
	    rlf SPIRXREG,F
	    decfsz SPIBBCOUNT,F
	    goto spiBBloopRx
	    return
;</editor-fold>
;<editor-fold defaultstate="collapsed" desc="spiBBtxrx">
spiBBtxrx:
    movlw 8
    movwf SPIBBCOUNT
    spiBBloopTxRx:
	rlf SPITXREG,F
	btfsc CARRY
	goto spiBBOneTxRx
	spiBBZeroTxRx:
	    bcf SPI_PORT,SPI_MOSI
	    goto spiBBtxrxClock
	spiBBOneTxRx:
	    bsf SPI_PORT,SPI_MOSI
	    nop
	    nop
	spiBBtxrxClock:
	    call spiSCKtoogle
	    call spiSCKtoogle
	    btfsc SPI_PORT,SPI_MISO
	    goto spiBBOneRxTx
	    spiBBZeroRxTx:
		bcf CARRY
		goto spiBBrxtxSave
	    spiBBOneRxTx:
		bsf CARRY
		nop
		nop
	    spiBBrxtxSave:
		rlf SPIRXREG,F
		decfsz SPIBBCOUNT,F
		goto spiBBloopTxRx
		return
;</editor-fold>
