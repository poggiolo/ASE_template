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
				
				add r6, r0, r1, LSL #2 			; get loop stop condition
				
loop			ldr r7, [r0], #4				; load first vett val (post increment r0)
				ldr r8, [r0], #4				; load second vett val (post increment r0)
				
				; logic here
				
				subs r10, r0, r6				; exit condition
				bne loop
				
exit			; put return value into r0
				; mov r0, #0
				
				pop {r4-r8, r10-r11, pc}
                endp

				end
					
;******************************************************************************
;**                            End Of File
;******************************************************************************
