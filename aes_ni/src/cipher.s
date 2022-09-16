;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Author 	: stales
;; Date   	: 2022-24-07 11:24:50
;; Filename	: cipher
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

format ELF64

public cipher

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;				INCLUDES
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

extrn key_expansion_128

section '.text' executable

; aes_cipher_128(char *data, char *key, size_t len);

cipher:
	; move key in to 128 bits register
	pxor xmm0, xmm0
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

	movdqu xmm1, [rsi]
	movdqu xmm0, [rsi]

	; Expand key with AES Round constant
	; Create 10 Rounds key
	aeskeygenassist xmm2, xmm1, 0x1
	call key_expansion_128
	movdqu xmm4, xmm1
	aeskeygenassist xmm2, xmm1, 0x2
	call key_expansion_128
	movdqu xmm5, xmm1
	aeskeygenassist xmm2, xmm1, 0x4
	call key_expansion_128
	movdqu xmm6, xmm1
	aeskeygenassist xmm2, xmm1, 0x8
	call key_expansion_128
	movdqu xmm7, xmm1
	aeskeygenassist xmm2, xmm1, 0x10
	call key_expansion_128
	movdqu xmm8, xmm1
	aeskeygenassist xmm2, xmm1, 0x20
	call key_expansion_128
	movdqu xmm9, xmm1
	aeskeygenassist xmm2, xmm1, 0x40
	call key_expansion_128
	movdqu xmm10, xmm1
	aeskeygenassist xmm2, xmm1, 0x80
	call key_expansion_128
	movdqu xmm11, xmm1
	aeskeygenassist xmm2, xmm1, 0x1b
	call key_expansion_128
	movdqu xmm12, xmm1
	aeskeygenassist xmm2, xmm1, 0x36
	call key_expansion_128
	movdqu xmm13, xmm1
	
	movdqu xmm15, [rdi]
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
	ret
