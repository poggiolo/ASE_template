				area    |.text|, code, readonly
					
; 	C-code of the ASM function
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;

; convenient register renaming
name0 RN 0
name1 RN 1
name2 RN 2
name3 RN 3
name4 RN 4
name5 RN 5
name6 RN 6
name7 RN 7
name8 RN 8
name9 RN 9

; NB append S to any instruction in order to update the flags

sopra_la_media			proc
                export  sopra_la_media
				
				; r12: value of the stack before the push
				; mov  r12, sp
				
				push {r4-r8, r10-r11, lr}
				
				;	5th paramenter
				;	ldr r4, [r12]
				;	6th parameter
				;	ldr r5, [r12, #4]
				
				mov r4, #0 ; r4: avg
				mov r8, #0 ; r8: output value (to be copied in r0)
				mov r5, r1 ; r5: N
				
				subs r1, r1, #1 ; r1: counter
				blt exit

avgloop			ldrb r7, [r0, r1]		; load first vett val
										; if VETT is an array of char (bytes)
										;  - change ldr -> ldrb, remove LSL #2
										; if VETT is an array of int16
										;  - change ldr -> ldrh, change LSL #2 -> LSL #1
				
				add r4, r4, r7					; mean_counter += VETT[i]
				

				subs r1, r1, #1					; exit condition
				bge avgloop						; for(i>=0;i--)
				
				sdiv r4, r4, r5 				; avg calculation
				
				mov r1, r5 						; reset counter to N
				
sumloop			ldrb r7, [r0, r1] 				; load vett[i]

				subs r6, r7, r4 				; r6= VETT[i] - avg
				ble endloop
				add r8, #1 						; increment output counter
				
endloop			subs r1, #1
				bge sumloop
				
				mov r0, r8 						; return output counter
								
exit			; put return value into r0
				; mov r0, #0
				
				pop {r4-r8, r10-r11, pc}
                endp

				end
					
;******************************************************************************
;**                            End Of File
;******************************************************************************
