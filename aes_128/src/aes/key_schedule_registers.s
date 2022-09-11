;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Author 	: stales
;; Date   	: 2022-03-11 19:03:21
;; Filename	: key_schedule_registers
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

format ELF64

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;				EXTERNAL
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

extrn key_expansion_128

public key_schedule_registers

section '.text' executable

; generate 10 key round because we are on aes 128 bits
; each key has been generated with round constant

key_schedule_registers:
	cmp rsi, 0x10
	jne _key_schedule_error ; check len of key
	movdqu xmm1, xword [rdi] ; store key in xmm1 register

	; 1

	aeskeygenassist xmm2, xmm1, 0x1
	call key_expansion_128 ; output in xmm1
	movdqu xmm4, xmm1

	; 2

	aeskeygenassist xmm2, xmm1, 0x2
	call key_expansion_128
	movdqu xmm5, xmm1

	; 3

	aeskeygenassist xmm2, xmm1, 0x4
	call key_expansion_128
	movdqu xmm6, xmm1

	; 4

	aeskeygenassist xmm2, xmm1, 0x8
	call key_expansion_128
	movdqu xmm7, xmm1

	; 5

	aeskeygenassist xmm2, xmm1, 0x10
	call key_expansion_128
	movdqu xmm8, xmm1

	; 6

	aeskeygenassist xmm2, xmm1, 0x20
	call key_expansion_128
	movdqu xmm9, xmm1

	; 7

	aeskeygenassist xmm2, xmm1, 0x40
	call key_expansion_128
	movdqu xmm10, xmm1

	; 8

	aeskeygenassist xmm2, xmm1, 0x80
	call key_expansion_128
	movdqu xmm11, xmm1

	; 9

	aeskeygenassist xmm2, xmm1, 0x1b
	call key_expansion_128
	movdqu xmm12, xmm1

	; 10
	
	aeskeygenassist xmm2, xmm1, 0x36
	call key_expansion_128
	movdqu xmm13, xmm1
	xor rax, rax
	ret

_key_schedule_error:
	mov eax, 0x1
	ret
