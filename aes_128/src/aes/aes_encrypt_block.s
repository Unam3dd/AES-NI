;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Author 	: stales
;; Date   	: 2022-57-11 22:57:59
;; Filename	: aes_encrypt_block
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

format ELF64

public aes_encrypt_block

section '.text' executable

aes_encrypt_block:
	cmp rdi, 0x0
	jz aes_encrypt_block_failure
	cmp rsi, 0x0
	jz aes_encrypt_block_failure


	movdqu xmm15, xword [rdi]
	movdqu xmm0, xword [rsi]

	pxor xmm15, xmm0
	aesenc xmm15, xmm4	; Round 1
	aesenc xmm15, xmm5	; Round 2
	aesenc xmm15, xmm6	; Round 3 etc..
	aesenc xmm15, xmm7
	aesenc xmm15, xmm8
	aesenc xmm15, xmm9
	aesenc xmm15, xmm10
	aesenc xmm15, xmm11
	aesenc xmm15, xmm12
	aesenclast xmm15, xmm13 ; last round without mix columns
	movdqu xmm1, xmm15	; return block data ciphered
	ret

aes_encrypt_block_failure:
	pxor xmm1, xmm1
	ret
