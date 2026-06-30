#ifndef MCP4822_INC
    #define MCP4822_INC
    
    #include"spiBitBang.inc"
    global MCP_PORT,MCP_TRIS,MCP_LDAC,MCP_REG 

    ;<editor-fold defaultstate="collapsed" desc="defines">
	#define DAC_A   'A'
	#define DAC_B   'B'
	#define X1	1
	#define X2	2
    ;</editor-fold>
    
    ;<editor-fold defaultstate="collapsed" desc="mcpIni Puerto,MOSI,SCK,LDAC">
    mcpIni macro puerto,MOSI,SCK,LDAC
	messg "biblioteca mcp4822 www.mgv3d.com"
	spiTxIni puerto,MOSI,SCK,mode0
	MCP_PORT equ PORT&puerto
	MCP_TRIS equ TRIS&puerto
	MCP_LDAC equ LDAC
	banksel MCP_TRIS
	bcf MCP_TRIS,MCP_LDAC
	banksel MCP_PORT
	bsf MCP_PORT,MCP_LDAC
    endm
    ;</editor-fold>
    ;<editor-fold defaultstate="collapsed" desc="mcpWriteL DAC,Gain,Literal">
    mcpWriteL macro DAC,gain,literal
	if (literal>4095)|(literal<0)
	    error "literal invalida"
	endif
	movlw low(literal)
	movwf MCP_REG
	movlw high(literal)
	movwf MCP_REG+1
	if DAC='A'
	    bcf MCP_REG+1,7
	endif
	if DAC='B'
	    bsf MCP_REG+1,7
	endif
	if gain=1
	    bsf MCP_REG+1,5
	else 
	    bcf MCP_REG+1,5
	endif
	bsf MCP_REG+1,4
	spiTx MCP_REG+1
	spiTx MCP_REG
    endm
    ;</editor-fold>
    ;<editor-fold defaultstate="collapsed" desc="mcpWriteF DAC,Gain,RegH,RegL">
    mcpWriteF macro DAC,gain,MCP_REG_HIGH,MCP_REG_LOW
	movf MCP_REG_HIGH,W
	movwf MCP_REG+1
	movf MCP_REG_LOW,W
	movwf MCP_REG
	movlw 00001111B
	andwf MCP_REG+1,F
	if DAC='A'
	    bcf MCP_REG+1,7
	endif
	if DAC='B'
	    bsf MCP_REG+1,7
	endif
	if gain=1
	    bsf MCP_REG+1,5
	else 
	    bcf MCP_REG+1,5
	endif
	bsf MCP_REG+1,4
	spiTx MCP_REG+1
	spiTx MCP_REG
    endm
    ;</editor-fold>
    ;<editor-fold defaultstate="collapsed" desc="mcpPush">
    mcpPush macro
	bcf MCP_PORT,MCP_LDAC
	bsf MCP_PORT,MCP_LDAC
    endm
    ;</editor-fold>

#endif


