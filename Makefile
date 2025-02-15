NAME = ft_ping

SUBDIR = libft

HEADERS = ping.h

CC = cc

SRC =	main.c \
		packet.c \
		utils.c \
		validation.c \

all: $(NAME)

$(NAME): $(SRC) $(HEADERS)
	$(CC) -o $(NAME) $(SRC)

