NAME = aes_ni
SRCS = $(wildcard src/*.s)
OBJS = $(SRCS:.s=.o)
FASM = fasm

all: $(NAME)

%.o: %.s
	$(FASM) $<

$(NAME): $(OBJS)
	ld $(OBJS) -o $(NAME) --dynamic-linker /lib/x86_64-linux-gnu/ld-linux-x86-64.so.2 -lc

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
