;
; DA2A(part1_avr).asm
;
; Created: 3/4/2019 4:37:44 PM
; Author : barrc1
;

.CSEG
.org	0x0000
 
 SBI DDRB, 5 ;Make sure PB5 stays turned off
 SBI PORTB, 5
 SBI DDRB, 2 ;Sets PB2 as an output
 LDI R16,0x04 ;Represents PB2
 LDI R17,0x00 ;Used to toggle LED
 LDI R20,5 ;set clock prescaler to 1024
 STS TCCR1B,R20 ;Clock prescaler now set to 1024

begin:
 LDI R20,0x00 ;Used to reset counter
 STS TCNT1H,R20 ;
 STS TCNT1L,R20 ;Counter high and low reset to 0
 SBI PORTB, 2 ; Turns on PB2
 RCALL delay ;calling timer to wait for 0.435 sec turned on
 LDI R20,0x00 ;Used to reset counter
 STS TCNT1H,R20
 STS TCNT1L,R20 
 CBI PORTB, 2 ; Turns off PB2
 RCALL delay2 ;calling timer to wait for 0.29 sec turned off
 RJMP begin ;repeat main loop

delay:
 LDS R29, TCNT1H ;Loads upper bits into register R29
 LDS R28, TCNT1L ;Loads lower bits into register R28
 CPI R28,0x8C ;comparing lower 8 bits of timer to 0x8C
 BRSH body ;if lower bits are the same or higher to 0x8C, jump to body and start counting there
 RJMP delay ;else, keep checking lower bits

body:
 CPI R29,0x1A ;comparing upper 8 bits of timer to 0x1A
 BRLT delay ;If lower, then go back and check the lower bits
 RET ;When the timer is over, return to turn off the lead


delay2:
 LDS R29, TCNT1H ;Loads upper bits into register R29
 LDS R28, TCNT1L ;Loads lower bits into register R28
 CPI R28,0xB2 ;comparing lower 8 bits of timer to 0xB2
 BRSH body2 ;if lower bits are the same or higher to 0xB2, jump to body and start counting there
 RJMP delay2 ;else, keep checking lower bits

body2:
 CPI R29,0x11 ;comparing upper 8 bits of timer to 0x11
 BRLT delay2 ;If lower, then go back and check the lower bits
 RET ;When the timer is over, return to turn off the lead