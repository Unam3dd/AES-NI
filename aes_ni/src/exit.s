;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Author 	: stales
;; Date   	: 2022-24-05 18:24:07
;; Filename	: exit
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

format ELF64

public exit

section '.text' executable

exit:
	mov rax, 0x3c
	syscall
