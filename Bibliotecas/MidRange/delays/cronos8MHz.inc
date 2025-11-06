psect udata_bank0
DCounter1: DS 1
DCounter2: DS 1
DCounter3: DS 1
DCounter4: DS 1
    
psect code
;Retardos en Minutos
delay1h:
delay60m:
    MOVLW 0X17
    MOVWF DCounter1
    MOVLW 0X9b
    MOVWF DCounter2
    MOVLW 0Xae
    MOVWF DCounter3
    MOVLW 0X8f
    MOVWF DCounter4
    LOOP60m:
	DECFSZ DCounter1, 1
	GOTO LOOP60m
	DECFSZ DCounter2, 1
	GOTO LOOP60m
	DECFSZ DCounter3, 1
	GOTO LOOP60m
	DECFSZ DCounter4, 1
	GOTO LOOP60m
    RETURN

delay30m:
    MOVLW 0X09
    MOVWF DCounter1
    MOVLW 0Xce
    MOVWF DCounter2
    MOVLW 0X57
    MOVWF DCounter3
    MOVLW 0X48
    MOVWF DCounter4
    LOOP30m:
	DECFSZ DCounter1, 1
	GOTO LOOP30m
	DECFSZ DCounter2, 1
	GOTO LOOP30m
	DECFSZ DCounter3, 1
	GOTO LOOP30m
	DECFSZ DCounter4, 1
	GOTO LOOP30m
    RETURN

delay15m:
    MOVLW 0X82
    MOVWF DCounter1
    MOVLW 0X67
    MOVWF DCounter2
    MOVLW 0Xac
    MOVWF DCounter3
    MOVLW 0X24
    MOVWF DCounter4
    LOOP15m:
	DECFSZ DCounter1, 1
	GOTO LOOP15m
	DECFSZ DCounter2, 1
	GOTO LOOP15m
	DECFSZ DCounter3, 1
	GOTO LOOP15m
	DECFSZ DCounter4, 1
	GOTO LOOP15m
	NOP
    RETURN
    
delay10m:
    MOVLW 0Xab
    MOVWF DCounter1
    MOVLW 0X90
    MOVWF DCounter2
    MOVLW 0Xc8
    MOVWF DCounter3
    MOVLW 0X18
    MOVWF DCounter4
    LOOP10m:
	DECFSZ DCounter1, 1
	GOTO LOOP10m
	DECFSZ DCounter2, 1
	GOTO LOOP10m
	DECFSZ DCounter3, 1
	GOTO LOOP10m
	DECFSZ DCounter4, 1
	GOTO LOOP10m
    RETURN
    
delay5m:
    MOVLW 0Xd3
    MOVWF DCounter1
    MOVLW 0Xcd
    MOVWF DCounter2
    MOVLW 0Xe4
    MOVWF DCounter3
    MOVLW 0X0c
    MOVWF DCounter4
    LOOP5m:
	DECFSZ DCounter1, 1
	GOTO LOOP5m
	DECFSZ DCounter2, 1
	GOTO LOOP5m
	DECFSZ DCounter3, 1
	GOTO LOOP5m
	DECFSZ DCounter4, 1
	GOTO LOOP5m
    NOP
    NOP
    RETURN

delay1m:
    MOVLW 0X8d
    MOVWF DCounter1
    MOVLW 0Xc3
    MOVWF DCounter2
    MOVLW 0X61
    MOVWF DCounter3
    MOVLW 0X03
    MOVWF DCounter4
    LOOP1m:
	DECFSZ DCounter1, 1
	GOTO LOOP1m
	DECFSZ DCounter2, 1
	GOTO LOOP1m
	DECFSZ DCounter3, 1
	GOTO LOOP1m
	DECFSZ DCounter4, 1
	GOTO LOOP1m
    RETURN

