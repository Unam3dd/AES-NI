NAME = aeslib.a
CC = gcc
C_SRC = $(wildcard src/**/*.c)
C_OBJ = $(C_SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -Iincludes -maes
UNIT_SRC = $(wildcard test/*.c)
UNIT_OBJ = $(UNIT_SRC:.c=)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -O3 -m64 -c $< -o $@

$(NAME): $(FASM_OBJ) $(C_OBJ)
	ar rcs $(NAME) $(C_OBJ)

clean:
	rm -rf $(C_OBJ)

unit:
	$(CC) -Iincludes test/hex_encoder.c aeslib.a -O3 -o test/hex_encoder 
	$(CC) -Iincludes test/utils.c aeslib.a -O3 -o test/utils
	$(CC) -Iincludes test/hex_decoder.c aeslib.a -O3 -o test/hex_decoder
	$(CC) -Iincludes test/base64_encoder.c aeslib.a -O3 -o test/base64_encoder
	$(CC) -Iincludes test/base64_decoder.c aeslib.a -O3 -o test/base64_decoder
	$(CC) -Iincludes test/aes_ecb_test.c aeslib.a -O3 -o test/aes_ecb_test

unit_clean: $(UNIT_OBJ)
	rm -rf $(UNIT_OBJ)
	
fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
