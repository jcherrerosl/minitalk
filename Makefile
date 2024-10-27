CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF_DIR = libft/ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

NAME_SERVER = server
NAME_CLIENT = client

SRCS_CLIENT = client.c utils_bin.c utils.c 
SRCS_SERVER = server.c  utils_bin.c utils.c

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

all: $(LIBFT) $(PRINTF) $(NAME_SERVER) $(NAME_CLIENT)

$(PRINTF):
	make -C $(PRINTF_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(NAME_SERVER) -L $(LIBFT_DIR) -lft -L $(PRINTF_DIR) -lftprintf

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(NAME_CLIENT) -L $(LIBFT_DIR) -lft -L $(PRINTF_DIR) -lftprintf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(PRINTF_DIR)
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(PRINTF_DIR)
	rm -f $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all

.PHONY: all clean fclean re
