;
; DA2A(part2_avr).asm
;
; Created: 3/4/2019 6:42:16 PM
; Author : barrc1
;


; Replace with your application code
.CSEG
.org	0x0000
 
 LDI R16, 0xFF ;Sets PB5 as output
 OUT DDRB, R16
 CBI DDRC, 2 ;Sets PC2 as input
 LDI R20,5 ;set clock prescaler to 1024
 STS TCCR1B, R20 ;send prescaler
 OUT PORTB, R16

LOOP:
 ;Loops back here when nothing is pressed
 SBI PORTB, 2 ;Keeps LED turned off
 SBIC PINC, 2 ;Skips next instruction if pushbutton is pressed
 RJMP LOOP ;If pushbutton isn't pressed, continues through this loop

 ;Goes here once button is pressed
 LDI R18, 0b1110_00 ;Turns on LED
 OUT PORTB, R18
 LDI R20, 0 ;Clears counter
 STS TCNT1H, R20
 STS TCNT1L, R20
 RCALL DELAY ;Delay for 1.25 seconds
 RJMP LOOP ;Loops back until pushbutton is pressed again

delay:
 LDS R29, TCNT1H ;Loads upper bits into register R29
 LDS R28, TCNT1L ;Loads lower bits into register R28
 CPI R28,0x4A ;comparing lower 8 bits of timer to 0x8C
 BRSH body ;if lower bits are the same or higher to 0x8C, jump to body and start counting there
 RJMP delay ;else, keep checking lower bits

body:
 CPI R29,0x4C ;comparing upper 8 bits of timer to 0x1A
 BRLT delay ;If lower, then go back and check the lower bits
 RET ;When the timer is over, return to turn off the lead