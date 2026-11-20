# ================================ PROGRAMA ==================================
NAME		=	push_swap
BONUS_NAME	=	checker

# =============================== COMPILADOR =================================
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

# ================================== LIBFT ===================================
LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a

# ================================ INCLUDES ==================================
INCLUDES	=	-I. -I$(LIBFT_DIR)

# ================================ FONTES ====================================
# Ficheiros usados pelos DOIS programas (push_swap e checker)
SHARED		=	disorder.c \
				errors.c \
				ops_rev_rotate.c \
				ops_rotate.c \
				ops_swap_push.c \
				parse_args.c \
				primitives.c \
				record.c \
				stack_query.c \
				stack_utils.c

SRCS		=	$(SHARED) \
				bench.c \
				dest_loc.c \
				dispatch.c \
				index.c \
				main.c \
				moves.c \
				optimize.c \
				parse_flags.c \
				quick_base.c \
				quick_loc.c \
				sort_complex.c \
				sort_medium.c \
				sort_simple.c \
				sort_small.c \
				turk_rot.c \
				turk_target.c

# Bonus: o checker usa os ficheiros partilhados + os seus *_bonus.c
BONUS_SRCS	=	$(SHARED) \
				checker_bonus.c \
				checker_utils_bonus.c

# ================================ OBJETOS ===================================
OBJS		=	$(SRCS:.c=.o)
BONUS_OBJS	=	$(BONUS_SRCS:.c=.o)

# ================================= REGRAS ===================================

# Regra padrao: compila o push_swap
all: $(NAME)

# Linka os objetos com a libft para gerar o executavel
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

# Bonus: gera o checker (sem relink, tal como o push_swap)
bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -L$(LIBFT_DIR) -lft -o $(BONUS_NAME)

# Compila a libft usando o Makefile dela (o FORCE faz o make da libft
# sempre rodar; ela mesma decide se precisa recompilar algo)
$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)

# Compila cada .c em .o (recompila se um dos headers mudar)
%.o: %.c push_swap.h checker_bonus.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Remove os objetos (.o) do projeto e da libft
clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

# Remove os objetos e os executaveis/bibliotecas
fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Recompila tudo do zero
re: fclean all

# Alvo vazio usado para forcar a execucao da regra da libft
FORCE:

.PHONY: all bonus clean fclean re FORCE