/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 10:30:00 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 12:36:56 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_ops	merged(t_ops x, t_ops y)
{
	if ((x == OP_RA && y == OP_RB) || (x == OP_RB && y == OP_RA))
		return (OP_RR);
	if ((x == OP_RRA && y == OP_RRB) || (x == OP_RRB && y == OP_RRA))
		return (OP_RRR);
	if ((x == OP_SA && y == OP_SB) || (x == OP_SB && y == OP_SA))
		return (OP_SS);
	return (OP_SIZE);
}

static int	cancels(t_ops x, t_ops y)
{
	if ((x == OP_PA && y == OP_PB) || (x == OP_PB && y == OP_PA))
		return (1);
	if ((x == OP_RA && y == OP_RRA) || (x == OP_RRA && y == OP_RA))
		return (1);
	if ((x == OP_RB && y == OP_RRB) || (x == OP_RRB && y == OP_RB))
		return (1);
	if ((x == OP_RR && y == OP_RRR) || (x == OP_RRR && y == OP_RR))
		return (1);
	return (x == y && (x == OP_SA || x == OP_SB || x == OP_SS));
}

static void	optimize_ops(t_ctx *ctx)
{
	int		i;
	int		out;
	t_ops	m;

	i = 0;
	out = 0;
	while (i < ctx->len)
	{
		m = OP_SIZE;
		if (out > 0)
			m = merged(ctx->buf[out - 1], ctx->buf[i]);
		if (out > 0 && cancels(ctx->buf[out - 1], ctx->buf[i]))
			out--;
		else if (m != OP_SIZE)
			ctx->buf[out - 1] = m;
		else
			ctx->buf[out++] = ctx->buf[i];
		i++;
	}
	ctx->len = out;
}

void	flush_ops(t_ctx *ctx)
{
	int	i;

	optimize_ops(ctx);
	i = 0;
	while (i < ctx->len)
	{
		ctx->ops_count[ctx->buf[i]]++;
		ft_putendl_fd(op_name(ctx->buf[i]), 1);
		i++;
	}
}
