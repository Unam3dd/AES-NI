;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Author 	: stales
;; Date   	: 2022-46-16 14:46:57
;; Filename	: aes_ni
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

format ELF64

public _start

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;		EXTERNAL FUNCTIONS
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

extrn printf

section '.bss' writeable
	buf rb 0x100									; Our buffer where we put our data ciphered

section '.data' writeable
	iv db "hkicupyeszbfqrwx", 0						; 16 bytes for IV because Cipher mode use an IV here is CBC
	key db "vilzqkcxahfyedwr", 0					; 16 bytes for the key
	message db "hello ceci easyy", 0					; 16 bytes message

section '.text' executable

; Key expansion algorithm used with KeyScheduler Algorithm

key_expansions_128:
	pshufd xmm2, xmm1, 0xff
	vpslldq xmm3, xmm1, 0x4
	pxor xmm1, xmm3
	vpslldq xmm3, xmm1, 0x4
	pxor xmm1, xmm3
	vpslldq xmm3, xmm1, 0x4
	pxor xmm1, xmm3
	pxor xmm1, xmm2
	ret

xor_xmm_registers:
	pxor xmm0, xmm0		; xor all xmm registers for safety
	pxor xmm1, xmm1
	pxor xmm2, xmm2
	pxor xmm3, xmm3
	pxor xmm4, xmm4
	pxor xmm5, xmm5
	pxor xmm6, xmm6
	pxor xmm7, xmm7
	pxor xmm8, xmm8
	pxor xmm9, xmm9
	pxor xmm10, xmm10
	pxor xmm11, xmm11
	pxor xmm12, xmm12
	pxor xmm13, xmm13
	pxor xmm14, xmm14
	pxor xmm15, xmm15
	ret


_start:
	; reset all xmm registers

	call xor_xmm_registers

	; generate key round with round constant

	movdqu xmm1, xword [key]
	movdqu xmm0, xword [key]

	aeskeygenassist xmm2, xmm1, 0x1
	call key_expansions_128
	movdqu xmm4, xmm1			; Key[0]

	aeskeygenassist xmm2, xmm1, 0x2
	call key_expansions_128
	movdqu xmm5, xmm1			; Key[1]

	aeskeygenassist xmm2, xmm1, 0x4
	call key_expansions_128
	movdqu xmm6, xmm1			; Key[2]

	aeskeygenassist xmm2, xmm1, 0x8
	call key_expansions_128
	movdqu xmm7, xmm1			; Key[3]

	aeskeygenassist xmm2, xmm1, 0x10
	call key_expansions_128
	movdqu xmm8, xmm1			; Key[4]

	aeskeygenassist	xmm2, xmm1, 0x20
	call key_expansions_128
	movdqu xmm9, xmm1			; Key[5]

	aeskeygenassist xmm2, xmm1, 0x40
	call key_expansions_128
	movdqu xmm10, xmm1			; Key[6]

	aeskeygenassist xmm2, xmm1, 0x80
	call key_expansions_128
	movdqu xmm11, xmm1			; Key[7]

	aeskeygenassist xmm2, xmm1, 0x1b
	call key_expansions_128
	movdqu xmm12, xmm1			; Key[8]

	aeskeygenassist xmm2, xmm1, 0x36
	call key_expansions_128
	movdqu xmm13, xmm1			; Key[9] Last round key in AES-128 bits

	movdqu xmm15, xword [message]
	pxor xmm15, xmm0
	aesenc xmm15, xmm4
	aesenc xmm15, xmm5
	aesenc xmm15, xmm6
	aesenc xmm15, xmm7
	aesenc xmm15, xmm8
	aesenc xmm15, xmm9
	aesenc xmm15, xmm10
	aesenc xmm15, xmm11
	aesenc xmm15, xmm12
	aesenclast xmm15, xmm13
	movdqu xmm1, xmm15

_exit:
	mov rax, 0x3c
	xor rdi, rdi
	syscall
