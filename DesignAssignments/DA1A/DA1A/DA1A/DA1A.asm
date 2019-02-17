;
; DA1A.asm
;
; Created: 2/7/2019 4:39:46 PM
; Author : Chris
;


; Replace with your application code

.EQU multiplicand = 0xFFFF		; multiplicand variable declaration
.EQU multiplier = 0xFF			; multiplier variabledeclaration

initialize:						; INITIALIZING THE MULTIPLICAND AND MULTIPLIER
 ldi r24, low(multiplicand)		; loading in low value multiplicand
 ldi r25, high(multiplicand)	; loading in high value multiplicand
 ldi r23, 0						; 0 for comparison when decrementing multiplier
 ldi r22, multiplier			; loading in multiplier

loop:							; LOOP TO "MULTIPLY"
 add r18, r24					; add the low value of the multiplicand
 adc r19, r25					; add the high value of the multiplicand and the carry
 adc r20, r23					; add the carry into the new 3rd register
 dec r22						; decrement the multiplier until it reaches 0
 cp  r22, r23					; compare the multiplier with 0
 brne loop						; if the multiplier reaches 0, the program is finished
done:jmp done					; left 'jmp done' for debugging purposes