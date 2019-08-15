;SECTION	.DATA
;
;    mes	db	'Hello, NASM!', 0xa, 0	; null terminated string to be printed
;    len	equ	$ - mes			; length of string
    
SECTION .TEXT    
    GLOBAL asm_say_hi

;    mesg	db	'Hello, NASM!', 0xa, 0	; null terminated string to be printed
;    len	equ	$ - mesg			; length of string    
    
asm_say_hi:
;	mov	edx, len	; string length
;	mov	ecx, mesg	; string to write
;	mov	ebx, 1	; file descriptor (stdout)
;	mov	eax, 4	; syscall number (sys_write)
;	int	0x80	; call kernel

	mov rax, 32
    ret
    
	
