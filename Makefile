NAME = ft_ping

SUBDIR = libft

HEADERS = ping.h

CC = cc

SRCS =	src/main.c \
		src/packet.c \
		src/utils.c \
		src/validation.c \
		src/packet_utils.c \
		src/packet_utils2.c \
		src/utils2.c

CFLAGS = -Wall -Wextra -Werror -g3 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C src/libft/
	sudo $(CC) $(CFLAGS) $(OBJS) src/libft/libft.a -o $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C src/libft/

fclean:	clean
	rm -f $(NAME)
	rm -rf src/libft/libft.a

re: fclean all

.PHONY: clean re fclean