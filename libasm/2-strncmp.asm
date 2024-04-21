section .text
global asm_strncmp


asm_strncmp:
	; Configure stack frame
	push rbp                          ; Save the rbp value on the stack
	mov rbp, rsp                      ; Set rbp as the current frame pointer
	mov rcx, 0                        ; Initialize rcx (counter) to zero

compare:
	xor rax, rax                      ; Clear rax (will be used for the result)
	xor rbx, rbx                      ; Clear rbx (will be used to compare bytes)

	cmp rcx, rdx                      ; Compare counter to length n
	je end_comparison                 ; If they are equal, end the comparison

	mov al, byte [rdi + rcx]          ; Load the byte of s1 into AL
	mov bl, byte [rsi + rcx]          ; Load the byte of s2 into BL

	cmp al, bl                        ; Compare the bytes

	je equal_chars                    ; If they are equal, jump to the equal tag
	jl less_chars                     ; If s1 is less than s2, jump to less_chars
	jg greater_chars                  ; If s1 is greater than s2, jump to greater_chars

equal_chars:
	; The characters are the same, check if it is a null character
	cmp al, 0                         ; Checks if it is a null character
	je end_comparison                 ; If so, end the comparison
	inc rcx                           ; Increase the counter
	jmp compare                       ; Jump back to compare to compare next bytes

less_chars:
	; Return a negative value (s1 < s2)
	mov rax, -1                       ; Set the result to -1 (s1 < s2)
	jmp end_comparison                ; Jump to end the comparison

greater_chars:
	; Return a positive value (s1 > s2)
	mov rax, 1                        ; Set the result to 1 (s1 > s2)
	jmp end_comparison                ; Jump to end the comparison

end_comparison:
	; Clear stack frame
	mov rsp, rbp                      ; Restore rsp to the original value
	pop rbp                           ; Restore rbp from stack
	ret                               ; Return with the result in rax
