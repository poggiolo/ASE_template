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

nome_molto_lungo_e_complicato			proc
                export  nome_molto_lungo_e_complicato
				
				; r12: value of the stack before the push
				; mov  r12, sp
				
				push {r4-r8, r10-r11, lr}
				
				;	5th paramenter
				;	ldr r4, [r12]
				;	6th parameter
				;	ldr r5, [r12, #4]
				
				subs r1, r1, #1
				blt exit

loop			ldr r7, [r0, r1, LSL #2]		; load first vett val
												; if VETT is an array of char (bytes)
												;  - change ldr -> ldrb, remove LSL #2
				
				; subs r1, #1					; update r1
				; blt exit						; if not sure N is even
				
				; ldr r8, [r0, r1, LSL #2]		; load second vett val
												; if VETT is an array of char (bytes)
												;  - change ldr -> ldrb, remove LSL #2

				; logic here
				
				subs r1, r1, #1					; exit condition
				bge loop
				
exit			; put return value into r0
				; mov r0, #0
				
				pop {r4-r8, r10-r11, pc}
                endp

				end
					
;******************************************************************************
;**                            End Of File
;******************************************************************************
