; LED Blink Example program GPIO 4

.org 0

    ljmp 0x1000    ; Jump Startup

.org 3
     reti   

.org 0xB
     reti

.org 0x13

     reti
.org 0x1B
      reti

.org 0x23
      reti
.org 0x2b
     reti

.org 0x1000

startup:

    mov    dptr,#0X2038 ; General purpose IO output enable
    
    movx    a , @dptr
    orl     a, #0b00010000 
    movx    @dptr, a	  ; Set GPIO as Output  

loop:

    mov dptr,#0X2030 ; Set output
    movx    a , @dptr 
    orl a, #0b00010000 
    movx    @dptr,a
    
    acall	delay
    mov dptr,#0X2030
    movx    a , @dptr
    anl a, #0b11101111
    movx    @dptr,a
    
    acall   delay
    sjmp	loop

exit:	ljmp	0



	;delay for a number of x ms
delay:
        mov     r2, #0x10
dly4:	mov	r0, #0xFF
dly2:	mov	r1, #0xFF
dly3:	nop
	nop
	nop			;6 NOPs + DJNZ 
	nop
	nop
	djnz	r1, dly3	;repeat 
	djnz	r0, dly2	;repeat for specified #
	djnz	r2, dly4	;repeat for specified #
	ret

