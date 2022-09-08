NAME = aeslib.a
FASM = fasm
CC = gcc
FASM_SRC = $(wildcard src/**/*.s)
C_SRC = $(wildcard src/**/*.c)
FASM_OBJ = $(FASM_SRC:.s=.o)
C_OBJ = $(C_SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -Iincludes

all: $(NAME)

%.o: %.s
	$(FASM) $< $@

%.o: %.c
	$(CC) $(CFLAGS) -O3 -m64 -c $< -o $@

$(NAME): $(FASM_OBJ) $(C_OBJ)
	ar rcs $(NAME) $(C_OBJ) $(FASM_OBJ)

clean:
	rm -rf $(C_OBJ)
	rm -rf $(FASM_OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
