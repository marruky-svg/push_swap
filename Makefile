NAME		=	push_swap
CC			=	cc 
CFLAGS		=	-Wall -Wextra -Werror

LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a

INCLUDES	=	-I. -I$(LIBFT_DIR)

SRCS	=	disorder.c \
			dispatch.c \
			main.c \
			ops_rev_rotate.c \
			ops_rotate.c \
			ops_swap_push.c \
			parse_args.c \
			parse_flags.c \
			primitives.c \
			record.c
		
OBJS	=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

FORCE:

.PHONY: all clean fclean re FORCE