;Retardos en Segundos
delay30s:
    MOVLW 0X43
    MOVWF DCounter1
    MOVLW 0X62
    MOVWF DCounter2
    MOVLW 0X31
    MOVWF DCounter3
    MOVLW 0X02
    MOVWF DCounter4
    LOOP30s:
	DECFSZ DCounter1, 1
	GOTO LOOP30s
	DECFSZ DCounter2, 1
	GOTO LOOP30s
	DECFSZ DCounter3, 1
	GOTO LOOP30s
	DECFSZ DCounter4, 1
	GOTO LOOP30s
	NOP
	NOP
    RETURN


delay10s:
    MOVLW 0Xbf
    MOVWF DCounter1
    MOVLW 0X76
    MOVWF DCounter2
    MOVLW 0X66
    MOVWF DCounter3
    LOOP10s:
	DECFSZ DCounter1, 1
	GOTO LOOP10s
	DECFSZ DCounter2, 1
	GOTO LOOP10s
	DECFSZ DCounter3, 1
	GOTO LOOP10s
    NOP
    NOP
    RETURN
    
delay5s:
    MOVLW 0Xde
    MOVWF DCounter1
    MOVLW 0Xbb
    MOVWF DCounter2
    MOVLW 0X33
    MOVWF DCounter3
    LOOP5s:
	DECFSZ DCounter1, 1
	GOTO LOOP5s
	DECFSZ DCounter2, 1
	GOTO LOOP5s
	DECFSZ DCounter3, 1
	GOTO LOOP5s
    NOP
    RETURN

delay1s:
    MOVLW 0X5c
    MOVWF DCounter1
    MOVLW 0X26
    MOVWF DCounter2
    MOVLW 0X0b
    MOVWF DCounter3
    LOOP1s:
	DECFSZ DCounter1, 1
	GOTO LOOP1s
	DECFSZ DCounter2, 1
	GOTO LOOP1s
	DECFSZ DCounter3, 1
	GOTO LOOP1s
    NOP
    RETURN

;Retardos en mili Segundos
delay500ms:
    MOVLW 0Xac
    MOVWF DCounter1
    MOVLW 0X13
    MOVWF DCounter2
    MOVLW 0X06
    MOVWF DCounter3
    LOOP500ms:
	DECFSZ DCounter1, 1
	GOTO LOOP500ms
	DECFSZ DCounter2, 1
	GOTO LOOP500ms
	DECFSZ DCounter3, 1
	GOTO LOOP500ms
    NOP
    RETURN

delay100ms:
    MOVLW 0Xb9
    MOVWF DCounter1
    MOVLW 0X04
    MOVWF DCounter2
    MOVLW 0X02
    MOVWF DCounter3
    LOOP100ms:
	DECFSZ DCounter1, 1
	GOTO LOOP100ms
	DECFSZ DCounter2, 1
	GOTO LOOP100ms
	DECFSZ DCounter3, 1
	GOTO LOOP100ms
    RETURN

delay50ms:
    MOVLW 0Xdc
    MOVWF DCounter1
    MOVLW 0X82
    MOVWF DCounter2
    LOOP50ms:
	DECFSZ DCounter1, 1
	GOTO LOOP50ms
	DECFSZ DCounter2, 1
	GOTO LOOP50ms
    NOP
    RETURN
    
delay10ms:
    MOVLW 0Xf7
    MOVWF DCounter1
    MOVLW 0X1a
    MOVWF DCounter2
    LOOP10ms:
	DECFSZ DCounter1, 1
	GOTO LOOP10ms
	DECFSZ DCounter2, 1
	GOTO LOOP10ms
    RETURN

delay5ms:    
    MOVLW 0Xfa
    MOVWF DCounter1
    MOVLW 0X0d
    MOVWF DCounter2
    LOOP5ms:
	DECFSZ DCounter1, 1
	GOTO LOOP5ms
	DECFSZ DCounter2, 1
	GOTO LOOP5ms
    NOP
    RETURN
    
delay1ms:
    MOVLW 0X96
    MOVWF DCounter1
    MOVLW 0X03
    MOVWF DCounter2
    LOOP1ms:
	DECFSZ DCounter1, 1
	GOTO LOOP1ms
	DECFSZ DCounter2, 1
	GOTO LOOP1ms
    NOP
    RETURN
