/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 16:27:00 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/16 12:08:05 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "libft/libft.h"

typedef enum e_ops
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
	OP_SIZE
}	t_ops;

typedef enum e_strat
{
	STRAT_ADAPTIVE,
	STRAT_SIMPLE,
	STRAT_MEDIUM,
	STRAT_COMPLEX,
}	t_strat;

typedef struct s_node
{
	struct s_node	*next;
	int				content;
	struct s_node	*previous;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	int	size;
}	t_stack;

typedef struct s_ctx
{
	t_stack	*a;
	t_stack	*b;
	int		ops_count[OP_SIZE];
}	t_ctx;

typedef struct s_cfg
{
	t_strat	strat;
	int		bench;
}	t_cfg;

void	swap(t_stack *stack);
void	push(t_stack *src, t_stack *dst);
void	rotate(t_stack *stack);
void	rev_rotate(t_stack *stack);

void	sa(t_ctx *ctx);
void	ss(t_ctx *ctx);
void	sb(t_ctx *ctx);
void	pa(t_ctx *ctx);
void	pb(t_ctx *ctx);
void	ra(t_ctx *ctx);
void	rb(t_ctx *ctx);
void	rr(t_ctx *ctx);
void	rra(t_ctx *ctx);
void	rrb(t_ctx *ctx);
void	rrr(t_ctx *ctx);

char	*op_name(t_ops op);
void	record_op(t_ctx *ctx, t_ops op);

double	disorder(t_stack *a);

int		parse_flags(char **argv, t_cfg *cfg);
int		parse_number(char *str, int *out);

t_node	*new_node(int value);
int		add_bottom(t_stack *stack, int value);
int		has_value(t_stack *stack, int value);
void	free_stack(t_stack *stack);


#endif
