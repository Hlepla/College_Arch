.org 0x00 

jmp entry

entry:

	ldi r16,255 ; load the value 255 into register 16
	ldi r17,0 ; load the value 0 into register 17
	ldi r18,-1 ; use -1 to decrement later

	out 0x04, r16 ; we must enable write to the ouput

	jmp LedHigh ; go to label for light "on"


DelayLoop:	

	ldi r20 , 255 
	ldi r21 , 255
	ldi r22 , 70 ; This value effects the speed of the blinking

	Loop: ; come to here for the decrement loop

	add r20, r18 ; decrement r20 by 1

	brbc 1, Loop ; If register 20 is not 0, loop
	
	add r21, r18 ; decrement r21 by 1

	nop ; wait a instruction, no operation
	
	brbc 1, Loop ; If register 21 is not 0, loop

	add r22, r18 ; decrement r22 by 1

	nop ; wait a instruction, no operation

	brbc 1, Loop ; If r22 is not 0, loop

	ret ; returns when r17 is 0

	jmp entry ; start back to the top



 LedHigh:
	
	out 0x05, r16 ; write to port B with bits being 1 
	call DelayLoop ; go to label for Delay
	jmp LedLow ; go to off label
	
	
LedLow:
	out 0x05, r17 ; write to port B with bit being 0
	call DelayLoop ; go to label for Delay 
	jmp LedHigh ; go to on label


