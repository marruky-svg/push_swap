/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 11:59:17 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 12:13:28 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** op_name: converte um t_ops no texto da operacao ("sa", "pb"...).
** Retorna NULL se op for invalido (>= OP_SIZE).
*/
char	*op_name(t_ops op)
{
	char	*names[OP_SIZE];

	if (op >= OP_SIZE)
		return (NULL);
	names[OP_PA] = "pa";
	names[OP_PB] = "pb";
	names[OP_RA] = "ra";
	names[OP_RB] = "rb";
	names[OP_RR] = "rr";
	names[OP_RRA] = "rra";
	names[OP_RRB] = "rrb";
	names[OP_RRR] = "rrr";
	names[OP_SA] = "sa";
	names[OP_SB] = "sb";
	names[OP_SS] = "ss";
	return (names[op]);
}

static int	grow_buffer(t_ctx *ctx)
{
	t_ops	*bigger;
	int		new_cap;

	new_cap = 64;
	if (ctx->cap > 0)
		new_cap = ctx->cap * 2;
	bigger = malloc(sizeof(t_ops) * new_cap);
	if (!bigger)
		return (0);
	if (ctx->buf)
		ft_memcpy(bigger, ctx->buf, sizeof(t_ops) * ctx->len);
	free(ctx->buf);
	ctx->buf = bigger;
	ctx->cap = new_cap;
	return (1);
}

void	record_op(t_ctx *ctx, t_ops op)
{
	if (op >= OP_SIZE)
	{
		ft_putendl_fd("record_op: invalid op", 2);
		return ;
	}
	if (ctx->len == ctx->cap && !grow_buffer(ctx))
	{
		ctx->alloc_failed = 1;
		return ;
	}
	ctx->buf[ctx->len] = op;
	ctx->len++;
}
