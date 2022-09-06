;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Author 	: stales
;; Date   	: 2022-22-05 18:22:50
;; Filename	: main
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

format ELF64

public _start

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;				INCLUDES
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

extrn exit
extrn printf

section '.data' writeable
	usage db "usage : %s <message> <key> --help", 0xa, 0x0
	aes_ni_error db "Error : your CPU does not support AES-NI extension :(", 0xa, 0x0

section '.text' executable

_start:
	mov edx, dword [rsp]
	xor edx, 0x3
	jnz _error_fmt

_check_support_aes_ni:
	xor eax, eax
	or eax, 0x1
	cpuid
	and ecx, 0x2000000
	xor ecx, 0x2000000
	jnz _error_aes_ni

_exit_success:
	xor rdi, rdi
	jmp exit

_error_aes_ni:
	mov rdi, aes_ni_error
	xor rsi, rsi
	xor al, al
	call printf
	mov rdi, 0x1
	jmp exit

_error_fmt:
	mov rdi, usage
	mov rsi, qword [rsp + 0x8]
	xor al, al
	call printf
	mov rdi, 0x1
	jmp exit
